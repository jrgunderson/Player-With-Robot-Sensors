/*
 * State Machine for Robots
*/

#include "runasrobot.h"


RunAsRobot::RunAsRobot(Driver *d, int id, bool toError)
{
    Locate* l = new Locate(d, id, toError);

    // wait to start
    if(id==1){
        cout << "waiting to start" << endl;
        l->wait4Ready();
    }

    bool success = l->run();

    // if error
    if(!success){
        if(id == 1){
            // wait for HUB to tell you what to do
            l->wait4Ready();

            //l->pushBoxAlone();
            l->push(50);

        }
    }
    else{
        // TODO: robotB stand by for teleoperation
    }

    // tell HUB task is complete
    d->SendSuccess();
}
