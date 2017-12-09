#include "driver.h"


Communicator* com;
thread* listen_thread;
thread* talk_thread;


Driver::Driver(char ip[], int port)
{
    com = new  Communicator(ip, port);

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


void Driver::SendStart()
{
    com->send_Start();
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

bool Driver::toStart()
{
    return com->getStart();
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

