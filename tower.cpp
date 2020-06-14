#include "Tower.h"
#include<QPainter>
#include<QVector2D>
#include "enemy.h"
#include "mainwindow.h"
#include "bullet.h"
#include"function.h"

Tower::Tower(QPoint pos,MainWindow*_game, const QPixmap &image):
    game(_game), position(pos),tower_image(image),attackstate(false),lockEnemy(NULL)
{
        rotateAngle=0.0;
       attackrate=500;
       attackrange=100;
       damage=30;
       attackTimer = new QTimer(this);
        connect(attackTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}
const QSize Tower::tower_size(100,100);
void Tower::checkEnemyInRange()
{
    if (lockEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(lockEnemy->getPosition() - position);
        normalized.normalize();
        rotateAngle = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围
        if (!Collision(position, attackrange, lockEnemy->getPosition(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = game->getenemylist();
        foreach (Enemy *enemy, enemyList)
        {
            if (Collision(position, attackrange, enemy->getPosition(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

Tower::~Tower()
{
    delete attackTimer;
    attackTimer = NULL;
}
void Tower::attackEnemy()
{
    attackTimer->start(attackrate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    lockEnemy = enemy;
    attackEnemy();
    lockEnemy->getAttacked(this);
}

void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(position, lockEnemy->getPosition(), damage, lockEnemy, game);
    bullet->move();
    game->addBullet(bullet);
}

void Tower::targetKilled()
{
    if (lockEnemy)
        lockEnemy = NULL;

    attackTimer->stop();
    rotateAngle = 0.0;
}

void Tower::lostSightOfEnemy()
{
    lockEnemy->gotLostSight(this);
    if (lockEnemy)
        lockEnemy = NULL;

    attackTimer->stop();
    rotateAngle = 0.0;
}

void Tower::show(QPainter *painter)
{
    painter->save();
    static const QPoint offsetPoint(-tower_size.width() / 2, -tower_size.height() / 2);
    painter->translate(position);
    painter->drawPixmap(offsetPoint, tower_image);
    painter->restore();
}
