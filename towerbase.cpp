#include "Towerbase.h"
#include <QPainter>

Towerbase::Towerbase(QPoint pos,const QPixmap &image):
position(pos),base_havetower(false),base_image(image)
{

}
const QSize Towerbase::base_size(100,100);


void Towerbase::setbase(bool state)
{
    base_havetower=state;
}

bool Towerbase::havetower() const
{
    return base_havetower;
}
void Towerbase::setHaveTower()
{
    base_havetower= true;
}
const  QPoint Towerbase::center() const
{
    QPoint realcenter(position.x()+base_size.width() / 2,position.y()+ base_size.height() / 2);
    return realcenter;

}
bool Towerbase:: inrange(const QPoint &pos) const
{
    bool isXInHere = position.x() < pos.x() && pos.x() < (position.x() + base_size.width());
    bool isYInHere = position.y() < pos.y() && pos.y() < (position.y() + base_size.height());
    return isXInHere && isYInHere;
}
void Towerbase:: show(QPainter *painter)
{
    painter->drawPixmap(position.x(),position.y(),base_image);
}
