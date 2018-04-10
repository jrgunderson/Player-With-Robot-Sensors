/*
 * State Machine for HUB
 */

#include "runasHub.h"

Driver *d;

// HUB must NOT change drivers -> all communications to Robot2 must be relayed Robot1
RunAsHub::RunAsHub(char robotIP[], bool toError)
{
    d = new Driver(robotIP);

    int todo;
    cout << "Press [1] when ready to commence trials" << endl;
    cin >>  todo;
    d->SendStart(toError); // tell robot1 to start (and whether trial will introduce error)
    cout << "Let the trials begin!" << endl;


    // wait for robot2 to move to its corner
    for(;;)
    {
        if(d->isReady())
        {
            d->SendReady(); // forward Ready Message from robot2 to robot1
            break;
        }

    }


    bool taskComplete= false; // flag that signifies HUB has completed task by teleoperation

    for(;;) // wait to see if robots completed task
    {
        if(d->needHelp())
        {
            cout << "Robot2 Needs Help!\n 1= Push Straight (Peer to Peer),\n"
                    "2= Push Alone (Full Autonomous), \n3= Teleoperate Robot1,\n"
                    "9= Pause (can only interrupt if robots NOT turning)" << endl;

            // tell robot2 how to continue
            cin >>  todo;
            d->Move(todo);


            // if HUB interrupted System Initiative autonomy,
            //  to give semi-autonomous (mixed-intiaitve) commands
            if(todo == 9)
            {
                cout << "1= Resume, 3= Quit Task"
                        "4= Go to Left Side of box (facing box),\n"
                        "5= Go to Left Side of box (box to the Right)\n"
                        "6= Go to Left Side of box (box to the Left)\n"
                        "7= Go to Right Side of box (facing box)\n"
                        "8= Go to Right Side of box (box to the Right)\n"
                        "9= Go to Right Side of box (box to the Left)\n"
                        "99= Exit Semi-Autonomous Mode" << endl;

                for(;;)
                {
                    cin >>  todo;
                    d->Move(todo);

                    if(todo == 99 || todo == 1){
                        break;
                    }
                    sleep(1);
                }
            }


            // if teleoperating Robot1
            if(todo == 3)
            {
                 cout << "2= Reverse, 4= Left, 6= Right, 8= Forward,\n"
                         "1= SendReady, 99= TaskComplete" << endl;
                 for(;;){
                     cin >>  todo;
                     d->Move(todo);

                     if(todo == 99 || todo == 1){ // task completed
                         taskComplete = true;
                         break; // breaks from teleoperate loop, but not from State Machine loop
                     }

                  }

             }

        }

        // if Robot2 did not need help && told me task complete
        else if(d->isSuccessful())
        {
            cout << "! TASK COMPLETE !" << endl;
            d->SendSuccess(); // tell robot1 to stand down
            break;
        }

        // if HUB decided task is complete
        else if(taskComplete){
            break;
        }

    }
}
