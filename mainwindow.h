#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"

namespace Ui {
class MainWindow;
}

class WayPoint;
class Enemy;
class QEnemyTypeA;
class QEnemyTypeB;
class QEnemyTypeC;
class QEnemyTypeD;
class Bullet;
class MusicPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);

    MusicPlayer* musicPlayer() const;
    QList<Enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();

    void mousePowerA();
    void mousePowerB();
    void mousePowerC();

private:
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();

private:
    Ui::MainWindow *		ui;
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameState;
    MusicPlayer *			m_MusicPlayer;
    QList<QStringList>		m_waveslist;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsListA;
    QList<WayPoint *>		m_wayPointsListB;
    QList<Enemy *>			m_enemyList;


    QList<Bullet *>			m_bulletList;

    int powerType;
};

#endif // MAINWINDOW_H
