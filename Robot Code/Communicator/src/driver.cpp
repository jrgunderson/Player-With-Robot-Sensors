// wraps communicator into a thread

#include "driver.h"

Communicator* com;
thread* listen_thread;
thread* talk_thread;


Driver::Driver(char ip[])
{
    com = new  Communicator(ip, 4950);

    talk_thread = new std::thread(&Driver::Speak, this);

    sleep(1); // a quick delay to space out threads

    listen_thread = new std::thread(&Driver::Listen, this);
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

void Driver::Speak()
{
    com->startSpeak();
}


void Driver::SendStart(bool e)
{
    com->send_Start(e);
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

void Driver::setMove(int m)
{
    com->setMove(m);
}

bool Driver::toStart()
{
    return com->getStart();
}

bool Driver::startBroken()
{
    return com->errorStart();
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

