#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <QDebug>

using namespace std;

class Communicator : public QObject
{
    Q_OBJECT

public:
    Communicator(char * ip, int p);
    void send_cmd(int sfd, char *msg);
    void parse_msg(char *msg);
    void send_Bid(int rn, int str, int dist);
    void send_Ready();
    void send_Help();
    void send_Task();
    void send_Start(int e);
    void send_Success();
    void send_Error(char *emsg);
    void send_Move(int i);
    int getMove();
    bool getStart();
    bool errorStart();
    bool getReady();
    bool getError();
    bool getHelp();
    bool getSuccess();
    int port;

private:

signals:
    void bidReceived(int rn, int s, int d);
    void taskReceived();
    void startReceived();
    void readyReceived();
    void errorReceived(char *emsg);
    void moveReceived(int m);
    void helpReceived();
    void successReceived();
public slots:
    void startListen();
    void startSpeak();
};

#endif // COMMUNICATOR_H
