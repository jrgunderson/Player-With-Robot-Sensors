#include "driver.h"

char ip1[] = "10.42.0.99";
char ip2[] = "10.42.0.99";
char ip3[] = "10.42.0.42"; // other robot

Communicator* com;

// default constructor: for Robot
Driver::Driver()
{
      com = new  Communicator(ip1,ip2,ip3, 4950);

      thread* listen_thread = new std::thread(&Driver::Listen, this);
      sleep(1); // a quick delay to space out threads

      thread* talk_thread = new std::thread(&Driver::Speak, this);
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
   // tlcom->send_Move(1, "Move Left"); // send Robot 2 Left
}
