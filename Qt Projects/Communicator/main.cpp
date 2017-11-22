
#include "driver.h"
#include <string>
#include "runasrobot.h"

int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2
char ipRight[] = "10.42.0.42"; // IP address for Robot1
char ipLeft[] = "10.42.0.11"; // IP address for Robot2

int pushFor = 50; // number of iterations to push box for
bool toError = true; // introduce error?


void runAsHub(Driver *d);

/*
 * TODO: RunAsRobot Constructor will run TWO SEPERATE METHODS based on ID
 * Robot2 will switch Drivers (does ALL talking to HUB)
 * Robot1 MUST NOT have option to SWITCH DRIVERS (because needs to be teleoperated)
 * HUB also does NOT change drivers -> so if HUB needs to talk to Robot2, must do so through Robot1
*/
int main(int argc, char *argv[])
{

    if(ID == 0)
    {
        Driver *d = new Driver(ipRight);
        runAsHub(d);
    }
    else if(ID == 1){
        new RunAsRobot(ID, ipLeft, pushFor, toError);
    }
    else if(ID == 2){
        new RunAsRobot(ID, ipRight, pushFor, toError);
    }

}

// State Machine for HUB
void runAsHub(Driver *d)
{

    int todo;
    cout << "Press [1] when ready to commence trials" << endl;
    cin >>  todo;
    d->SendReady(); // tell robot1 to start
    cout << "Let the trials begin!" << endl;

    // wait to see if robot's completed task
    bool taskComplete= false;
    for(;;)
    {           
        if(d->needHelp()) // message comes from robot2, but for some reason can only hear on robot1 thread
        {
            Driver *r2d = new Driver(ipLeft); // only works if i put robot2 thread after

            cout << "Robot2 Needs Help!\n 1=push straight, 2=push alone, 3=teleoperate Robot1" << endl;

            // tell robot how to continue
            cin >>  todo;
            r2d->Move(todo);


            // if teleoperating Robot1
            /*
             * Unable to teleoperate Robot1 while simultaneously telling Robot2 when its OK to push
             *
             * TODO: redesign communication
             *          OR
             *      figure out how to chain communication AS TO avoid switching Drivers
            */
            if(todo == 3)
            {
                d= new Driver(ipRight);
                 cout << "2=reverse, 4=left, 6=right, 8=forward,\n 1=SendReady, 9=SendError, 99=TaskComplete" << endl;
                 for(;;){
                     cin >>  todo;
                     d->Move(todo);

                     if(todo == 99){
                         taskComplete = true;
                         break;
                     }
                 }

            }

        }
        else if(d->isSuccessful())
        {
            cout << "! TASK COMPLETE !" << endl;

            d = new Driver(ipRight);
            d->SendSuccess(); // tell robot1 to stand down
            d->SendSuccess(); // needs to be done twice for some reason

            break;
        }
        else if(taskComplete){
            break;
        }

        sleep(1); // slow down loop a little
    }

}

