/********************************************************************************
** Form generated from reading UI file 'gamewidgetb.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGETB_H
#define UI_GAMEWIDGETB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWidgetB
{
public:
    QPushButton *pushButton_a;
    QPushButton *pushButton_b;

    void setupUi(QWidget *GameWidgetB)
    {
        if (GameWidgetB->objectName().isEmpty())
            GameWidgetB->setObjectName(QString::fromUtf8("GameWidgetB"));
        GameWidgetB->resize(1000, 600);
        pushButton_a = new QPushButton(GameWidgetB);
        pushButton_a->setObjectName(QString::fromUtf8("pushButton_a"));
        pushButton_a->setGeometry(QRect(420, 340, 161, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(16);
        pushButton_a->setFont(font);
        pushButton_a->setStyleSheet(QString::fromUtf8("Color: white;\n"
"border-image: url(:/image/button.jpg);"));
        pushButton_b = new QPushButton(GameWidgetB);
        pushButton_b->setObjectName(QString::fromUtf8("pushButton_b"));
        pushButton_b->setGeometry(QRect(420, 440, 161, 61));
        pushButton_b->setFont(font);
        pushButton_b->setStyleSheet(QString::fromUtf8("Color: white;\n"
"border-image: url(:/image/button.jpg);"));

        retranslateUi(GameWidgetB);

        QMetaObject::connectSlotsByName(GameWidgetB);
    } // setupUi

    void retranslateUi(QWidget *GameWidgetB)
    {
        GameWidgetB->setWindowTitle(QApplication::translate("GameWidgetB", "Form", nullptr));
        pushButton_a->setText(QApplication::translate("GameWidgetB", "\346\214\221\346\210\230\344\270\213\344\270\200\345\205\263", nullptr));
        pushButton_b->setText(QApplication::translate("GameWidgetB", "\347\273\223\346\235\237\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWidgetB: public Ui_GameWidgetB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGETB_H
