/*
 * State Machine for Robots
 *
 * Robot1 = Right Robot
 * Robot2 = Left Robot
*/

#include "runasrobot.h"

Driver *dr;
Locate *l;

void Robot1();
void Robot2(char hostIP[]);


// id= this.RobotID, ip= IP address of OTHER ROBOT (sending messages to)
RunAsRobot::RunAsRobot(int id, char robotIP[], char hostIP[], int pushFor)
{
    dr = new Driver(robotIP);
    l = new Locate(dr, id, pushFor);

    if(id == 1)
    {
        Robot1();
    }
    else if(id == 2)
    {
        Robot2( hostIP );
    }

    cout << "goodbye" << endl;
}


// Robot1 (Right_Robot) do this...
void Robot1()
{
    // wait to start
    cout << "waiting to start" << endl;
    l->wait2start();

    int pushesRemain = l->run();

    cout << pushesRemain << endl;

    // Regardless if ERROR or not...
    bool giveup = false;
    int move;
    for(;;)
    {
        // if recieve signal from HUB (forwarded from Robot2) that finished task
        if(dr->isSuccessful())
        {
            break;
        }

        // respond to teleoperation
        // forward messages from HUB to Robot2
        else
        {
            move = dr->getMove();

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
                    case 1: dr->SendReady(); l->push(pushesRemain); break;

                    case 11: dr->Move(1); sleep(1); giveup = true; break;
                    case 12: dr->Move(2); sleep(1); giveup = true; break;
                    case 13: dr->Move(3); sleep(1); break;

                    case 99: dr->SendSuccess(); giveup = true; break;

                    default: l->stop(); dr->Error(); break;
                }

                // stop between each move && make sure other robot stops as well
                l->stop();
                dr->setMove(-1);
            }
        }


        // if HUB told you task completed directly
        if(giveup){
            break;
        }

    }// end for(;;)
}


// Robot2 (Left_Robot) do this...
void Robot2(char hostIP[])
{

    int pushesRemain = l->run();

     // create new talk thread - BUT keep old listen thread
     Driver *hd = new Driver(hostIP);

     // if ERROR
     if(pushesRemain > 0)
     {
         hd->SendHelp();

         pushesRemain +=11; // this robot will always need to catch-up
         cout << pushesRemain << endl;

         // wait for HUB to tell you what to do
         int move;
         for(;;)
         {
             move = dr->getMove();

             switch( move )
             {
                 // just push box straight
                 case 1: pushesRemain = l->push(pushesRemain); break;

                 // push box alone (number of times to push each side)
                 case 2: l->pushBoxAlone(3); pushesRemain =0; break;

                 // wait for teleoperate to send signal
                 case 3:
                     bool stopPushing = l->wait4ready();

                     if(stopPushing){
                         pushesRemain = 0;
                     }else{
                         pushesRemain = l->push(pushesRemain);
                     }

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
