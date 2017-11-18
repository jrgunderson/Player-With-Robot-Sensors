/* Run Robots first, then Hub */

#include "driver.h"
//#include "runasrobot.h"

Driver *hd;
int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2
bool toError = false; // introduce error?


void runAsHub();


int main(int argc, char *argv[])
{
    hd = new Driver();


    if(ID == 0){
        runAsHub();
    }
    else if(ID == 1 || ID == 2){
        //new RunAsRobot(ID, toError);
    }

}


void runAsHub()
{
    hd->SendReady(); // tell robots to start

    // wait to see if robot's completed task
    for(;;)
    {
        if(hd->needHelp())
        {
            int todo;
            cout << "Robot Needs Help!" << endl;
            cin >>  todo;

            hd->SendReady();


        }

        sleep(1);
    }

}

