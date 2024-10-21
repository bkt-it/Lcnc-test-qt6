#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "QTimer"
#include "QtCore"
#include "QtGui"
#include "QTreeWidget"
#include "QTreeWidgetItem"


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
#include "hal_priv.h"
#include <QTime>
#include <QTimeEdit>
#include <QDateEdit>
#include <QDateTime>
#include <QProcess>


#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>

#include <stdlib.h>




#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QRegularExpressionMatch>


#include <QtCore/QRandomGenerator>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QPieSeries>
#include <QStatusBar>
#include <QChartView>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlRelation>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <memory>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRelationalDelegate>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlTableModel>
#include <QtWidgets>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork>
#include <QKeyEvent>
#include <QInputDialog>

//
//#include <QtWebEngineWidgets>
//#include <QtWebEngineCore>
//#include <QtWebView/QtWebView>



#include <unistd.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
   // void addTreeRoot(QString tagNumber, QString tagName, QString tagType);
  //  void addTreeChild(QTreeWidgetItem *parent, QString name, QString Description, QString tagType );


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer timer;
    QTimer plc_timer;
    QTimer ethercat_timer;
    QTimer infoCPU_timer;




public slots:


        void setCL_On(QString nameBitOn);
        void setCL_Off(QString nameBitOff);
        void setCL_OnTimeOff(QString nameBitOnOff, int shoTime);
        void setCL_On500Off(QString nameBNT);
        void setCL_On500OffnoName();
        void setCL_OnOff_named_bool(QString namePIN, bool valPIN);
        void toggleBnt_hal(bool pressVal);
        void momentaryBnt_hal_ON();
        void momentaryBnt_hal_OFF();
        void updateFval(float val1);
        void updateLcecIn();
        void motPinOn(int idOn);
        void motPinOff(int idOff);
        void updnmlval();







private slots:


private:
    Ui::MainWindow *ui;





protected:


signals:



};

#endif // MAINWINDOW_H
