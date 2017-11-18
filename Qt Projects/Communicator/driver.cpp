#include "driver.h"

char ip1[] = "10.42.0.1";
char ip2[] = "10.42.0.11";
char ip3[] = "10.42.0.42"; // Other Robot

Communicator* com;


Driver::Driver()
{
      com = new  Communicator(ip1,ip2,ip3, 4950);

      thread* listen_thread = new std::thread(&Driver::Listen, this);
      sleep(1); // a quick delay to space out threads

      thread* talk_thread = new std::thread(&Driver::SendReady, this);
}



void Driver::Listen()
{
    com->startListen();
}


void Driver::SendReady()
{
    com->send_Ready();
}


void Driver::Error()
{
    com->send_Error("Error");
}

void Driver::SendHelp()
{
    com->send_Help();
}


void Driver::SendSuccess()
{
    com->send_Success();
}

void Driver::Move(int i)
{
    com->send_Move(i);
}


int Driver::getMove()
{
    return com->getMove();
}


bool Driver::isReady()
{
    return com->getReady();
}

bool Driver::isError()
{
    return com->getError();
}

bool Driver::needHelp()
{
    return com->getHelp();
}

bool Driver::isSuccessful()
{
    return com->getSuccess();
}

