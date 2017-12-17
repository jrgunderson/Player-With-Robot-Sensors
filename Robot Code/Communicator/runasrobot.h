#ifndef RUNASROBOT_H
#define RUNASROBOT_H

#include "locate.h"
#include <ctime>

class RunAsRobot
{
public:
    RunAsRobot(int id, char robotIP[], char hostIP[], int pushFor);
    void Robot1();
    void Robot2(char hostIP[]);
    bool Teleoperate(int pushFor);
    void SemiAuto();

};

#endif // RUNASROBOT_H
