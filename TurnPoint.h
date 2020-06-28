#ifndef TURNPOINT_H
#define TURNPOINT_H

#include <QPoint>

class QPainter;

// 敌人移动的航线
class TurnPoint
{
public:
    TurnPoint(QPoint pos);

    void setNextTurnPoint(TurnPoint *nextPoint);
    TurnPoint* nextTurnPoint() const;
	const QPoint pos() const;

	void draw(QPainter *painter) const;

private:
	const QPoint		m_pos;
    TurnPoint *			m_nextTurnPoint;
};

#endif // TurnPoint_H
