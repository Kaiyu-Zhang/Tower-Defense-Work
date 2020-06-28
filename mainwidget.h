#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
        virtual void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_a_clicked();

    void on_pushButton_b_clicked();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
