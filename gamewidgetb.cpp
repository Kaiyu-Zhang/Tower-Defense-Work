#include "gamewidgetb.h"
#include "ui_gamewidgetb.h"
#include<QPainter>
#include"gamewidgeta.h"
GameWidgetB::GameWidgetB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidgetB)
{
    ui->setupUi(this);
    setWindowTitle("Tower Defense");
}

GameWidgetB::~GameWidgetB()
{
    delete ui;
}

void GameWidgetB::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/victory.jpg");
    pix = pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void GameWidgetB::on_pushButton_a_clicked()
{
    GameWidgetA* w2=new GameWidgetA;
    qApp->closeAllWindows();
    g_gamelevel++;
    w2->setLevel(g_gamelevel);
    w2->exec();
//    this->close();
    w2->show();
}

void GameWidgetB::on_pushButton_b_clicked()
{
   qApp->quit();

}
