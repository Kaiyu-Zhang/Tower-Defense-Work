#include "gamewidgeta.h"
#include "turnpoint.h"
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
#include<QWidget>
#include<QApplication>
static const int TowerCost = 400;

GameWidgetA::GameWidgetA(QWidget *parent) : QDialog(parent)
{
    resize(1200,700);
    m_waves = 0;
    powerType = 1;
    m_playerHp = 10;
    m_playrGold = 1500;
    m_gameEnded = false;
    m_gameState = false;
    setWindowTitle("Tower Defense Game");


    m_MusicPlayer = new MusicPlayer(this);
    m_MusicPlayer->startBGM();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    // 设置500ms后游戏启动
    QTimer::singleShot(500, this, SLOT(gameStart()));
}

void GameWidgetA::loadTowerBases()
{
    m_TowerBasesList.clear();
    if(level == 1){
        m_TowerBasesList.push_back(QPoint(310-25, 250-20));
        m_TowerBasesList.push_back(QPoint(480-25, 250-20));
        m_TowerBasesList.push_back(QPoint(530-25, 250-20));
        m_TowerBasesList.push_back(QPoint(700-25, 250-20));
        m_TowerBasesList.push_back(QPoint(760-25, 250-20));
        m_TowerBasesList.push_back(QPoint(310-25, 500-20));
        m_TowerBasesList.push_back(QPoint(480-25, 500-20));
        m_TowerBasesList.push_back(QPoint(530-25, 500-20));
        m_TowerBasesList.push_back(QPoint(700-25, 500-20));
        m_TowerBasesList.push_back(QPoint(760-25, 500-20));
    }else{
        m_TowerBasesList.push_back(QPoint(310-25, 250-20));
        m_TowerBasesList.push_back(QPoint(530-25, 250-20));
        m_TowerBasesList.push_back(QPoint(760-25, 250-20));
        m_TowerBasesList.push_back(QPoint(310-25, 500-20));
        m_TowerBasesList.push_back(QPoint(530-25, 500-20));
        m_TowerBasesList.push_back(QPoint(760-25, 500-20));
    }

}

void GameWidgetA::paintEvent(QPaintEvent *)
{
    if (m_gameEnded )
    {
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/image/over.jpg");
        pix.scaled(this->width(),this->height());
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        QString text = m_gameEnded ? "你输了!!!" : "你赢了!!!";
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
//        QMessageBox msgBox;
//        msgBox.setText("游戏结束");
//        msgBox.exec();
//        done(0);
        return;
    }
    if(m_gameState)
    {
       qApp->closeAllWindows();
        w2->show();
        this->hide();
    }
    QPixmap cachePix;
    if(level == 1){
        cachePix = QPixmap(":/image/Bg.png");
    }else{
        cachePix = QPixmap(":/image/Bg.png");
    }
    QPainter cachePainter(&cachePix);

    foreach (const TowerBase &towerPos, m_TowerBasesList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
    {   tower->draw(&cachePainter);
        tower->particularDraw(&cachePainter);}

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

void GameWidgetA::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    if(event->button()==Qt::LeftButton)//鼠标左
    {
        auto it = m_TowerBasesList.begin();
        while (it != m_TowerBasesList.end())
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
        bool statePos = false;
        auto it = m_TowerBasesList.begin();
        while (it != m_TowerBasesList.end())
        {
            if (it->containPoint(pressPos) && it->hasTower())
            {
                statePos = true;
                pressTowerPos.setX(pressPos.x());
                pressTowerPos.setY(pressPos.y());
                break;
            }
            ++it;
        }

        if(statePos == true){//点击到炮台上了
            QMenu *pMenu = new QMenu(this);
            QAction *actA = new QAction(tr("升级攻击域"), this);
            QAction *actB = new QAction(tr("升级攻击域和攻击力"), this);
            QAction *actC = new QAction(tr("全面升级攻击域，攻击力，攻速"), this);
            QAction *actD = new QAction(tr("拆除防御塔"), this);
            actA->setIcon(QIcon(":/image/icon_gold.png"));
            actB->setIcon(QIcon(":/image/icon_gold.png"));
            actC->setIcon(QIcon(":/image/icon_gold.png"));
            actD->setIcon(QIcon(":/image/icon_red.png"));
            pMenu->addAction(actA);
            pMenu->addAction(actB);
            pMenu->addAction(actC);
            pMenu->addAction(actD);
            connect(actA, SIGNAL(triggered()), this, SLOT(upgradePower1()));
            connect(actB, SIGNAL(triggered()), this, SLOT(upgradePower2()));
            connect(actC, SIGNAL(triggered()), this, SLOT(upgradePower3()));
            connect(actD, SIGNAL(triggered()), this, SLOT(removedTower()));
            pMenu->exec(cursor().pos());
        }else{
            QMenu *pMenu = new QMenu(this);
            QAction *actA = new QAction(tr("子弹攻击塔"), this);
            QAction *actB = new QAction(tr("区域攻击塔"), this);
            QAction *actC = new QAction(tr("激光攻击塔"), this);
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
}

bool GameWidgetA::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void GameWidgetA::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QRect(400, 5, 100, 25), QString("敌人波数 : %1").arg(m_waves + 1));
}

void GameWidgetA::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QRect(30, 5, 100, 25), QString("生命 : %1").arg(m_playerHp));
}

void GameWidgetA::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QRect(200, 5, 200, 25), QString("金币 : %1").arg(m_playrGold));
}

void GameWidgetA::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
    }
}

void GameWidgetA::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

MusicPlayer *GameWidgetA::musicPlayer() const
{
    return m_MusicPlayer;
}

//void GameWidgetA::setHardValue(int value)
//{
//    hardValue=value;
//}

void GameWidgetA::addTurnPoints()
{
    TurnPoint *TurnPoint1 = new TurnPoint(QPoint(190, 200));
    TurnPoint *TurnPoint2 = new TurnPoint(QPoint(355, 200));
    TurnPoint *TurnPoint3 = new TurnPoint(QPoint(355, 370));
    TurnPoint *TurnPoint4 = new TurnPoint(QPoint(430, 370));
    TurnPoint *TurnPoint5 = new TurnPoint(QPoint(430, 540));
    TurnPoint *TurnPoint6 = new TurnPoint(QPoint(575, 540));
    TurnPoint *TurnPoint7 = new TurnPoint(QPoint(575, 370));
    TurnPoint *TurnPoint8 = new TurnPoint(QPoint(650, 370));
    TurnPoint *TurnPoint9 = new TurnPoint(QPoint(650, 200));
    TurnPoint *TurnPoint10 = new TurnPoint(QPoint(800, 200));
    TurnPoint *TurnPoint11 = new TurnPoint(QPoint(800, 370));
    TurnPoint *TurnPoint12 = new TurnPoint(QPoint(880, 370));

    m_TurnPointsListA.push_back(TurnPoint1);
    m_TurnPointsListA.push_back(TurnPoint2);
    TurnPoint2->setNextTurnPoint(TurnPoint1);
    m_TurnPointsListA.push_back(TurnPoint3);
    TurnPoint3->setNextTurnPoint(TurnPoint2);
    m_TurnPointsListA.push_back(TurnPoint4);
    TurnPoint4->setNextTurnPoint(TurnPoint3);
    m_TurnPointsListA.push_back(TurnPoint5);
    TurnPoint5->setNextTurnPoint(TurnPoint4);
    m_TurnPointsListA.push_back(TurnPoint6);
    TurnPoint6->setNextTurnPoint(TurnPoint5);
    m_TurnPointsListA.push_back(TurnPoint7);
    TurnPoint7->setNextTurnPoint(TurnPoint6);
    m_TurnPointsListA.push_back(TurnPoint8);
    TurnPoint8->setNextTurnPoint(TurnPoint7);
    m_TurnPointsListA.push_back(TurnPoint9);
    TurnPoint9->setNextTurnPoint(TurnPoint8);
    m_TurnPointsListA.push_back(TurnPoint10);
    TurnPoint10->setNextTurnPoint(TurnPoint9);
    m_TurnPointsListA.push_back(TurnPoint11);
    TurnPoint11->setNextTurnPoint(TurnPoint10);
    m_TurnPointsListA.push_back(TurnPoint12);
    TurnPoint12->setNextTurnPoint(TurnPoint11);


    TurnPoint *bTurnPoint1 = new TurnPoint(QPoint(190, 540));
    TurnPoint *bTurnPoint2 = new TurnPoint(QPoint(355, 540));
    TurnPoint *bTurnPoint3 = new TurnPoint(QPoint(355, 370));
    TurnPoint *bTurnPoint4 = new TurnPoint(QPoint(430, 370));
    TurnPoint *bTurnPoint5 = new TurnPoint(QPoint(430, 200));
    TurnPoint *bTurnPoint6 = new TurnPoint(QPoint(575, 200));
    TurnPoint *bTurnPoint7 = new TurnPoint(QPoint(575, 370));
    TurnPoint *bTurnPoint8 = new TurnPoint(QPoint(650, 370));
    TurnPoint *bTurnPoint9 = new TurnPoint(QPoint(650, 540));
    TurnPoint *bTurnPoint10 = new TurnPoint(QPoint(800, 540));
    TurnPoint *bTurnPoint11 = new TurnPoint(QPoint(800, 370));
    TurnPoint *bTurnPoint12 = new TurnPoint(QPoint(880, 370));

    m_TurnPointsListB.push_back(bTurnPoint1);
    m_TurnPointsListB.push_back(bTurnPoint2);
    bTurnPoint2->setNextTurnPoint(bTurnPoint1);
    m_TurnPointsListB.push_back(bTurnPoint3);
    bTurnPoint3->setNextTurnPoint(bTurnPoint2);
    m_TurnPointsListB.push_back(bTurnPoint4);
    bTurnPoint4->setNextTurnPoint(bTurnPoint3);
    m_TurnPointsListB.push_back(bTurnPoint5);
    bTurnPoint5->setNextTurnPoint(bTurnPoint4);
    m_TurnPointsListB.push_back(bTurnPoint6);
    bTurnPoint6->setNextTurnPoint(bTurnPoint5);
    m_TurnPointsListB.push_back(bTurnPoint7);
    bTurnPoint7->setNextTurnPoint(bTurnPoint6);
    m_TurnPointsListB.push_back(bTurnPoint8);
    bTurnPoint8->setNextTurnPoint(bTurnPoint7);
    m_TurnPointsListB.push_back(bTurnPoint9);
    bTurnPoint9->setNextTurnPoint(bTurnPoint8);
    m_TurnPointsListB.push_back(bTurnPoint10);
    bTurnPoint10->setNextTurnPoint(bTurnPoint9);
    m_TurnPointsListB.push_back(bTurnPoint11);
    bTurnPoint11->setNextTurnPoint(bTurnPoint10);
    m_TurnPointsListB.push_back(bTurnPoint12);
    bTurnPoint12->setNextTurnPoint(bTurnPoint11);
}

void GameWidgetA::getHpDamage(int damage/* = 1*/)
{
    m_MusicPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void GameWidgetA::removedEnemy(Enemy *enemy)
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

void GameWidgetA::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void GameWidgetA::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void GameWidgetA::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void GameWidgetA::preLoadWavesInfo()
{
    m_waveslist.clear();
    if(level == 1){
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
    }else{
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

        m_waveslist.append(tlistA);
        m_waveslist.append(tlistC);
        m_waveslist.append(tlistB);
    }
}

bool GameWidgetA::loadWave()
{
    if (m_waves >= m_waveslist.size())
        return false;
    int ranenum = qrand()%2;
    TurnPoint *startTurnPoint;
    if(ranenum==0){
        startTurnPoint = m_TurnPointsListA.back();
    }else{
        startTurnPoint = m_TurnPointsListB.back();
    }
    for (int i = 0; i < m_waveslist.at(m_waves).size(); ++i)
    {
        int spawnTime = m_waveslist.at(m_waves).at(i).toInt();
        Enemy *enemy;
    //根据塔的数量设定敌人波数
        int randnum = qrand()%4;
        if(m_towersList.size()<4)
        {if(randnum == 0){
            enemy = new QEnemyTypeA(startTurnPoint, this);
        }if(randnum == 1){
            enemy = new QEnemyTypeB(startTurnPoint, this);
        }if(randnum == 2){
            enemy = new QEnemyTypeC(startTurnPoint, this);
        }if(randnum == 3){
            enemy = new QEnemyTypeD(startTurnPoint, this);
        }
        }
        else {
            if(randnum == 0||randnum==1){
                        enemy = new QEnemyTypeC(startTurnPoint, this);
                    }
            if(randnum == 2||randnum==3){
                        enemy = new QEnemyTypeD(startTurnPoint, this);
                    }
        }

        if(level == 1){
//            enemy->setEnemyData(100);//设置血量
        }else{
            enemy->setDifficulty(level);//设置血量和移动速度
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }
    return true;
}

QList<Enemy *> GameWidgetA::enemyList() const
{
    return m_enemyList;
}

void GameWidgetA::setLevel(int value)
{
    level = value;
    preLoadWavesInfo();
    loadTowerBases();
    addTurnPoints();
}

void GameWidgetA::gameStart()
{
    loadWave();
}

void GameWidgetA::mousePowerA()
{
    powerType = 1;
}

void GameWidgetA::mousePowerB()
{
    powerType = 2;
}

void GameWidgetA::mousePowerC()
{
    powerType = 3;
}

void GameWidgetA::upgradePower1()
{
    qDebug()<<"upgradePower1";
    for(int i = 0 ;i < m_towersList.size();i++){
        Tower* pTower = m_towersList.at(i);
        if (abs(pTower->retPointTower().x() - pressTowerPos.x()) < 20&&abs(pTower->retPointTower().y() - pressTowerPos.y()) < 20)
        {
            m_playrGold-=100;
            pTower->setTowerData(pTower->getTowerRange()+20);
//            qDebug()<<"ddddddddddddddddddddd";
        }
    }

}

void GameWidgetA::upgradePower2()
{
    qDebug()<<"upgradePower2"<<pressTowerPos;
    for(int i = 0 ;i < m_towersList.size();i++){
        Tower* pTower = m_towersList.at(i);
        if (abs(pTower->retPointTower().x() - pressTowerPos.x()) < 20&&abs(pTower->retPointTower().y() - pressTowerPos.y()) < 20)
        {
            m_playrGold-=200;
            pTower->setTowerData(pTower->getTowerRange()+10,pTower->getTowerDamage()+10);
//            qDebug()<<"ddddddddddddddddddddd";
        }
    }
}

void GameWidgetA::upgradePower3()
{
    qDebug()<<"upgradePower3"<<pressTowerPos;
    for(int i = 0 ;i < m_towersList.size();i++){
        Tower* pTower = m_towersList.at(i);
        if (abs(pTower->retPointTower().x() - pressTowerPos.x()) < 20&&abs(pTower->retPointTower().y() - pressTowerPos.y()) < 20)
        {
            m_playrGold-=300;
            if(pTower->getFireRate()>200)
            pTower->setTowerData(pTower->getTowerRange()+10,pTower->getTowerDamage()+5,pTower->getFireRate()-100);
            else {
                pTower->setTowerData(pTower->getTowerRange()+20,pTower->getTowerDamage()+10);
            }
//            qDebug()<<"ddddddddddddddddddddd";
        }
    }
}
void GameWidgetA::removedTower()
{
    qDebug()<<"upPower1";
    for(int i = 0 ;i < m_towersList.size();i++){
        Tower* pTower = m_towersList.at(i);
        if (abs(pTower->retPointTower().x() - pressTowerPos.x()) < 20&&abs(pTower->retPointTower().y() - pressTowerPos.y()) < 20)
        {
            m_playrGold+=100;
            Q_ASSERT(pTower);

            m_towersList.removeOne(pTower);
            delete pTower;
            break;
        }

    }
        auto it = m_TowerBasesList.begin();
               while (it != m_TowerBasesList.end())
               {
                   if (it->containPoint(pressTowerPos))
                   {
                       m_MusicPlayer->playSound(TowerPlaceSound);
                       it->setHasTower(false);

                   break;
                   }
                    ++it;
               }

           }



