/*
 * State Machine for Robots
 *
 * Robot1 = Right Robot
 * Robot2 = Left Robot
*/

#include "runasrobot.h"

Driver *dr;
Locate *l;


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
void RunAsRobot::Robot1()
{
    // wait to start
    cout << "waiting to start" << endl;
    l->wait2start();

    int pushesRemain = l->run();

    cout << pushesRemain << endl;

    // Regardless if ERROR or not...
    int move;
    bool exit = false;
    for(;;)
    {
        // if recieve signal from HUB (forwarded from Robot2) that task finished
        if(dr->isSuccessful())
        {
            break;
        }


        move = dr->getMove();

        // forward HUB's initial response on how to help Robot2
        switch(move)
        {
            case 1: dr->Move(1); sleep(1); exit = true; break; // P2P
            case 2: dr->Move(2); sleep(1); break; // Push Box Alone
            case 3: dr->Move(3); sleep(1); break; // Teleoperation
            case 9: dr->Error(); sleep(1); break; // Pause
        }

        if( move == 3) // Enter Teleoperation Mode
        {
            exit = Teleoperate(pushesRemain);
        }


        if(move == 9) // Enter Semi-Autonomous Mode
        {
            for(;;)
            {
                move = dr->getMove();

                // Resume Task
                if(move == 1){
                    dr->SendReady();
                    break;
                }
                // Quit Task
                else if(move == 3){
                    dr->SendSuccess();
                }
                // Exit Semi-Autonomous Mode
                else if(move == 99)
                {
                    break;
                }

                // Forward Semi-Autonomous Move to Robot2
                else{
                    dr->Move(move);
                }

            }
        }

        // leave state machine if appropriate to
        if(exit == true){
            break;
        }

    }//end for(;;)

}


// Robot2 (Left_Robot) do this...
void RunAsRobot::Robot2(char hostIP[])
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
         int timeout = 20;
         time_t start = time(0);
         for(;;)
         {
             move = dr->getMove();

             // if HUB not telling you how to troubleshoot error
             if( difftime(time(0), start) >= timeout )
             {
                move = 2;
             }

             switch( move )
             {
                 // just push box straight
                 case 1: pushesRemain = l->push(pushesRemain); break;

                 // push box alone (number of times to push each side)
                 case 2: pushesRemain = l->pushBoxAlone(3); break;

                 // wait for teleoperate to send signal
                 case 3:
                 {
                     bool stopPushing = l->wait4ready();

                     if(stopPushing)
                     {
                         pushesRemain = 0;
                     }else{
                         pushesRemain = l->push(pushesRemain);
                     }

                     break;
                 }


                 /* Semi-Autonomous Responses */


                 // Go to Left Side of box (facing box)
                 case 4: l->goToLeftSide(); break;

                 // Go to Left Side of box (box to the Right)
                 case 5:
                     l->moveForwardFromRight(l->rightEye);
                     l->turnRight(l->right);
                     l->adjustRight(l->middle);
                     break;

                 // Go to Left Side of box (box to the Left)
                 case 6:
                     l->turnLeft(l->left);
                     l->adjustLeft(l->middle);
                     l->goToLeftSide();
                     break;


                 // Go to Right Side of box (facing box)
                 case 7: l->goToRightSide(); break;

                 // Go to Right Side of box (box to the Right)
                 case 8:
                     l->moveForwardFromLeft(l->leftEye);
                     l->turnLeft(l->left);
                     l->adjustLeft(l->middle);
                     break;

                 // Go to Right  Side of box (box to the Left)
                 case 9:
                     l->turnRight(l->right);
                     l->adjustRight(l->middle);
                     l->goToRightSide();
                     break;
                 
             }// end switch-case

             if(pushesRemain == 0){
                 break;
             }
         }
     }

     // tell HUB task is complete
     hd->SendSuccess();
}



// Teloperate and/or Forward messages to other robot
bool RunAsRobot::Teleoperate(int pushFor)
{
    bool exit = false;
    int move;
    for(;;)
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

                case 1: dr->SendReady();
                        if( l->push(pushFor) == 0 ) { exit = true; }
                        break;

                case 7: exit = true; break;
                case 9: dr->Error(); break;
                case 99: dr->SendSuccess(); exit = true; break;

                default: l->stop(); dr->Error(); break;
            }

            // stop between each move && make sure other robot stops as well
            l->stop();
            dr->setMove(-1);
        }

        if(exit){break;}
    }


    // if HUB told you to stop teleoperation
    return exit;
}
