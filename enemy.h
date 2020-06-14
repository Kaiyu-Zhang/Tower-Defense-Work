#ifndef ENEMY_H
#define ENEMY_H
#include <QPoint>
#include<QPixmap>
#include<QPainter>
#include<QObject>
#include "checkpoints.h"
#include"function.h"
class MainWindow;
class Tower;
class Enemy:public QObject
{
   Q_OBJECT
public:
    Enemy(Checkpoints* startPoint, MainWindow * _game,const QPixmap &image=QPixmap(":/image/enemy.jpg"));
    ~Enemy();
    void show(QPainter*painter);
    void move();
    void getAttacked(Tower *attacker);
    QPoint getPosition();
    void gotLostSight(Tower *attacker);
    void getDamage(int damage);
    void getRemoved();
public slots:
    void enable();

protected:
    int maxlife;
    int life;
    double speed;
    bool active;
    Checkpoints* destination;
    double angle;
    MainWindow* game;
    QPoint position;
    QPixmap enemy_image;
    static const QSize enemy_size;
    QList<Tower *>	attackedTowersList;

};

#endif // ENEMY_H
