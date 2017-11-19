/*
 * State Machine for Robots
*/

#include "runasrobot.h"


RunAsRobot::RunAsRobot(Driver *d, int id, int pushFor, bool toError)
{
    Locate* l = new Locate(d, id, pushFor, toError);

    // wait to start
    if(id==1){
        cout << "waiting to start" << endl;
        l->wait4Ready();
    }

    bool success = l->run();

    // if error
    if(!success)
    {
        // Robot1 do this...
        if(id == 1)
        {
            // wait for HUB to tell you what to do
            {
                int move;
                for(;;)
                {
                    move = d->getMove();
                    switch( move )
                    {
                        // just push box straight (for n iterations)
                        case 0: l->push(pushFor/2); break; // divided by 2 since failure happens halfway into task

                        // push box alone (number of times to push each side)
                        case 1: l->pushBoxAlone(3); break;

                        // else wait for instructions
                        default: l->wait(1); break;
                    }
                }
            }
        }
        // Robot2 do this...
        else{
            // TODO: robotB stand by for teleoperation
        }
    }

    // tell HUB task is complete
    d->SendSuccess();
}
