#include "communicatorwrapper.h"

CommunicatorWrapper::CommunicatorWrapper(char *ip1, char *ip2, char *ip3, int portnum)
{
    /*ip_addr1 = ip1;
    ip_addr2 = ip2;
    ip_addr3 = ip3;
    port = portnum;*/

    sender.init(ip1,ip2,ip3,port);
    receiver.init(ip1,ip2,ip3,port);
    connectReceiver();
    receiver.moveToThread(&receiveThread);
    receiveThread.start();
    connect(&receiveThread, SIGNAL(started()),
            &receiver, SLOT(startListen()));
}
void CommunicatorWrapper::connectReceiver(){
    connect(&receiver, SIGNAL(bidReceived(int,int,double)),
            this, SLOT(receiveBid(int,int,int)));
    connect(&receiver, SIGNAL(errorReceived(char*)),
            this, SLOT(receiveError(char*)));
    connect(&receiver, SIGNAL(moveReceived(int)),
            this, SLOT(receiveMove(int)));
    connect(&receiver, SIGNAL(readyReceived()),
            this, SLOT(receiveReady()));
    connect(&receiver, SIGNAL(startReceived()),
            this, SLOT(receiveReady()));
    connect(&receiver, SIGNAL(startReceived()),
            this, SLOT(receiveStart()));
    connect(&receiver, SIGNAL(taskReceived()),
            this, SLOT(receiveTask()));
}

void CommunicatorWrapper::sendBid(int rn, int str, double dist){
    sender.send_Bid(rn,str,dist);
}
void CommunicatorWrapper::sendError(char *emsg){
    sender.send_Error(emsg);
}
void CommunicatorWrapper::sendMove(int i, int m){
    sender.send_Move(i,m);
}
void CommunicatorWrapper::sendReady(){
    sender.send_Ready();
}
void CommunicatorWrapper::sendStart(){
    sender.send_Start();
}
void CommunicatorWrapper::sendTask(){
    sender.send_Task();
}
void CommunicatorWrapper::receiveBid(int rn, int str, double dist){
    emit(newBid(rn,str,dist));
}
void CommunicatorWrapper::receiveError(char *msg){
    emit(newError(msg));
}
void CommunicatorWrapper::receiveMove(int m){
    emit(newMove(m));
}
void CommunicatorWrapper::receiveReady(){
    emit(ready());
}
void CommunicatorWrapper::receiveStart(){
    emit(start());
}
void CommunicatorWrapper::receiveTask(){
    emit(newTask());
}
