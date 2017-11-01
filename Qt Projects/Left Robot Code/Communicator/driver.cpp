#include "driver.h"

//pthread_t thread[2];
char ip1[] = "192.168.0.12"; //Robot 1 or Other Robot
char ip2[] = "192.168.0.12"; //Robot 2 or Phone
char ip3[] = "192.168.0.12"; //Desktop
int port = 4950; // needs to be the same


Driver::Driver()
{
      thread* thread1 = new std::thread(&Driver::Listen, this);
      sleep(1); // a quick delay is necessary
      thread* thread2 = new std::thread(&Driver::Speak, this);
      sleep(10); //otherwise constructor completes before thread2 has the chance to speak

}

void Driver::Listen()
{
    Communicator* com;

    cout << "Listen Thread Created..." << endl;

    com = new Communicator(ip1,ip2,ip3, port);
    com->startListen();

    cout << "listen over" << endl;

}

void Driver::Speak()
{
    Communicator* com;

    cout << "Speak Thread Created..." << endl;

    com = new Communicator(ip1,ip2,ip3, port);
    com->send_Ready();
    sleep(3);
    com->send_Task();
    sleep(3);
    com->send_Bid(1,5,12);

    cout << "speak over" << endl;
}
