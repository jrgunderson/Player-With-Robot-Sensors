#ifndef RUNASROBOT_H
#define RUNASROBOT_H

#include "locate.h"

class RunAsRobot
{
public:
    RunAsRobot(Driver *d, int id, int pushFor, bool toError);
};

#endif // RUNASROBOT_H
