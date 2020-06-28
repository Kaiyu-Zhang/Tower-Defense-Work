#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "musicplayer.h"
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>

static const int TowerCost = 300;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_waves = 0;
    powerType = 1;
    m_playerHp = 5;
    m_playrGold = 1000;
    m_gameEnded = false;
    m_gameState = false;
    setWindowTitle("Qt塔防");
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();

    m_MusicPlayer = new MusicPlayer(this);
    m_MusicPlayer->startBGM();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    // 设置500ms后游戏启动
    QTimer::singleShot(500, this, SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTowerPositions()
{
    m_towerPositionsList.push_back(QPoint(310-25, 250-20));
    m_towerPositionsList.push_back(QPoint(480-25, 250-20));
    m_towerPositionsList.push_back(QPoint(530-25, 250-20));
    m_towerPositionsList.push_back(QPoint(700-25, 250-20));
    m_towerPositionsList.push_back(QPoint(760-25, 250-20));
    m_towerPositionsList.push_back(QPoint(310-25, 500-20));
    m_towerPositionsList.push_back(QPoint(480-25, 500-20));
    m_towerPositionsList.push_back(QPoint(530-25, 500-20));
    m_towerPositionsList.push_back(QPoint(700-25, 500-20));
    m_towerPositionsList.push_back(QPoint(760-25, 500-20));


}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameState)
    {
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/image/over.jpg");
        pix.scaled(this->width(),this->height());
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        QString text = m_gameEnded ? "你输了!!!" : "你赢了!!!";
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    QPixmap cachePix(":/image/Bg.png");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave(&cachePainter);
    drawHP(&cachePainter);
    drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    if(event->button()==Qt::LeftButton)//鼠标右
    {
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
            {
                m_MusicPlayer->playSound(TowerPlaceSound);
                m_playrGold -= TowerCost;
                it->setHasTower();

                Tower *tower;
                if(powerType == 1){
                    tower = new TowerTypeA(it->centerPos(), this);
                }
                if(powerType == 2){
                    tower = new TowerTypeB(it->centerPos(), this);
                }
                if(powerType == 3){
                    tower = new TowerTypeC(it->centerPos(), this);
                }
                m_towersList.push_back(tower);
                update();
                break;
            }
            ++it;
        }
    }
    if(event->button()==Qt::RightButton)//鼠标右
    {
        QMenu *pMenu = new QMenu(this);
        QAction *actA = new QAction(tr("炮台1"), this);
        QAction *actB = new QAction(tr("炮台2"), this);
        QAction *actC = new QAction(tr("炮台3"), this);
        actA->setIcon(QIcon(":/image/tower1.png"));
        actB->setIcon(QIcon(":/image/tower2.png"));
        actC->setIcon(QIcon(":/image/tower3.png"));
        pMenu->addAction(actA);
        pMenu->addAction(actB);
        pMenu->addAction(actC);
        connect(actA, SIGNAL(triggered()), this, SLOT(mousePowerA()));
        connect(actB, SIGNAL(triggered()), this, SLOT(mousePowerB()));
        connect(actC, SIGNAL(triggered()), this, SLOT(mousePowerC()));
        pMenu->exec(cursor().pos());
    }
}

bool MainWindow::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void MainWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QRect(400, 5, 100, 25), QString("敌人波数 : %1").arg(m_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QRect(30, 5, 100, 25), QString("生命 : %1").arg(m_playerHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QRect(200, 5, 200, 25), QString("金币 : %1").arg(m_playrGold));
}

void MainWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
    }
}

void MainWindow::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

MusicPlayer *MainWindow::musicPlayer() const
{
    return m_MusicPlayer;
}

void MainWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(190, 200));
    WayPoint *wayPoint2 = new WayPoint(QPoint(355, 200));
    WayPoint *wayPoint3 = new WayPoint(QPoint(355, 370));
    WayPoint *wayPoint4 = new WayPoint(QPoint(430, 370));
    WayPoint *wayPoint5 = new WayPoint(QPoint(430, 540));
    WayPoint *wayPoint6 = new WayPoint(QPoint(575, 540));
    WayPoint *wayPoint7 = new WayPoint(QPoint(575, 370));
    WayPoint *wayPoint8 = new WayPoint(QPoint(650, 370));
    WayPoint *wayPoint9 = new WayPoint(QPoint(650, 200));
    WayPoint *wayPoint10 = new WayPoint(QPoint(800, 200));
    WayPoint *wayPoint11 = new WayPoint(QPoint(800, 370));
    WayPoint *wayPoint12 = new WayPoint(QPoint(880, 370));

    m_wayPointsListA.push_back(wayPoint1);
    m_wayPointsListA.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);
    m_wayPointsListA.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);
    m_wayPointsListA.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);
    m_wayPointsListA.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);
    m_wayPointsListA.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
    m_wayPointsListA.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);
    m_wayPointsListA.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);
    m_wayPointsListA.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);
    m_wayPointsListA.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);
    m_wayPointsListA.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);
    m_wayPointsListA.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);


    WayPoint *bwayPoint1 = new WayPoint(QPoint(190, 540));
    WayPoint *bwayPoint2 = new WayPoint(QPoint(355, 540));
    WayPoint *bwayPoint3 = new WayPoint(QPoint(355, 370));
    WayPoint *bwayPoint4 = new WayPoint(QPoint(430, 370));
    WayPoint *bwayPoint5 = new WayPoint(QPoint(430, 200));
    WayPoint *bwayPoint6 = new WayPoint(QPoint(575, 200));
    WayPoint *bwayPoint7 = new WayPoint(QPoint(575, 370));
    WayPoint *bwayPoint8 = new WayPoint(QPoint(650, 370));
    WayPoint *bwayPoint9 = new WayPoint(QPoint(650, 540));
    WayPoint *bwayPoint10 = new WayPoint(QPoint(800, 540));
    WayPoint *bwayPoint11 = new WayPoint(QPoint(800, 370));
    WayPoint *bwayPoint12 = new WayPoint(QPoint(880, 370));

    m_wayPointsListB.push_back(bwayPoint1);
    m_wayPointsListB.push_back(bwayPoint2);
    bwayPoint2->setNextWayPoint(bwayPoint1);
    m_wayPointsListB.push_back(bwayPoint3);
    bwayPoint3->setNextWayPoint(bwayPoint2);
    m_wayPointsListB.push_back(bwayPoint4);
    bwayPoint4->setNextWayPoint(bwayPoint3);
    m_wayPointsListB.push_back(bwayPoint5);
    bwayPoint5->setNextWayPoint(bwayPoint4);
    m_wayPointsListB.push_back(bwayPoint6);
    bwayPoint6->setNextWayPoint(bwayPoint5);
    m_wayPointsListB.push_back(bwayPoint7);
    bwayPoint7->setNextWayPoint(bwayPoint6);
    m_wayPointsListB.push_back(bwayPoint8);
    bwayPoint8->setNextWayPoint(bwayPoint7);
    m_wayPointsListB.push_back(bwayPoint9);
    bwayPoint9->setNextWayPoint(bwayPoint8);
    m_wayPointsListB.push_back(bwayPoint10);
    bwayPoint10->setNextWayPoint(bwayPoint9);
    m_wayPointsListB.push_back(bwayPoint11);
    bwayPoint11->setNextWayPoint(bwayPoint10);
    m_wayPointsListB.push_back(bwayPoint12);
    bwayPoint12->setNextWayPoint(bwayPoint11);
}

void MainWindow::getHpDamage(int damage/* = 1*/)
{
    m_MusicPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameState = true;
        }
    }
}

void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void MainWindow::preLoadWavesInfo()
{
    QStringList tlistA;
    tlistA.append("1500");
    tlistA.append("1800");
    tlistA.append("2200");
    tlistA.append("2500");
    tlistA.append("2800");
    tlistA.append("3100");
    tlistA.append("4400");
    m_waveslist.append(tlistA);

    QStringList tlistB;
    tlistB.append("500");
    tlistB.append("800");
    tlistB.append("1200");
    tlistB.append("1500");
    tlistB.append("1800");
    tlistB.append("2100");
    tlistB.append("2400");
    m_waveslist.append(tlistB);

    QStringList tlistC;
    tlistC.append("300");
    tlistC.append("400");
    tlistC.append("700");
    tlistC.append("1100");
    tlistC.append("1400");
    tlistC.append("2800");
    tlistC.append("2900");
    m_waveslist.append(tlistC);
}

bool MainWindow::loadWave()
{
    if (m_waves >= m_waveslist.size())
        return false;
    int ranenum = qrand()%2;
    WayPoint *startWayPoint;
    if(ranenum==0){
        startWayPoint = m_wayPointsListA.back();
    }else{
        startWayPoint = m_wayPointsListB.back();
    }
    for (int i = 0; i < m_waveslist.at(m_waves).size(); ++i)
    {
        int spawnTime = m_waveslist.at(m_waves).at(i).toInt();
        Enemy *enemy;
        int randnum = qrand()%4;
        if(randnum == 0){
            enemy = new QEnemyTypeA(startWayPoint, this);
        }if(randnum == 1){
            enemy = new QEnemyTypeB(startWayPoint, this);
        }if(randnum == 2){
            enemy = new QEnemyTypeC(startWayPoint, this);
        }if(randnum == 3){
            enemy = new QEnemyTypeD(startWayPoint, this);
        }

        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }
    return true;
}

QList<Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::gameStart()
{
    loadWave();
}

void MainWindow::mousePowerA()
{
    powerType = 1;
}

void MainWindow::mousePowerB()
{
    powerType = 2;
}

void MainWindow::mousePowerC()
{
    powerType = 3;
}
