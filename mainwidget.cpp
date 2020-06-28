#include "mainwidget.h"
#include "gamewidgeta.h"
#include "ui_mainwidget.h"
#include <QPainter>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("Tower Defense");
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/start.jpg");
    pix = pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void MainWidget::on_pushButton_a_clicked()
{
    GameWidgetA w;
    w.setLevel(1);
    w.exec();
    this->hide();
    this->close();
}

void MainWidget::on_pushButton_b_clicked()
{
    GameWidgetA w;
    w.setLevel(2);
    w.exec();
    this->hide();
    this->close();
}
