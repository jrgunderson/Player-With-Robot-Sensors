/* I apologize in advance for what seems to be so many redundant Methods
 * But it was proving impossible to pass Communicator objects through threads
 * So each Method deals with a specific thread */

#include "driver.h"

char ip[] = "10.42.0.99";
char r1ip[] = "10.42.0.42"; // other robot
char r2ip[] = "10.42.0.11";
Communicator* r1com;
Communicator* r2com;

// default constructor: for Robot
Driver::Driver()
{
      r1com = new Communicator(ip,ip,r1ip, 4950);
      r2com = new Communicator(ip,ip,r2ip, 4951);

      thread* r1lt= new std::thread(&Driver::Listen1, this);
      thread* r2lt= new std::thread(&Driver::Listen2, this);

      thread* r1st= new std::thread(&Driver::Speak1, this);
      thread* r2st= new std::thread(&Driver::Speak2, this);
}


// Start Listening to Robot1
void Driver::Listen1( )
{
    r1com->startListen();
}

// Start Listening to Robot1
void Driver::Listen2( )
{
    r2com->startListen();
}

// Send Ready to Robot1
void Driver::Speak1()
{
    r1com->send_Ready();
}

// Send Ready to Robot2
void Driver::Speak2()
{
    r2com->send_Ready();
}

// Send Error to Robot1
void Driver::Error1()
{
    r1com->send_Error("Error");
}

// Send Error to Robot2
void Driver::Error2()
{
    r2com->send_Error("Error");
}

// For Hub
void Driver::Command1()
{
    r1com->send_Move(0, "Move Right"); // send Robot 1 Right
}

void Driver::Command2()
{
    r2com->send_Move(1, "Move Left"); // send Robot 2 Left
}
