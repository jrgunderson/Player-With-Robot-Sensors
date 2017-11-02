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
        void Speak();
        void Error();
        void Command();
};

#endif // DRIVER_H
