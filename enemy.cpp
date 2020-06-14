#include "enemy.h"

#include"mainwindow.h"
#include <QVector2D>
Enemy::Enemy(Checkpoints *startPoint,MainWindow* _game,const QPixmap &image):
    QObject(0),game(_game),enemy_image(image),position(startPoint->pos()),destination(startPoint->nextCheckpoint())
{

    maxlife=100;
    life=100;
    speed=5.0;

    angle=0.0;
    active=false;
    }
const QSize Enemy::enemy_size(120,120);
Enemy::~Enemy()
{
    destination=NULL;
    game=NULL;
}
void Enemy::enable()
{
    active = true;
}

void Enemy::show(QPainter*painter)
{
        if (!active)
            return;

        const int width = 90;
        painter->save();
        QPoint healthBarPoint = position + QPoint(-width / 2 , -enemy_size.height() / 3);
        // 绘制血条
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::red);
        QRect totalHealthRect(healthBarPoint, QSize(width, 2));
        painter->drawRect(totalHealthRect);
        painter->setBrush(Qt::green);


        QRect healthBarRect(healthBarPoint, QSize(double(life)/double(maxlife) * width, 2));
        painter->drawRect(healthBarRect);
        // 绘制偏转坐标,由中心+偏移=左上
        static const QPoint offsetPoint(-enemy_size.width() / 2, -enemy_size.height() / 2);
        painter->translate(position);
        painter->rotate(angle);
        // 绘制敌人
        painter->drawPixmap(offsetPoint,enemy_image);
        painter->restore();
}
void Enemy::move()
{
    if (!active)
        return;
    if (Collision(position,1,destination->pos(),1))
        // 敌人抵达了一个航点
                {if (destination->nextCheckpoint())
                {
                    // 还有下一个航点
                    position = destination->pos();
                    destination = destination->nextCheckpoint();
                }
                else
                {
                    // 表示进入基地
                    game->getHpDamage();
                    game->removeEnemy(this);
                    return;
                }
            }
        QPoint targetPoint = destination->pos();
        // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
        // 向量标准化
        double movementSpeed = speed;
        QVector2D normalized(targetPoint - position);
        normalized.normalize();
        position = position + normalized.toPoint() * movementSpeed;
        // 确定敌人选择方向

        angle = double( qRadiansToDegrees(qAtan2(normalized.y(), normalized.x()))) ;


}
QPoint Enemy:: getPosition()
{
    return position;
}
void Enemy::getAttacked(Tower *attacker)
{
    attackedTowersList.push_back(attacker);
}
void Enemy::gotLostSight(Tower *attacker)
{
    attackedTowersList.removeOne(attacker);
}
void Enemy::getDamage(int damage)
{

    life -= damage;

    // 阵亡,需要移除
    if (life <= 0)
    {

        getRemoved();
    }
}
void Enemy::getRemoved()
{
    if (attackedTowersList.empty())
        return;

    foreach (Tower *attacker, attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    game->removedEnemy(this);
}

