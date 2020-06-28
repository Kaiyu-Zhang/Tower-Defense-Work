#ifndef GAMEWIDGETA_H
#define GAMEWIDGETA_H

#include <QWidget>
#include <QDialog>
#include <QList>
#include "towerbase.h"
#include "tower.h"
#include"gamewidgetb.h"
class TurnPoint;
class Enemy;
class QEnemyTypeA;
class QEnemyTypeB;
class QEnemyTypeC;
class QEnemyTypeD;
class Bullet;
class MusicPlayer;

class GameWidgetA : public QDialog
{
    Q_OBJECT
public:
    explicit GameWidgetA(QWidget *parent = nullptr);

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);
//    void setHardValue(int);
    MusicPlayer* musicPlayer() const;
    QList<Enemy *> enemyList() const;
    void setLevel(int);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();

    void mousePowerA();
    void mousePowerB();
    void mousePowerC();

    void upgradePower1();
    void upgradePower2();
    void upgradePower3();
    void removedTower();
private:
    void loadTowerBases();
    void addTurnPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();

private:
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameState;
    MusicPlayer *			m_MusicPlayer;
    QList<QStringList>		m_waveslist;
    QList<TowerBase>        m_TowerBasesList;
    QList<Tower*>			m_towersList;
    QList<TurnPoint *>		m_TurnPointsListA;
    QList<TurnPoint *>		m_TurnPointsListB;
    QList<Enemy *>			m_enemyList;
    QList<Bullet *>			m_bulletList;
    int powerType;
    int level;
    int hardValue=1;
    QPoint pressTowerPos;
    GameWidgetB* w2= new GameWidgetB;
};

#endif // GAMEWIDGETA_H
