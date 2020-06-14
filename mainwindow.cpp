#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<QPainter>
#include<QMouseEvent>
#include"checkpoints.h"
#include<iostream>
#include <QObject>
#include "bullet.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCheckPoints();
    this->loadEnemy();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    waves=0;
}
bool MainWindow:: canBuy() const
{
    return true;
}
void MainWindow::loadTowerbase()
{
    QPoint pos[] =
        {
//            QPoint(100, 900),
//            QPoint(400, 900),
            QPoint(700, 900),
            QPoint(1000, 900),
            QPoint(1300,900),

//            QPoint(150, 550),
//            QPoint(450, 550),
            QPoint(750, 550),
            QPoint(1050, 550),
            QPoint(1350,550),

            QPoint(150, 300),
            QPoint(450, 300),
            QPoint(750, 300),
            QPoint(1050, 300),
            QPoint(1350,300),

            QPoint(100, 50),
            QPoint(400, 50),
            QPoint(700, 50),
            QPoint(1000, 50),
            QPoint(1300,50),
        };
        int len	= sizeof(pos) / sizeof(pos[0]);
        int i;
        for (i = 0; i < len; i++)
           { baselist.push_back(pos[i]);}


}

void MainWindow::setCheckPoints()
{
    Checkpoints *Checkpoints1 = new Checkpoints(QPoint(1500, 750));
    CheckpointsList.push_back(Checkpoints1);

    Checkpoints *Checkpoints2 = new Checkpoints(QPoint(700, 750));
    CheckpointsList.push_back(Checkpoints2);
    Checkpoints2->setNextCheckpoint(Checkpoints1);

    Checkpoints *Checkpoints3 = new Checkpoints(QPoint(700, 450));
    CheckpointsList.push_back(Checkpoints3);
    Checkpoints3->setNextCheckpoint(Checkpoints2);

    Checkpoints *Checkpoints4 = new Checkpoints(QPoint(1500, 450));
    CheckpointsList.push_back(Checkpoints4);
    Checkpoints4->setNextCheckpoint(Checkpoints3);

    Checkpoints *Checkpoints5 = new Checkpoints(QPoint(1500, 225));
    CheckpointsList.push_back(Checkpoints5);
    Checkpoints5->setNextCheckpoint(Checkpoints4);

    Checkpoints *Checkpoints6 = new Checkpoints(QPoint(100, 225));
    CheckpointsList.push_back(Checkpoints6);
    Checkpoints6->setNextCheckpoint(Checkpoints5);

    }
void MainWindow::getHpDamage(int damage/* = 1*/)
{
    // 暂时空实现，以后这里进行基地费血行为
}
void MainWindow::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    enemylist.removeOne(enemy);
    delete enemy;
    if (enemylist.empty())
    {
        ++waves; // 当前波数加1
        // 继续读取下一波
        if (gameWin)
        {
            // 当没有下一波时，这里表示游戏胜利
            // 设置游戏胜利标志为true
             return;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}
void MainWindow::updateMap()
{
    foreach (Enemy *enemy, enemylist)
       enemy->move();
    foreach(Tower* tower,towerlist)
        tower->checkEnemyInRange();
    update();
}

void MainWindow::loadEnemy()
{
    if (waves >= 6)
       gameWin=true;
    //这里要注意
    Checkpoints *startCheckpoints = CheckpointsList.back();

    int enemyStartInterval[] = { 100, 800, 1600, 3000, 5000, 8000 };
    for (int i = 0; i < 6; i++)
    {
        Enemy *enemy = new Enemy(startCheckpoints,this);
        enemylist.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(enable()));
    }

}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //购买塔
    QPoint pressPos = event->pos();
    if(event->button()==Qt::LeftButton)
    {
        auto it = baselist.begin();
        while (it != baselist.end())
    {
        if (canBuy() && it->inrange(pressPos) && !it->havetower())
        {
            it->setHaveTower();
//			Tower *tower = new Tower(it->center(), this);

            Tower *tower = new Tower(it->center(),this);
            towerlist.push_back(tower);
            update();
            break;
        }

        it++;
    }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/image/background1.jpg"));
    int i;
    for(i=0;i<baselist.length();i++)
    {
        baselist[i].show(&painter);

    }
    foreach(Tower *tower,towerlist)
    {
        tower->show(&painter);
    }
    foreach(Checkpoints* check,CheckpointsList)
    {
        check->show(&painter);

    }

    foreach(Enemy* enemy,enemylist)
    {
        enemy->show(&painter);

    }
    foreach (Bullet * bullet,bulletlist)
    {
        bullet->draw(&painter);
        cout<<"is";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QList <Enemy*> MainWindow:: getenemylist() const
{
    return  enemylist;
}
void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    enemylist.removeOne(enemy);
    delete enemy;

    if (enemylist.empty())
    {
        ++waves;
        if (!gameWin)
        {
            gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    bulletlist.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    bulletlist.push_back(bullet);
}
