
#include "driver.h"
#include <string>
#include "runasrobot.h"

int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2
char ipRight[] = "10.42.0.42"; // IP address for Robot1
char ipLeft[] = "10.42.0.11"; // IP address for Robot2

int pushFor = 50; // number of iterations to push box for
bool toError = false; // introduce error?


void runAsHub(Driver *d);


int main(int argc, char *argv[])
{
    Driver *d;
    d = new Driver(ipRight);

    if(ID == 0){
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

    d->SendReady(); // tell robot1 to start

    // wait to see if robot's completed task
    for(;;)
    {
        if(d->needHelp())
        {
            d->Close();
            d = new Driver(ipLeft);
            cout << "Robot2 Needs Help!/n 1=push straight, 2=push alone, 3=teleoperate Robot2" << endl;

            // tell robot how to continue
            int todo;
            cin >>  todo;
            d->Move(todo);

            // if teleoperating Robot1 -> switch drivers back
            if(todo == 3)
            {
                d->Close();
                d = new Driver(ipRight);
            }

        }
        else if(d->isSuccessful())
        {
            cout << "! TASK COMPLETE !" << endl;
            break;
        }

        sleep(1); // slow down loop a little
    }

}

