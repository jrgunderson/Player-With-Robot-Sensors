#include "driver.h"

char ip1[] = "10.42.0.99";
char ip2[] = "10.42.0.99";
//char ip3[] = "10.42.0.42"; //other robot

Communicator* com;
thread* listen_thread;
thread* talk_thread;


Driver::Driver(char ip[])
{
    com = new  Communicator(ip1,ip2,ip, 4950);

    listen_thread = new std::thread(&Driver::Listen, this);
    sleep(1); // a quick delay to space out threads

    talk_thread = new std::thread();
}


void Driver::Close()
{
    listen_thread->join();
    talk_thread->join();
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

