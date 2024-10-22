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
//#include <QWebEngineView>

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


QString stringMdi;

QString relErr;
QString relErr_t;
QString pgrErr;
QString pgrErr_t;
QString outRelErr;
QString outRelErr_t;
QString outPgrErr;
QString outPgrErr_t;

QString txtwrite;
QString txtLOGwrite;
QString txtresult;
QString txt_plc_dint_00;
QString txt_plc_udint_00;

QString maxSx ="max_psx";
QString maxFalda = "max_falda";
QString maxH = "max_h";


QString txt_countUp;
QString txt_countDown;
//bool momBnt = false;

uint32_t            dim[3];
short               value = 0;
uint32_t            dataSize = 0;
uint16_t            bufsize;
uint32_t            out_numTags;
uint32_t            numTags;

int                 RCS_STAT_CHANNEL_STATE = 0;

RCS_STAT_CHANNEL    *stat_one;
RCS_CMD_CHANNEL     *cmd_one;
RCS_STAT_MSG        *msg_one;
// the NML channel for errors
static NML *emcErrorBuffer = 0;
static char error_string[NML_ERROR_LEN] = "";
bool momBnt = false;





//** Main::Window APP START ***********************************************************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hal_connection();

// ############################# start pgr ########################################

// ############################# start pgr ########################################

// ############################# start pgr ########################################




    //** CREATE RCS_STAT_CHANNEL *stat ****************************************************************
    const char *nmlfile = "/usr/share/linuxcnc/linuxcnc.nml";
    stat_one = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", nmlfile);
    txtwrite.append ("(8.0) STAT ready  \n");
    //ui->infoCnc->setText(txtwrite   +   "\n");

    if(!stat_one->valid()){
        //qDebug() << Q_FUNC_INFO << "... stat_one non è valido purtroppo ... RCS_STAT_CHANNEL ... ";
        QProcess procExit;
        procExit.start("/bin/bash", QStringList() << "-c" << "halrun -U");
        procExit.waitForFinished();
        QByteArray outputExit = procExit.readAll();
        procExit.close();
        /*m_help = new HelpHome();
        m_help->setWindowTitle(QApplication::translate("pas", "AVVISO UTENTE"));
        m_help->setWindowFlags(Qt::FramelessWindowHint);
        m_help->setAttribute(Qt::WA_AcceptTouchEvents);
        connect(this, SIGNAL(sendWarnMsgToUser(QByteArray)), m_help, SLOT(getWarningMsg(QByteArray)));
        emit sendWarnMsgToUser(outputExit);
        m_help->exec();*/
    }

    // //qDebug() << Q_FUNC_INFO << "ora proviamo a generare ... RCS_CMD_CHANNEL ... ";


    cmd_one = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", nmlfile);
    txtwrite.append ("(8.1) CMD ready  \n");
    //ui->infoCnc->setText(txtwrite   +   "\n");

    //qDebug() << Q_FUNC_INFO << "controlliamo stato cnc ... " << stat_one;



    //== UPDATE TIMER START =======================================================
   // cycles  =   0;
    // connect(&timer, SIGNAL(timeout()), this, SLOT (updateRandomNumber()));
    timer.start(50);
    if (timer.isActive())
    {
        // connect(&timer,SIGNAL(timeout()), this, SLOT(updnmlval()));
        //connect(&timer, SIGNAL(timeout()), this, SLOT(updateRandomNumber()));
    }

    //== UPDATE TIMER END ========================================================

    plc_timer.start(100);
    if (plc_timer.isActive())
    {
        //qDebug() << Q_FUNC_INFO << "plc_timer ... " << plc_timer.isActive();
        connect(&plc_timer,SIGNAL(timeout()), this, SLOT(updateLcecIn()));
    }




    connect(ui->hal_cmd_1, SIGNAL(pressed()), this, SLOT(momentaryBnt_hal_ON()));
    connect(ui->hal_cmd_1, SIGNAL(released()), this, SLOT(momentaryBnt_hal_OFF()));



    connect(ui->hal_cmd_2, SIGNAL(toggled(bool)), this, SLOT(toggleBnt_hal(bool)));
    connect(ui->hal_cmd_3, SIGNAL(toggled(bool)), this, SLOT(toggleBnt_hal(bool)));


    connect(ui->hal_cmd_5, SIGNAL(released()), this, SLOT(changeFloatVal()));









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
    qDebug() << Q_FUNC_INFO << "name Toggle received  :" << pepper;
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


    qDebug() << Q_FUNC_INFO << "name Press received  :" << pepperOn;
}

void MainWindow::momentaryBnt_hal_OFF(){
    QPushButton *btnOff = dynamic_cast<QPushButton*>(sender());
    QString pepperOff = btnOff->objectName().toLower();
    momBnt = false;
    set_CL_I20_OnOff(momBnt, pepperOff);
    //ui->led_11->LVexchange(false);
    //ui->wled_1->setState(false);

   qDebug() << Q_FUNC_INFO << "name Release received  :" << pepperOff;
}


void MainWindow::updnmlval()
{


    if(!stat_one->valid()){
        txtwrite.append ("(9.0) INVALID STAT \n");
       // ui->infoCnc->setText(txtwrite   +   "\n");
    }



    if(stat_one->valid())
    {
        if(stat_one->peek() == EMC_STAT_TYPE)
        {
            EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat_one->get_address());
            /*
//Returns double obj containing the CMD pos in ABS coords,
        double xAxisPosAbsCMD = emcStatus->motion.traj.position.tran.x;
        double yAxisPosAbsCMD = emcStatus->motion.traj.position.tran.y;
        double zAxisPosAbsCMD = emcStatus->motion.traj.position.tran.z;

//Returns double obj containing the CMD pos in REL coords,
        double xAxisPosRelCMD = (emcStatus->motion.traj.position.tran.x -
                               emcStatus->task.g5x_offset.tran.x -
                               emcStatus->task.g92_offset.tran.x -
                               emcStatus->task.toolOffset.tran.x);

//Returns double objs containing the ACT pos in REL coords,
        double xAxisPosRelACT = (emcStatus->motion.traj.actualPosition.tran.x -
                                       emcStatus->task.g5x_offset.tran.x -
                                       emcStatus->task.g92_offset.tran.x -
                                       emcStatus->task.toolOffset.tran.x);

        double yAxisPosRelACT = (emcStatus->motion.traj.actualPosition.tran.y -
                                       emcStatus->task.g5x_offset.tran.y -
                                       emcStatus->task.g92_offset.tran.y -
                                       emcStatus->task.toolOffset.tran.y);

      //  double zAxisPosRelACT = (emcStatus->motion.traj.actualPosition.tran.z -
                          //     emcStatus->task.g5x_offset.tran.z -
                          //     emcStatus->task.g92_offset.tran.z -
                          //     emcStatus->task.toolOffset.tran.z);

//Returns double objs containing the ACT pos in ABS coords,
        double xAxisPosAbsACT = emcStatus->motion.traj.actualPosition.tran.x;
        double yAxisPosAbsACT = emcStatus->motion.traj.actualPosition.tran.y;
        double zAxisPosAbsACT = emcStatus->motion.traj.actualPosition.tran.z;

//Returns double obj containing Total distance_to_go,
        double allAxisDTG = emcStatus->motion.traj.distance_to_go;

//Returns double obj containing dtg x|y|..... ,
        double  xAxisDTG  = emcStatus->motion.traj.dtg.tran.x;
        double  yAxisDTG  = emcStatus->motion.traj.dtg.tran.y;
        double  zAxisDTG  = emcStatus->motion.traj.dtg.tran.z;

      //  double aAxisDTG = emcStatus->motion.traj.dtg.a;
      //  double bAxisDTG = emcStatus->motion.traj.dtg.b;
       // double cAxisDTG = emcStatus->motion.traj.dtg.c;

*/
            /*ui->lbl_X_AxisPosAct->setText( QString::number(xAxisPosAbsACT, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Y_AxisPosAct->setText( QString().setNum(yAxisPosAbsACT, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Z_AxisPosAct->setText( QString().setNum(zAxisPosAbsACT, 'f', 4) ); //setNum(num, 'g', 3) );

        ui->lbl_X_AxisPosCMD->setText( QString::number(xAxisPosAbsCMD, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Y_AxisPosCMD->setText( QString::number(yAxisPosAbsCMD, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Z_AxisPosCMD->setText( QString::number(zAxisPosAbsCMD, 'f', 4) ); //setNum(num, 'g', 3) );

        ui->lbl_AllAxisDTG->setText( QString().setNum(allAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_X_AxisDTG->setText( QString().setNum(xAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Y_AxisDTG->setText( QString().setNum(yAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );
        ui->lbl_Z_AxisDTG->setText( QString().setNum(zAxisDTG, 'f', 4) ); //setNum(num, 'g', 3) );*/


        }
    }
}


void MainWindow::motPinOn(int idOn)
{
    EMC_MOTION_SET_DOUT dout;
    dout.now=1;
    dout.index=idOn;
    dout.start=1;
    dout.end=0;
    cmd_one->write(&dout);
    //qDebug() << Q_FUNC_INFO << "Pin " << idOn << " on";

    //hal_ready(1);
    //char * hal_comp_name(1);

}

void MainWindow::motPinOff(int idOff)
{
    EMC_MOTION_SET_DOUT dout;
    dout.now=1;
    dout.index=idOff;
    dout.start=0;
    dout.end=1;
    cmd_one->write(&dout);
    //qDebug() << Q_FUNC_INFO << "Pin " <<  idOff << " off";
}



void MainWindow::updateLcecIn(){

    int plcInNr = 0;
    int plcHMI = 0;
    int plcJK = 0;
    float valK =0;
    int lcdValueK = 0;
    float valW =0;
    int lcdValueW = 0;
    int tmpCount = 0;

    QString plcInC;
    QString ledInC;
    QString xMotor;
    QString yMotor;
    QString zMotor;
    QString aMotor;
    QString xMotorT;
    QString yMotorT;
    QString zMotorT;
    QString aMotorT;

    bool testOut = false;



    //qDebug() << Q_FUNC_INFO << " ... entrato in update lcec ... ";


    /**********************************************************/
    /* SCAN INPUT in lcec.0.1.din-1...                        */
    /**********************************************************/
   /* for(plcInNr=0; plcInNr<8; plcInNr++)
    {
        plcInC = "in" + QString::number(plcInNr);
        ledInC = "wled_PLC_0_" + QString::number(plcInNr);
        WLED * lbl = this->findChild<WLED *>(ledInC);
        if(get_PLC_input(plcInC) != -1){
            if(get_PLC_input(plcInC) == 1){ if(lbl)lbl->setState(true);}
            else{ if(lbl)lbl->setState(false);}
        }
    }*/
    //qDebug() << Q_FUNC_INFO << "abbiamo wled_PLC_0_"  << ledInC;
    plcInNr=0;

    /*****************************************/
    /* SCAN OUTPUT out10 lcec.0.3.dout-1 ... */
    /*****************************************/
   /* for(plcInNr=0; plcInNr<8; plcInNr++)
    {
        if(plcInNr==0){plcInC = "out1" + QString::number(plcInNr) + "a";}
        else{plcInC = "out1" + QString::number(plcInNr);}
        ledInC = "wled_PLCO_0_" + QString::number(plcInNr);
        WLED * lbl = this->findChild<WLED *>(ledInC);
        if(get_PLC_input(plcInC) != -1){
            if(get_PLC_input(plcInC) == 1){ if(lbl)lbl->setState(true);}
            else{ if(lbl)lbl->setState(false);}
        }

    }*/



}

void MainWindow::changeFloatVal(){
    float pirl = 0;
    QString text =ui->hal_float->text();

    // Convert the text to a float
    bool ok;
    pirl = text.toFloat(&ok);

    // Check if the conversion was successful
    if (ok) {
        // Format the float to 3 decimal places
        QString formattedValue = QString::number(pirl, 'f', 3);

        // Print the formatted value
        qDebug() << "Converted value (3 decimal places):" << formattedValue;
    } else {
        qDebug() << "Error: Could not convert text to float.";
    }

    updateFval(pirl);
}

void MainWindow::updateFval(float val1){
    if(set_pin_FLOAT_calc(val1, maxFalda) > 10){
        qDebug() << Q_FUNC_INFO << "func INPUT FLOAT " << val1 << "  &  " << maxFalda << " have some problem  ;";
    }
}




