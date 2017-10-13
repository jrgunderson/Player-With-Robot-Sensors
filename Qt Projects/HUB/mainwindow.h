#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <QThread>
#include <QStandardItemModel>
#include <QProcess>
#include <QtNetwork/QUdpSocket>
#include <QElapsedTimer>
#include <QTimer>
#include "taskallocator.h"
#include <QKeyEvent>
#include <QDir>
#include <QtCore>
#include <QtGui>
#include "optaskresp.h"
#include "remotecontrol.h"
#include "taskallocator.h"
#include "taskalowindow.h"
#include "communicator.h"
#include "errorwindow.h"
#include "communicatorwrapper.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
     void onWinnerFound(QList<Team>);
     void addToLog(QString s);
     //void missionComplete();
     void receiveBid(int rn, int s, double d);
     void receiveError(char *emsg);
     void teleopClosed();

private slots:

    void on_submitTaskButton_clicked();

    void on_taskAloButton_clicked();

    void on_slidAutSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void continueTaskAlo();

private:
    Ui::MainWindow *ui;
    QUdpSocket* socket;
    QElapsedTimer t;
    QTimer timer;
    int winnerB;
    int replys;
    bool stopped[3];
    bool manual[3];
    bool aPressed, wPressed, sPressed, dPressed;
    bool mStart;
    qint64 mTime;
};

#endif // MAINWINDOW_H


