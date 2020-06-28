#include "bullet.h"
#include "enemy.h"
#include "GameWidgetA.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(8, 8);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               GameWidgetA *game, const QPixmap &sprite/* = QPixmap(":/image/bullet.png")*/)
    : b_startPos(startPos)
    , b_targetPos(targetPoint)
    , b_sprite(sprite)
    , b_currentPos(startPos)
    , b_target(target)
    , b_game(game)
    , b_damage(damage)
{
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(b_currentPos, b_sprite);
}

void Bullet::move()
{
	// 100毫秒内击中敌人
	static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "b_currentPos");
	animation->setDuration(duration);
    animation->setStartValue(b_startPos);
    animation->setEndValue(b_targetPos);
	connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

	animation->start();
}

void Bullet::hitTarget()
{
	// 这样处理的原因是:
	// 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
	// 后续炮弹再攻击到的敌人就是无效内存区域
	// 因此先判断下敌人是否还有效
    if (b_game->enemyList().indexOf(b_target) != -1)
        b_target->getDamage(b_damage);
    b_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos)
{
    b_currentPos = pos;
}

QPoint Bullet::currentPos() const
{
    return b_currentPos;
}
