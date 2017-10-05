#ifndef COMMUNICATORWRAPPER_H
#define COMMUNICATORWRAPPER_H

#include <QObject>
#include <communicator.h>
#include <QThread>

class CommunicatorWrapper : public QObject
{
    Q_OBJECT
public:
    CommunicatorWrapper(char *ip1, char *ip2, char *ip3, int portnum);

private:
    int port;
    char *ip_addr1;
    char *ip_addr2;
    char *ip_addr3;
    Communicator sender;
    Communicator receiver;
    QThread receiveThread;
    void connectReceiver();


signals:
    void ready();
    void newTask();
    void start();
    void newError(char *emsg);
    void newMove(int m);
    void newBid(int rn, int str, double d);

public slots:
    //Sending
    void sendReady();
    void sendTask();
    void sendStart();
    void sendError(char *emsg);
    void sendMove(int i, int m);
    void sendBid(int rn, int str, double dist);

    //Receiving
    void receiveReady();
    void receiveTask();
    void receiveStart();
    void receiveError(char *msg);
    void receiveMove(int m);
    void receiveBid(int rn, int str, double dist);

};

#endif // COMMUNICATORWRAPPER_H
