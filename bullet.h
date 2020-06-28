#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>


class QPainter;
class Enemy;
class GameWidgetA;

class Bullet : QObject
{
	Q_OBJECT
    Q_PROPERTY(QPoint b_currentPos READ currentPos WRITE setCurrentPos)

public:
	Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/bullet.png"));

	void draw(QPainter *painter) const;
	void move();
	void setCurrentPos(QPoint pos);
	QPoint currentPos() const;

private slots:
	void hitTarget();

private:
    const QPoint	b_startPos;
    const QPoint	b_targetPos;
    const QPixmap	b_sprite;
    QPoint			b_currentPos;
    Enemy *			b_target;
    GameWidgetA *	b_game;
    int				b_damage;

	static const QSize ms_fixedSize;
};

#endif // BULLET_H
