/*
 * State Machine for Robots
 *
 * Robot1 = Right Robot
 * Robot2 = Left Robot
 *
 * toError = Robot1 stops
*/

#include "runasrobot.h"

// id= this.RobotID, ip= IP address of OTHER ROBOT (sending messages to)
RunAsRobot::RunAsRobot(int id, char ip[], int pushFor, bool toError)
{
    Driver *d;
    d = new Driver(ip);

    Locate* l = new Locate(d, id, pushFor, toError);

    // wait to start
    if(id==1){
        cout << "waiting to start" << endl;
        l->wait4Ready();
    }

    bool pushesRemain = l->run();

    // if ERROR
    if(pushesRemain != 0)
    {
        // Robot2 do this...
        if(id == 2)
        {
            // wait for HUB to tell you what to do
            int move;
            for(;;)
            {
                move = d->getMove();
                switch( move )
                {
                    // just push box straight (for n iterations)
                    case 1: l->push(pushesRemain); break;

                    // push box alone (number of times to push each side)
                    case 2: l->pushBoxAlone(3); break;

                    // wait for teleoperate to send signal
                    case 3:
                        l->wait4Ready();
                        l->push(pushesRemain);
                    break;

                    // else wait for instructions
                    default: l->wait(1); break;
                }
            }
        }

        //Robot1 do this...
        else{

            // listen for teleoperation signal
            int move;
            for(;;)
            {
                // if recieve signal that robot2 finished task
                if(d->isSuccessful())
                {
                    break;
                }

                // else respond to teleoperation
                else{
                    move = d->getMove();
                    switch( move )
                    {
                        case 2: //TODO: moveBackwards(); break;

                        case 8: //TODO: moveStraight(); break;

                        case 4: //TODO: moveLeft(); break;

                        case 6: //TODO: moveRight(); break;
						
						case 11: //TODO: SendReady; break;
						
						case 99: //TODO: SendError; break;

                        // else wait for instructions
                        default: l->wait(1); break;
                    }
                }
            }
        }
    }

    // tell HUB task is complete
    d->SendSuccess();
}

