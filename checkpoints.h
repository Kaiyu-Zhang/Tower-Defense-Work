#ifndef CHECKPOINTS_H
#define CHECKPOINTS_H
#include <QPoint>
#include<QPixmap>
#include<QPainter>

class Checkpoints
{
public:
    Checkpoints(QPoint pos);
    Checkpoints(const Checkpoints& c);
    void set(const Checkpoints& c);
    void setNextCheckpoint(Checkpoints *nextPoint);
    Checkpoints * nextCheckpoint() const;
    const QPoint pos() const;
    void show(QPainter *painter) const;
private:
    QPoint position;
    Checkpoints * nextPoint;

};

#endif // CHECKPOINTS_H
