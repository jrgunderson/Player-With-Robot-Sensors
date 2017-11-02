#include "driver.h"

char ip1[] = "10.42.0.99";
char ip2[] = "10.42.0.99";
char ip3[] = "10.42.0.42"; // Robot1
thread* listen_thread;
thread* talk_thread;
Communicator* lcom;
Communicator* tcom;
Communicator* tlcom;
Communicator* trcom;

// default constructor: for Robot
Driver::Driver()
{
      lcom = new Communicator(ip1,ip2,ip3, 4950);
      listen_thread = new std::thread(&Driver::Listen, this);
      sleep(1); // a quick delay to space out threads

      tcom = new Communicator(ip1,ip2,ip3, 4951);
      talk_thread = new std::thread(&Driver::Speak, this);
}


// constructor for Hub
Driver::Driver(int i)
{
    lcom = new Communicator(ip1,ip2,ip3, 4950);
    listen_thread = new std::thread(&Driver::Listen, this);
    sleep(1); // a quick delay to space out threads

    trcom = new Communicator(ip1,ip2,ip3, 4951);
    tlcom = new Communicator(ip1,ip2,ip3, 4952);
    talk_thread = new std::thread(&Driver::Command, this);
}

// For anyone
void Driver::Listen()
{
    lcom->startListen();
}

// For Robot
void Driver::Speak()
{
    tcom->send_Ready();
}

// For Robot
void Driver::Error()
{
    tcom->send_Error("Error");
}

// For Hub
void Driver::Command()
{
    trcom->send_Move(0, "Move Right"); // send Robot 1 Right
    tlcom->send_Move(1, "Move Left"); // send Robot 2 Left
}
