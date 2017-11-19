
#include "driver.h"
#include <string>
//#include "runasrobot.h"

Driver *d;
int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2
int pushFor = 50; // number of iterations to push box for
bool toError = false; // introduce error?


void runAsHub();


int main(int argc, char *argv[])
{
    d = new Driver();

    for(;;)
    {
        int i;
        cin >> i;
        if(i != 99){
            d->Move(i);
        }
        else{ break; }

    }

    if(ID == 0){
        runAsHub();
    }
    else if(ID == 1 || ID == 2){
        //new RunAsRobot(d, ID, pushFor, toError);
    }

}

// State Machine for HUB
void runAsHub()
{

    d->SendReady(); // tell robot1 to start

    // wait to see if robot's completed task
    for(;;)
    {
        if(d->needHelp())
        {
            cout << "Robot Needs Help!/n 0=push straight, 1=push alone" << endl;

            // tell robot how to continue
            int todo;
            cin >>  todo;
            d->Move(todo);

        }
        else if(d->isSuccessful())
        {
            cout << "! TASK COMPLETE !" << endl;
            break;
        }

        sleep(1); // slow down loop a little
    }

}

