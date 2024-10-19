#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include <QScreen>
#include <QIcon>
#include <QGuiApplication>
#include <QGuiApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.resize(35,600);
    //w.move(( scr.center() - rect().center() ));
    w.show();



    return a.exec();


}
