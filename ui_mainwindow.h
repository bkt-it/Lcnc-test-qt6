/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *hal_cmd_5;
    QPushButton *hal_cmd_3;
    QPushButton *hal_cmd_2;
    QPushButton *hal_cmd_4;
    QPushButton *hal_cmd_1;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(354, 637);
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(1250, 900));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setMaximumSize(QSize(1240, 903));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        hal_cmd_5 = new QPushButton(centralWidget);
        hal_cmd_5->setObjectName("hal_cmd_5");
        hal_cmd_5->setGeometry(QRect(130, 540, 80, 60));
        hal_cmd_5->setBaseSize(QSize(192, 96));
        QFont font;
        font.setFamilies({QString::fromUtf8("DejaVu Sans")});
        font.setPointSize(20);
        font.setBold(true);
        hal_cmd_5->setFont(font);
        hal_cmd_5->setStyleSheet(QString::fromUtf8("QPushButton {font-weight: bold;color: black; border: 2px solid #1c5e12;border-radius: 5px;background: rgba(242, 242, 242, 150); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFD, stop: 0.2 #96ADB2);min-width: 41px;}\n"
"QPushButton:pressed{font-weight: bold;color: black;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #6F7E81, stop: 0.2 #DCF6FC);border-color: #27d404; border-width: 3px;}\n"
"QPushButton:flat {border: none;}\n"
"QPushButton:default { border-color: cyan;}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/aexit.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        hal_cmd_5->setIcon(icon);
        hal_cmd_5->setIconSize(QSize(48, 48));
        hal_cmd_3 = new QPushButton(centralWidget);
        hal_cmd_3->setObjectName("hal_cmd_3");
        hal_cmd_3->setGeometry(QRect(130, 460, 80, 60));
        hal_cmd_3->setBaseSize(QSize(192, 96));
        hal_cmd_3->setFont(font);
        hal_cmd_3->setStyleSheet(QString::fromUtf8("QPushButton {font-weight: bold;color: black; border: 2px solid #1c5e12;border-radius: 5px;background: rgba(242, 242, 242, 150); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFD, stop: 0.2 #96ADB2);min-width: 41px;}\n"
"QPushButton:pressed{font-weight: bold;color: black;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #6F7E81, stop: 0.2 #DCF6FC);border-color: #27d404; border-width: 3px;}\n"
"QPushButton:flat {border: none;}\n"
"QPushButton:default { border-color: cyan;}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/remote_ass.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        hal_cmd_3->setIcon(icon1);
        hal_cmd_3->setIconSize(QSize(48, 48));
        hal_cmd_2 = new QPushButton(centralWidget);
        hal_cmd_2->setObjectName("hal_cmd_2");
        hal_cmd_2->setGeometry(QRect(40, 460, 80, 60));
        hal_cmd_2->setBaseSize(QSize(192, 96));
        hal_cmd_2->setFont(font);
        hal_cmd_2->setStyleSheet(QString::fromUtf8("QPushButton {font-weight: bold;color: black; border: 2px solid #1c5e12;border-radius: 5px;background: rgba(242, 242, 242, 150); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFD, stop: 0.2 #96ADB2);min-width: 41px;}\n"
"QPushButton:pressed{font-weight: bold;color: black;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #6F7E81, stop: 0.2 #DCF6FC);border-color: #27d404; border-width: 3px;}\n"
"QPushButton:flat {border: none;}\n"
"QPushButton:default { border-color: cyan;}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/key.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        hal_cmd_2->setIcon(icon2);
        hal_cmd_2->setIconSize(QSize(48, 48));
        hal_cmd_4 = new QPushButton(centralWidget);
        hal_cmd_4->setObjectName("hal_cmd_4");
        hal_cmd_4->setEnabled(false);
        hal_cmd_4->setGeometry(QRect(40, 540, 80, 60));
        hal_cmd_4->setBaseSize(QSize(192, 96));
        hal_cmd_4->setFont(font);
        hal_cmd_4->setStyleSheet(QString::fromUtf8("QPushButton {font-weight: bold;color: black; border: 2px solid #1c5e12;border-radius: 5px;background: rgba(242, 242, 242, 150); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFD, stop: 0.2 #96ADB2);min-width: 41px;}\n"
"QPushButton:pressed{font-weight: bold;color: black;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #6F7E81, stop: 0.2 #DCF6FC);border-color: #27d404; border-width: 3px;}\n"
"QPushButton:flat {border: none;}\n"
"QPushButton:default { border-color: cyan;}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/shield_check.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/resources/shield_plus.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        icon3.addFile(QString::fromUtf8(":/resources/shield_check.svg"), QSize(), QIcon::Mode::Selected, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/resources/shield_plus.svg"), QSize(), QIcon::Mode::Selected, QIcon::State::On);
        hal_cmd_4->setIcon(icon3);
        hal_cmd_4->setIconSize(QSize(48, 48));
        hal_cmd_1 = new QPushButton(centralWidget);
        hal_cmd_1->setObjectName("hal_cmd_1");
        hal_cmd_1->setGeometry(QRect(40, 290, 111, 80));
        hal_cmd_1->setBaseSize(QSize(192, 96));
        hal_cmd_1->setFont(font);
        hal_cmd_1->setStyleSheet(QString::fromUtf8("QPushButton {font-weight: bold;color: black; border: 2px solid #1c5e12;border-radius: 5px;background: rgba(242, 242, 242, 150); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFD, stop: 0.2 #96ADB2);min-width: 41px;}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/emergency_stop"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        hal_cmd_1->setIcon(icon4);
        hal_cmd_1->setIconSize(QSize(64, 64));
        hal_cmd_1->setCheckable(false);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        hal_cmd_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        hal_cmd_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        hal_cmd_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        hal_cmd_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        hal_cmd_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
