#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <QDebug>

class Communicator : public QObject
{
    Q_OBJECT

public:
    Communicator(char * ip1,char * ip2,char * ip3, int p);
    void send_cmd(int sfd, char *msg);
    void parse_msg(char *msg);
    void send_Bid(int rn, int str, int dist);
    void send_Ready();
    void send_Task();
    void send_Start();
    void send_Error(char *emsg);
    void send_Move(int i, int m);
    int port;

private:

signals:
    void bidReceived(int rn, int s, int d);
    void taskReceived();
    void startReceived();
    void readyReceived();
    void errorReceived(char *emsg);
    void moveReceived(int m);
public slots:
    void startListen();
};

#endif // COMMUNICATOR_H
