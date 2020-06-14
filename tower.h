#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include<QPixmap>
#include<QObject>
#include<QPainter>

#include<QTimer>
class Enemy;
class MainWindow;

class Tower:public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,MainWindow*_game, const QPixmap &image=QPixmap(":/image/tower2.jpg"));
    ~Tower();
    void show(QPainter* painter);
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();

private slots:
    void shootWeapon();
protected:
    QPoint position;
    bool attackstate;
    int attackrate;
    int attackrange;
    int damage;
    QTimer* attackTimer;
    Enemy* lockEnemy;
    MainWindow* game;

    double rotateAngle;
    QPixmap tower_image;
    static const QSize tower_size;
};

#endif // TOWER_H
