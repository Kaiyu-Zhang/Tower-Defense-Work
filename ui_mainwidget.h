/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_b;
    QPushButton *pushButton_a;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(1024, 600);
        MainWidget->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\231\256\351\200\232\346\200\201*/\n"
"QPushButton\n"
"{\n"
"    /*\345\255\227\344\275\223\344\270\272\345\276\256\350\275\257\351\233\205\351\273\221*/\n"
"    font-family:Microsoft Yahei;\n"
"    /*\345\255\227\344\275\223\345\244\247\345\260\217\344\270\27220\347\202\271*/\n"
"    font-size:20pt;\n"
"    /*\345\255\227\344\275\223\351\242\234\350\211\262\344\270\272\347\231\275\350\211\262*/    \n"
"    color:white;\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(14 , 150 , 254);\n"
"    /*\350\276\271\346\241\206\345\234\206\350\247\222\345\215\212\345\276\204\344\270\2728\345\203\217\347\264\240*/ \n"
"    border-radius:8px;\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\345\201\234\347\225\231\346\200\201*/\n"
"QPushButton:hover\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(44 , 137 , 255);\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\200\201*/\n"
"QPushButton"
                        ":pressed\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(14 , 135 , 228);\n"
"    /*\345\267\246\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-left:3px;\n"
"    /*\344\270\212\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-top:3px;\n"
"}"));
        gridLayout_2 = new QGridLayout(MainWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 8, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 6, 7, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 4, 1, 1);

        pushButton_b = new QPushButton(MainWidget);
        pushButton_b->setObjectName(QString::fromUtf8("pushButton_b"));
        pushButton_b->setMinimumSize(QSize(120, 60));
        pushButton_b->setStyleSheet(QString::fromUtf8("border-image: url(:/image/button.jpg);"));

        gridLayout->addWidget(pushButton_b, 5, 4, 1, 1);

        pushButton_a = new QPushButton(MainWidget);
        pushButton_a->setObjectName(QString::fromUtf8("pushButton_a"));
        pushButton_a->setMinimumSize(QSize(120, 60));
        pushButton_a->setStyleSheet(QString::fromUtf8("border-image: url(:/image/button.jpg);"));

        gridLayout->addWidget(pushButton_a, 1, 4, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Form", nullptr));
        pushButton_b->setText(QApplication::translate("MainWidget", "Hard", nullptr));
        pushButton_a->setText(QApplication::translate("MainWidget", "Easy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
