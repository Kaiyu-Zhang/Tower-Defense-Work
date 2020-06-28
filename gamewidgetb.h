#ifndef GAMEWIDGETB_H
#define GAMEWIDGETB_H

#include <QWidget>

namespace Ui {
class GameWidgetB;
}

class GameWidgetB : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidgetB(QWidget *parent = nullptr);
    ~GameWidgetB();
protected:
        virtual void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_a_clicked();

    void on_pushButton_b_clicked();
private:
    Ui::GameWidgetB *ui;
    int g_gamelevel=2;
};

#endif // GAMEWIDGETB_H

