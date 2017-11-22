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
            hd->SendHelp();

            // wait for HUB to tell you what to do
            int move;
            for(;;)
            {
                move = hd->getMove();
                switch( move )
                {
                    // just push box straight (for n iterations)
                    case 1: l->push(pushesRemain); pushesRemain =0; break;

                    // push box alone (number of times to push each side)
                    case 2: l->pushBoxAlone(3); pushesRemain =0; break;

                    // wait for teleoperate to send signal
                    case 3:
                        l->wait4Ready();
                        l->push(pushesRemain);
                        pushesRemain =0;
                    break;
                }
                if(pushesRemain == 0){
                    break;
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
                    move = hd->getMove();
                    switch( move )
                    {
                        case 2: l->moveBackards(); break;

                        case 8: l->moveForwards(); break;

                        case 4: l->moveRight(); break;

                        case 6: l->moveLeft(); break;
						
                        case 1: d->SendReady(); break;
						
                        case 9: d->Error(); break;

                        case 99: d->SendSuccess(); break;

                        // else don't move
                        default: l->stop(); break;
                    }
                }
            }
        }
    }

    // tell HUB task is complete
    hd->SendSuccess();
}

