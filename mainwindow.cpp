#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "get_command.h"
#include "send_command.h"


#include <stdlib.h>

#include <QPushButton>
#include <QFileDialog>
#include <QBuffer>
#include <QtCore/QDebug>
#include <QTime>
#include <QThread>
#include <QTextStream>
#include <QMessageBox>
#include <QLCDNumber>
#include <QProcess>
#include <QString>
#include <QWidgetList>
#include <QTreeWidget>
#include <QLabel>
#include <QFrame>
#include <QRandomGenerator>
#include <QDialog>
#include <QVector>
#include <QtWidgets>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork>
#include <QWebEngineView>

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QRegularExpressionMatch>




#include <QTextBrowser>
#include <qstring.h>
#include <stdlib.h>
#include <tuple>
#include <unistd.h>
#include <cmath>
#include <cstdlib>

// For user space HAL RTAPI
#ifdef RTAPI
#undef RTAPI
#endif

#ifndef ULAPI
#define ULAPI
#endif

#include "emc.hh"
#include "emc_nml.hh"
#include "emcIniFile.hh"
#include "emcpos.h"
#include "hal.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include "motion.h"
#include "inifile.h"
#include "iniaxis.hh"
#include "inifile.hh"
#include "inihal.hh"
#include "nml_oi.hh"





//QT_CHARTS_USE_NAMESPAC


#define ARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define _tprintf printf




#define PI 3.141592

bool momBnt = false;



//** Main::Window APP START ***********************************************************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



// ############################# start pgr ########################################

// ############################# start pgr ########################################

// ############################# start pgr ########################################






}
//** Main::Window APP END *************************************************************************







MainWindow::~MainWindow()
{
    delete ui;
}


/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/
/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/
/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/


/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/
/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/
/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/

/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/
/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/
/*----------------------------------  OPCUA SERVER DATA CALL start  ---------------------------------*/






void MainWindow::setCL_On500OffnoName(){

    QPushButton *btOff = dynamic_cast<QPushButton*>(sender());
    QString ppOff = btOff->objectName().toLower();
    //momBnt = false;
    set_CL_I20_OnOff(true, ppOff);
    QTimer::singleShot(500, this, SLOT(set_CL_I20_OnOff(false, ppOff)));
}


void MainWindow::setCL_On500Off(QString nameBNT){

    //QPushButton *btOff = dynamic_cast<QPushButton*>(sender());
    //QString ppOff = btOff->objectName().toLower();
    //momBnt = false;
    set_CL_I20_OnOff(true, nameBNT);
    //QTimer::singleShot(500, this, SLOT(set_CL_I20_OnOff(false, nameBNT)));
    QTimer::singleShot(500, this, [nameBNT] () {
            set_CL_I20_OnOff(false, nameBNT);
        });
}

void MainWindow::setCL_OnTimeOff(QString nameBitOnOff, int shoTime){

    set_CL_I20_OnOff(true, nameBitOnOff);

    QTimer::singleShot(shoTime, this, [nameBitOnOff] () {
            set_CL_I20_OnOff(false, nameBitOnOff);
        });
   /* QTimer::singleShot(shoTime*1, [this, set_CL_I20_OnOff(false, nameBitOnOff)](){on_snoozeTimeout(selectedData);});
    QTimer::singleShot(shoTime, this, SLOT(set_CL_I20_OnOff(false, nameBitOnOff)));*/
}


void MainWindow::setCL_On(QString nameBitOn){
    set_CL_I20_OnOff(true, nameBitOn);
}
void MainWindow::setCL_Off(QString nameBitOff){
    set_CL_I20_OnOff(false, nameBitOff);
}

void MainWindow::setCL_OnOff_named_bool(QString namePIN, bool valPIN){
    set_CL_I20_OnOff(valPIN, namePIN);
}


void MainWindow::toggleBnt_hal(bool pressVal) //, QString pepper)
{
    //QPushButton *btnAny = dynamic_cast<QPushButton*>(sender());
    //QString pbAny = btnAny->objectName();
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());
    QString pepper = btn->objectName();
    //qDebug() << Q_FUNC_INFO << "name Toggle received  :" << pepper;
    //QString pepper = "in10"; //"lcec.0.4.dout-7";  //"in10";
    set_CL_I20_OnOff(pressVal, pepper);
}

void MainWindow::momentaryBnt_hal_ON(){
    QPushButton *btnOn = dynamic_cast<QPushButton*>(sender());
    QString pepperOn = btnOn->objectName().toLower();
    momBnt = true;
    set_CL_I20_OnOff(momBnt, pepperOn);
    //ui->led_11->LVexchange(true);
    //ui->wled_1->setState(true);


    ////qDebug() << Q_FUNC_INFO << "name Press received  :" << pepperOn;
}

void MainWindow::momentaryBnt_hal_OFF(){
    QPushButton *btnOff = dynamic_cast<QPushButton*>(sender());
    QString pepperOff = btnOff->objectName().toLower();
    momBnt = false;
    set_CL_I20_OnOff(momBnt, pepperOff);
    //ui->led_11->LVexchange(false);
    //ui->wled_1->setState(false);

   // //qDebug() << Q_FUNC_INFO << "name Release received  :" << pepperOff;
}
