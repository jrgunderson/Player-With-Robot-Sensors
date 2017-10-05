#include "driver.h"
#include <QThread>
#include <QDebug>

Communicator* com;
QThread receiveThread;

Driver::Driver(QObject *parent)
    : QObject(parent)
{
    char ip1[] = "192.168.0.14"; //Robot 1 or Other Robot
    char ip2[] = "192.168.0.14"; //Robot 2 or Phone
    char ip3[] = "192.168.0.14"; //Desktop

    com = new Communicator(ip1,ip2,ip3, 6665);
    com->moveToThread(&receiveThread);
    receiveThread.start();

    connect(&receiveThread,SIGNAL(started()),
            com,SLOT(startListen()));
    qDebug() << receiveThread.isRunning();
    com->send_Ready();
    sleep(10);
    com->send_Task();
    sleep(10);
    com->send_Bid(1,5,12);
}
