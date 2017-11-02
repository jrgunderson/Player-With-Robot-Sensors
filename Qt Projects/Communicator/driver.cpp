#include "driver.h"

char ip1[] = "10.110.253.62"; //Robot 1 or Other Robot
char ip2[] = "10.110.253.62"; //Robot 2 or Phone
char ip3[] = "10.110.253.62"; //Desktop
int port = 4950; // needs to be the same
thread* listen_thread;
thread* talk_thread;
Communicator* com;

// default constructor: for Robot
Driver::Driver()
{
      com = new Communicator(ip1,ip2,ip3, port);

      listen_thread = new std::thread(&Driver::Listen, this);
      sleep(1); // a quick delay to space out threads

      talk_thread = new std::thread(&Driver::Speak, this);
}


// constructor for Hub
Driver::Driver(int i)
{
    com = new Communicator(ip1,ip2,ip3, port);

    listen_thread = new std::thread(&Driver::Listen, this);
    sleep(1); // a quick delay to space out threads

    talk_thread = new std::thread(&Driver::Command, this);
}

// For anyone
void Driver::Listen()
{
    com->startListen();
}

// For Robot
void Driver::Speak()
{
    com->send_Ready();
}

// For Robot
void Driver::Error()
{
    com->send_Error("Error");
}

// For Hub
void Driver::Command()
{
    com->send_Move(0, "Move Right"); // send Robot 1 Right
    com->send_Move(1, "Move Left"); // send Robot 2 Left
}
