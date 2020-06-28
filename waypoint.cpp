#include "turnpoint.h"
#include <QPainter>
#include <QColor>

TurnPoint::TurnPoint(QPoint pos)
	: m_pos(pos)
    , m_nextTurnPoint(NULL)
{
}

void TurnPoint::setNextTurnPoint(TurnPoint *nextPoint)
{
    m_nextTurnPoint = nextPoint;
}

TurnPoint* TurnPoint::nextTurnPoint() const
{
    return m_nextTurnPoint;
}

const QPoint TurnPoint::pos() const
{
	return m_pos;
}

void TurnPoint::draw(QPainter *painter) const
{
	painter->save();
	painter->setPen(Qt::green);
	painter->drawEllipse(m_pos, 6, 6);
	painter->drawEllipse(m_pos, 2, 2);

    if (m_nextTurnPoint)
        painter->drawLine(m_pos, m_nextTurnPoint->m_pos);
	painter->restore();
}
