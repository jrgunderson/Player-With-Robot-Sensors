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
        void Listen1();
        void Listen2();
        void Speak1();
        void Speak2();
        void Error1();
        void Error2();
        void Command1();
        void Command2();
};

#endif // DRIVER_H
