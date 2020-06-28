#include "enemy.h"
#include "turnpoint.h"
#include "tower.h"
#include "function.h"
#include "GameWidgetA.h"
#include "musicplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 20;

const QSize Enemy::ms_fixedSize(52, 52);


Enemy::Enemy(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite/* = QPixmap(":/image/enemy.png")*/)
    : QObject(0)
    , e_active(false)
    , e_maxHp(40)
    , e_currentHp(40)
    , e_walkingSpeed(1.0)
    , e_rotationSprite(0.0)
    , e_pos(startTurnPoint->pos())
    , e_destinationTurnPoint(startTurnPoint->nextTurnPoint())
    , e_game(game)
    , e_sprite(sprite)
{
}

Enemy::~Enemy()
{
    e_attackedTowersList.clear();
    e_destinationTurnPoint = NULL;
    e_game = NULL;
}

void Enemy::doActivate()
{
    e_active = true;
}

void Enemy::setEnemyData(int t_value)
{
    e_maxHp = t_value;
    e_currentHp=t_value;
}

void Enemy::setEnemyData(int t_value, qreal t_s)
{
    e_maxHp = t_value;
    e_currentHp=t_value;
    e_walkingSpeed = t_s;
}
void Enemy::setDifficulty(double t_value)
{
    e_maxHp=int(e_maxHp*(1+t_value/3));
    e_currentHp=e_maxHp;
    if(t_value<2)
    e_walkingSpeed*=t_value;
    else {
        e_walkingSpeed*=2;
    }
}
void Enemy::move()
{
    if (!e_active)
        return;

    if (Collision(e_pos, 1, e_destinationTurnPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (e_destinationTurnPoint->nextTurnPoint())
        {
            // 还有下一个航点
            e_pos = e_destinationTurnPoint->pos();
            e_destinationTurnPoint = e_destinationTurnPoint->nextTurnPoint();
        }
        else
        {
            // 表示进入基地
            e_game->getHpDamage();
            e_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = e_destinationTurnPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,e_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = e_walkingSpeed;
    QVector2D normalized(targetPoint - e_pos);
    normalized.normalize();
    e_pos = e_pos + normalized.toPoint() * movementSpeed;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
    e_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}

void Enemy::draw(QPainter *painter) const
{
    if (!e_active)
        return;

    painter->save();

    QPoint healthBarPoint = e_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 2);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)e_currentHp / e_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(e_pos);
    painter->rotate(e_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, e_sprite);

    painter->restore();
}

void Enemy::getRemoved()
{
    if (e_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, e_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    e_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{
    e_game->musicPlayer()->playSound(LaserShootSound);
    e_currentHp -= damage;

    // 阵亡,需要移除
    if (e_currentHp <= 0)
    {
        e_game->musicPlayer()->playSound(EnemyDestorySound);
        e_game->awardGold(200);
        getRemoved();
    }
}

void Enemy::getAttacked(Tower *attacker)
{
    e_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
    e_attackedTowersList.removeOne(attacker);
}

QPoint Enemy::pos() const
{
    return e_pos;
}


QEnemyTypeA::QEnemyTypeA(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite): Enemy(startTurnPoint,game,sprite)
{
      setEnemyData(40,1.0);
}

QEnemyTypeB::QEnemyTypeB(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite): Enemy(startTurnPoint,game,sprite)
{
    setEnemyData(25,2);
}
//强大敌人类
QEnemyTypeC::QEnemyTypeC(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite): Enemy(startTurnPoint,game,sprite)
{
    setEnemyData(80,1.2);
}

QEnemyTypeD::QEnemyTypeD(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite): Enemy(startTurnPoint,game,sprite)
{
    setEnemyData(50,2);
}
