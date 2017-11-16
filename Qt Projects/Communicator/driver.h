#ifndef DRIVER_H
#define DRIVER_H


#include <iostream>
#include <communicator.h>
#include <thread>

using namespace std;


class Driver
{
    public:
        explicit Driver();
        void Listen();
        void SendReady();
        void SendHelp();
        void Error();
        void Command();
        bool isReady();
        bool isError();
        bool needHelp();
};

#endif // DRIVER_H
