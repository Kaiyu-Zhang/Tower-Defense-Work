#include "checkpoints.h"


Checkpoints::Checkpoints(QPoint pos)
    : position(pos)
    , nextPoint(NULL)
{
}
Checkpoints:: Checkpoints(const Checkpoints& c)
{
    position=c.position;
    nextPoint=c.nextPoint;

}
void Checkpoints::setNextCheckpoint(Checkpoints *next)
{
    nextPoint = next;
}

Checkpoints* Checkpoints::nextCheckpoint() const
{
    return nextPoint;
}

const QPoint Checkpoints::pos() const
{
    return position;
}

void Checkpoints::show(QPainter *painter) const
{
    painter->save();
    painter->setPen(QColor(255, 255, 255));
//    painter->drawEllipse(position, 6, 6);
//    painter->drawEllipse(position, 2, 2);

    if (nextPoint)
        painter->drawLine(position, nextPoint->position);
    painter->restore();}
