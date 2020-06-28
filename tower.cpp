#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "gamewidgeta.h"
#include "function.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(42, 42);

Tower::Tower(QPoint pos, GameWidgetA *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/)
    : t_attacking(false)
    , t_attackRange(70)
    , t_damage(10)
    , t_fireRate(1000)
    , t_rotationSprite(0.0)
    , t_chooseEnemy(NULL)
    , t_game(game)
    , t_pos(pos)
    , t_sprite(sprite)
{
    t_fireRateTimer = new QTimer(this);
    connect(t_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower()
{
    delete t_fireRateTimer;
    t_fireRateTimer = NULL;
}


void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(QPen(QColor(170,255,63),1));
    // 绘制攻击范围
    painter->drawEllipse(t_pos, t_attackRange, t_attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(t_pos);
    painter->rotate(t_rotationSprite);
    painter->drawPixmap(offsetPoint, t_sprite);
    painter->restore();
}
QPoint Tower::pos() const
{
    return t_pos;
}
void Tower::checkEnemyInRange()
{
    if (t_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(t_chooseEnemy->pos() - t_pos);
        normalized.normalize();
        t_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围
        if (!Collision(t_pos, t_attackRange, t_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = t_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (Collision(t_pos, t_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}
void Tower::attackEnemy()
{
    t_fireRateTimer->start(t_fireRate);
    t_attacking=true;
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    t_chooseEnemy = enemy;
    attackEnemy();
    t_chooseEnemy->getAttacked(this);
}



void Tower::targetKilled()
{
    if (t_chooseEnemy)
        t_chooseEnemy = NULL;

    t_fireRateTimer->stop();
    t_rotationSprite = 0.0;
    t_attacking=false;
}

void Tower::lostSightOfEnemy()
{
    t_chooseEnemy->gotLostSight(this);
    if (t_chooseEnemy)
        t_chooseEnemy = NULL;

    t_fireRateTimer->stop();
    t_rotationSprite = 0.0;
    t_attacking=false;
}

int Tower::getTowerRange()
{
    return t_attackRange;
}
int Tower::getTowerDamage()
{
    return t_damage;
}
int Tower::getFireRate()
{
    return t_fireRate;
}
QPoint Tower::retPointTower()
{
    return t_pos;
}

void Tower::setTowerData(int valueA)
{
    t_attackRange = valueA;
}

void Tower::setTowerData(int valueA, int valueB)
{
    t_attackRange = valueA;
    t_damage = valueB;
}

void Tower::setTowerData(int valueA, int valueB, int valueC)
{
    t_attackRange = valueA;
    t_damage = valueB;
    t_fireRate = valueC;
}

TowerTypeA::TowerTypeA(QPoint pos, GameWidgetA *game, const QPixmap &sprite):Tower(pos,game,sprite)
{
    t_attackRange=120;
    //
    t_damage=20;
    t_fireRate=500;
}

TowerTypeB::TowerTypeB(QPoint pos, GameWidgetA *game, const QPixmap &sprite):Tower(pos,game,sprite)
{
    t_attackRange=70;
    t_damage=15;
    t_fireRate=750;
}

TowerTypeC::TowerTypeC(QPoint pos, GameWidgetA *game, const QPixmap &sprite):Tower(pos,game,sprite)
{
    t_attackRange=90;
    t_damage=1;
    t_fireRate=50;
}

void TowerTypeA::shootWeapon()
{
    Bullet *bullet = new Bullet(t_pos, t_chooseEnemy->pos(), t_damage, t_chooseEnemy, t_game);
    bullet->move();
    t_game->addBullet(bullet);
}

void TowerTypeB::shootWeapon()
{

    QList<Enemy *> enemyList = t_game->enemyList();
    foreach (Enemy *enemy, enemyList)
    {
        if (Collision(t_pos, t_attackRange, enemy->pos(), 1))
        {

            enemy->getDamage(t_damage);
        }
    }
}

void TowerTypeC::shootWeapon()
{
    t_chooseEnemy->getDamage(t_damage);

}

void TowerTypeA::particularDraw(QPainter *painter) const
{
    return;
}

void TowerTypeB::particularDraw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    if(t_attacking)
    {
        painter->drawEllipse(t_pos, t_attackRange, t_attackRange);
    }
    painter->restore();
}

void TowerTypeC::particularDraw(QPainter *painter) const
{
    painter->save();
    painter->setPen(QPen(QColor(155,0,0),3));
    if(t_attacking)
    {
        painter->drawLine(this->pos(),t_chooseEnemy->pos());
    }
    painter->restore();
}
