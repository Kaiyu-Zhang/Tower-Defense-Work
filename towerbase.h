#ifndef TOWERBASE_H
#define TOWERBASE_H
#include <QPoint>
#include<QPixmap>

class Towerbase
{
public:
    Towerbase(QPoint pos,const QPixmap &image=QPixmap(":/image/towerbase.jpg"));
    void setbase(bool state=true);  //设定基座
    bool havetower() const;         //是否有塔
    void setHaveTower();
    const QPoint center() const;        //返回中心点
    bool inrange(const QPoint &pos) const;      //是否位于塔座区域内
    void show(QPainter *painter);

private:
    QPoint position;
    bool base_havetower;
    QPixmap base_image;
    static const QSize base_size;
};

#endif // TOWERBASE_H
