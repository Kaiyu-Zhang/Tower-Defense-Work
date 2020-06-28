#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Tower;
class TowerTypeA;
class TowerTypeB;
class TowerTypeC;
class Enemy;
class GameWidgetA;
class QTimer;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, GameWidgetA *game, const QPixmap &sprite = QPixmap(""));
    ~Tower();

    void draw(QPainter *painter) const;
    virtual void particularDraw(QPainter *painter) const=0;
    QPoint pos() const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void damageEnemy();
    void lostSightOfEnemy();
    int getTowerRange();//距离
    int getTowerDamage();
    int getFireRate();
    void setTowerData(int);//距离
    void setTowerData(int,int);//距离加伤害
    void setTowerData(int,int,int);//距离加伤害加攻速
    virtual int getTowerType()=0;
public slots:
    virtual void shootWeapon()=0;
    QPoint retPointTower();
public:
    bool			t_attacking;
    int				t_attackRange;	// 代表塔可以攻击到敌人的距离
    int				t_damage;		// 代表攻击敌人时造成的伤害
    int				t_fireRate;		// 代表再次攻击敌人的时间间隔
    qreal			t_rotationSprite;

    Enemy *			t_chooseEnemy;
    GameWidgetA *	t_game;
    QTimer *		t_fireRateTimer;

    QPoint	t_pos;
    const QPixmap	t_sprite;

    static const QSize ms_fixedSize;
};

class TowerTypeA : public Tower
{
    Q_OBJECT
public:
    TowerTypeA(QPoint pos, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/tower1.png"));
    ~TowerTypeA(){}
    void particularDraw(QPainter *painter) const;
    int getTowerType()
    {
        return 1;
    }
public slots:
    void shootWeapon();
};

class TowerTypeB : public Tower
{
    Q_OBJECT
public:
    TowerTypeB(QPoint pos, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/tower2.png"));
    ~TowerTypeB(){}
    void particularDraw(QPainter *painter) const;
    int getTowerType()
    {
        return 2;
    }
public slots:
    void shootWeapon();
};

class TowerTypeC : public Tower
{
    Q_OBJECT
public:
    TowerTypeC(QPoint pos, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/tower3.png"));
    ~TowerTypeC(){}
    void particularDraw(QPainter *painter) const;
    int getTowerType()
    {
        return 3;
    }
public slots:
    void shootWeapon();
};

#endif // TOWER_H
