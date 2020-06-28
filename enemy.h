#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class TurnPoint;
class QPainter;
class GameWidgetA;
class Tower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint pos() const;

    //多态实现
    void setEnemyData(int t_value, qreal t_s);
    void setEnemyData(int t_value);
    void setDifficulty(qreal t_value);
public slots:
    void doActivate();

private:
    bool			e_active;
    int				e_maxHp;
    int				e_currentHp;
    qreal			e_walkingSpeed;
    qreal			e_rotationSprite;

    QPoint			e_pos;
    TurnPoint *		e_destinationTurnPoint;
    GameWidgetA *	e_game;
    QList<Tower *>	e_attackedTowersList;

    const QPixmap	e_sprite;
    static const QSize ms_fixedSize;
};

class QEnemyTypeA : public Enemy
{
    Q_OBJECT
public:
    QEnemyTypeA(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/enemy1.png"));
    ~QEnemyTypeA(){}

};

class QEnemyTypeB : public Enemy
{
    Q_OBJECT
public:
    QEnemyTypeB(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/enemy2.png"));
    ~QEnemyTypeB(){}

};
//强大的敌人1
class QEnemyTypeC : public Enemy
{
    Q_OBJECT
public:
    QEnemyTypeC(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/enemy3.png"));
    ~QEnemyTypeC(){}

};
//强大的敌人2
class QEnemyTypeD : public Enemy
{
    Q_OBJECT
public:
    QEnemyTypeD(TurnPoint *startTurnPoint, GameWidgetA *game, const QPixmap &sprite = QPixmap(":/image/enemy4.png"));
    ~QEnemyTypeD(){}

};
#endif // ENEMY_H
