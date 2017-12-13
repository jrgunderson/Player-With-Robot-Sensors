/*
 * State Machine for Robots
 *
 * Robot1 = Right Robot
 * Robot2 = Left Robot
*/

#include "runasrobot.h"

char hostIP[] = "10.42.0.1";


// id= this.RobotID, ip= IP address of OTHER ROBOT (sending messages to)
RunAsRobot::RunAsRobot(int id, char ip[], int pushFor)
{
    Driver *d = new Driver(ip);
    Locate *l = new Locate(d, id, pushFor);

    // wait to start
    if(id==1)
    {
        cout << "waiting to start" << endl;
        l->wait2start();
    }

    int pushesRemain = l->run();

    // if Robot2 -> switch drivers to talk to HUB
    if(id == 2)
    {
         d = new Driver(hostIP);
         l = new Locate(d, id, pushesRemain);


         // if ERROR
         if(pushesRemain > 0)
         {
             d->SendHelp();

             // wait for HUB to tell you what to do
             int move;
             for(;;)
             {
                 move = d->getMove();

                 switch( move )
                 {
                     // just push box straight
                     case 1: l->push(pushesRemain); pushesRemain =0; break;

                     // push box alone (number of times to push each side)
                     case 2: l->pushBoxAlone(3); pushesRemain =0; break;

                     // wait for teleoperate to send signal
                     case 3:
                         bool stopPushing = l->wait4ready();

                         if(stopPushing){
                             pushesRemain = 0;
                         }else{
                             l->push(100); // push count arbitrary cuz robot2 will stop when robot1 stops
                             pushesRemain = 0;
                         }

                     break;
                 }
                 if(pushesRemain == 0){
                     break;
                 }
             }
         }

         // tell HUB task is complete
         d->SendSuccess();
    }

    // Robot1 do this...
    else
    {
        bool giveup = false;

        // Regardless if ERROR or not...
        int move;
        for(;;)
        {
            // if recieve signal from HUB (forwarded from Robot2) that finished task
            if(d->isSuccessful())
            {
                break;
            }

            // respond to teleoperation
            // forward messages from HUB to Robot2
            else
            {
                move = d->getMove();

                // only make a move if move to be made
                if(move != -1)
                {
                    switch( move )
                    {
                        // teleoperation controls
                        //      about 4 move<turn>s = 90 degree turn

                        case 2: l->moveBackards(); l->slow(); sleep(1); break;
                        case 22: l->moveBackards(); l->slow(); sleep(2); break; // long Reverse
                        case 222: l->moveBackards(); l->slow(); sleep(4); break; // longer Reverse

                        case 4: l->moveLeft(); sleep(1); break;
                        case 44: l->moveLeft(); sleep(4); break; // long Left turn

                        case 6: l->moveRight(); sleep(1); break;
                        case 66: l->moveRight(); sleep(4); break; // long Right turn

                        case 8: l->moveForwards(); sleep(1); break;
                        case 88: l->moveForwards(); sleep(2); break; // long Forward
                        case 888: l->moveForwards(); sleep(4); break; // longer Forward

                        // messages forwarded to Robot2
                        case 1: d->SendReady(); l->push(pushesRemain); break;

                        case 11: d->Move(1); sleep(1); giveup = true; break;
                        case 12: d->Move(2); sleep(1); giveup = true; break;
                        case 13: d->Move(3); sleep(1); break;

                        case 99: d->SendSuccess(); giveup = true; break;

                        default: l->stop(); d->Error(); break;
                    }

                    // stop between each move && make sure other robot stops as well
                    l->stop();
                    d->Error();
                    d->setMove(-1);
                }
            }


            // if HUB told you task completed directly
            if(giveup){
                break;
            }

        }// end for(;;)
    }

    cout << "goodbye" << endl;
}

