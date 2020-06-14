#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Towerbase.h"
#include <QMainWindow>
#include"enemy.h"
#include"Tower.h"
#include"checkpoints.h"
#include<QObject>
#include "bullet.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void loadTowerbase();
    void setCheckPoints();
    bool canBuy() const;
    void removedEnemy(Enemy *enemy);
    void getHpDamage(int damage=1);
    void removeEnemy(Enemy *enemy);


    void loadEnemy();
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    QList <Enemy*> getenemylist() const;
public slots:
    void updateMap();
private:
    Ui::MainWindow *ui;
    QList <Towerbase> baselist;
    QList <Tower*> towerlist;
    QList <Enemy*> enemylist;
    QList <Checkpoints*> CheckpointsList;
    QList<Bullet *> bulletlist;
    bool gameWin;
    int waves;
};

#endif // MAINWINDOW_H
