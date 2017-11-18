/*
 * State Machine for Robots
*/

#include "runasrobot.h"

Driver *d;

RunAsRobot::RunAsRobot(int id, bool toError)
{
    Locate* l = new Locate(d, id, toError);
    bool success = l->run();

    // wait to start
    l->wait4Ready();

    if(!success){
        if(id == 1){
            // wait for HUB to tell you what to do
            l->wait4Ready();

            //l->pushBoxAlone();
            l->push(50);

        }
    }
    else{
        // TODO: stand by for teleoperation
    }
}
