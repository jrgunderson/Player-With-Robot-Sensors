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


    // if Robot2 -> switch drivers to talk to HUB
    if(id == 2)
    {
         Driver *hd = new Driver(hostIP);

         // if ERROR
         if(pushesRemain > 0)
         {
             hd->SendHelp();

             // wait for HUB to tell you what to do
             int move;
             for(;;)
             {
                 move = hd->getMove();
                 switch( move )
                 {
                     // just push box straight
                     case 1: l->push(pushesRemain); pushesRemain =0; break;

                     // push box alone (number of times to push each side)
                     case 2: l->pushBoxAlone(3); pushesRemain =0; break;

                     // wait for teleoperate to send signal
                     case 3:
                         l->wait4Ready();
                         l->push(100);     // arbitrary push count,
                         pushesRemain = 0; // robot stops pushing when told to
                     break;
                 }
                 if(pushesRemain == 0){
                     break;
                 }
             }
         }

         // tell HUB task is complete
         hd->SendSuccess();
    }

    // Robot1 do this...
    else
    {
        bool giveup = false;

        // Regardless if ERROR or not...
        int move;
        for(;;)
        {
            // if recieve signal from HUB that finished task
            if(d->isSuccessful())
            {
                break;
            }

            // else respond to teleoperation
            // OR forward messages from HUB to Robot2
            else{
                move = d->getMove();
                switch( move )
                {
                    // teleoperation controls
                    case 0: l->stop(); d->Error(); break; // to stop and have other robot stop with you

                    case 2: l->moveBackards(); break;

                    case 4: l->moveLeft(); break;

                    case 6: l->moveRight(); break;

                    case 8: l->moveForwards(); break;

                    // robot2 messages
                    case 1: d->SendReady(); break;

                    case 9: d->Error(); break;

                    case 11: d->Move(1); sleep(1); giveup = true; break;
                    case 12: d->Move(2); sleep(1); giveup = true; break;
                    case 13: d->Move(3); sleep(1); break;

                    case 99: d->SendSuccess(); giveup = true; break;

                    // else don't move
                    l->stop(); break;
                }
            }

            if(giveup){
                break;
            }

        }
    }



}

