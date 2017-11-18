
#include "driver.h"
#include <string>
//#include "runasrobot.h"

Driver *d;
int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2
bool toError = false; // introduce error?


void runAsHub();


int main(int argc, char *argv[])
{
    d = new Driver();

    d->SendSuccess();


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
        //new RunAsRobot(d, ID, toError);
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
            cout << "Robot Needs Help!" << endl;

            char todo;
            cin >>  todo;

            d->SendReady();

        }
        else if(d->isSuccessful())
        {
            cout << "game over" << endl;
            break;
        }

        sleep(1); // slow down loop a little
    }


    cout << "! TASK COMPLETE !" << endl;
}

