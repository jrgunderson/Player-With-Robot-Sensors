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
        void Move(int i);
        void SendSuccess();
        int getMove();
        bool isReady();
        bool isError();
        bool needHelp();
        bool isSuccessful();
};

#endif // DRIVER_H
