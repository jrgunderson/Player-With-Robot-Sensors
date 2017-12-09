#ifndef DRIVER_H
#define DRIVER_H


#include <iostream>
#include <communicator.h>
#include <thread>

using namespace std;


class Driver
{
    public:
        explicit Driver(char ip[], int port);
        void Listen();
        void Speak();
        void SendStart();
        void SendReady();
        void SendHelp();
        void Error();
        void Move(int i);
        void SendSuccess();
        int getMove();
        void Close();
        bool toStart();
        bool isReady();
        bool isError();
        bool needHelp();
        bool isSuccessful();
};

#endif // DRIVER_H
