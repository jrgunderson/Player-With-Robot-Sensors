#ifndef RUNASROBOT_H
#define RUNASROBOT_H

#include "locate.h"
#include "channel.h"

class RunAsRobot
{
public:
    RunAsRobot(int id, Channel *c, int pushFor, bool toError);
};

#endif // RUNASROBOT_H
