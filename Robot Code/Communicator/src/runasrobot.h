#ifndef RUNASROBOT_H
#define RUNASROBOT_H

#include "locate.h"
#include <ctime>

class RunAsRobot
{
public:
    RunAsRobot(int id, char robotIP[], int pushFor);
    void Robot1();
    void Robot2();
    bool Teleoperate(int pushFor);
    void SemiAuto();

};

#endif // RUNASROBOT_H
