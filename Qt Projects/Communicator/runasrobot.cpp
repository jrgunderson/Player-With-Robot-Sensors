/*
 * State Machine for Robots
 *
 * Robot1 = Right Robot
 * Robot2 = Left Robot
 *
 * toError = Robot1 stops
*/

#include "runasrobot.h"

char hostIP[] = "10.42.0.1";

// id= this.RobotID, ip= IP address of OTHER ROBOT (sending messages to)
RunAsRobot::RunAsRobot(int id, char ip[], int pushFor, bool toError)
{
    Driver *d = new Driver(ip);

    Locate* l = new Locate(d, id, pushFor, toError);

    // wait to start
    if(id==1){
        cout << "waiting to start" << endl;
        l->wait4Ready();
    }

    int pushesRemain = l->run();

    Driver *hd = new Driver(hostIP);

    // if ERROR
    if(pushesRemain > 0)
    {
        // Robot2 do this...
        if(id == 2)
        {
            d->SendHelp();

            // wait for HUB to tell you what to do
            int move;
            for(;;)
            {
                move = hd->getMove();
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
                if(hd->isSuccessful())
                {
                    break;
                }

                // else respond to teleoperation
                else{
                    move = hd->getMove();
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
    hd->SendSuccess();
}

