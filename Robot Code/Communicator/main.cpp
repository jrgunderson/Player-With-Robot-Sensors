
#include "driver.h"
#include <string>
#include "runasrobot.h"

int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2

char ipRight[] = "10.42.0.42"; // IP address for Robot1
char ipLeft[] = "10.42.0.11"; // IP address for Robot2

int pushFor = 75; // number of iterations to push box for
bool toError = 1; // HUB tell robotA to fail?


void runAsHub(Driver *d);


int main(int argc, char *argv[])
{

    if(ID == 0)
    {
        Driver *d = new Driver(ipRight);
        runAsHub(d);
    }

    else if(ID == 1){
        new RunAsRobot(ID, ipLeft, pushFor);
    }
    else if(ID == 2){
        new RunAsRobot(ID, ipRight, pushFor);
    }


}

// State Machine for HUB
// HUB must NOT change drivers -> all communications to Robot2 must be relayed Robot1
void runAsHub(Driver *d)
{

    int todo;
    cout << "Press [1] when ready to commence trials" << endl;
    cin >>  todo;
    d->SendStart(toError); // tell robot1 to start
    cout << "Let the trials begin!" << endl;


    // wait to see if robot's completed task
    bool taskComplete= false;
    for(;;)
    {           
        if(d->needHelp())
        {
            cout << "Robot2 Needs Help!\n 1=push straight, 2=push alone, 3=teleoperate Robot1" << endl;

            // tell robot2 how to continue
            cin >>  todo;
            todo += 10; // convert to format for Robot1 to pass message to Robot2
            d->Move(todo);


            // if teleoperating Robot1
            if(todo == 13)
            {
                 cout << "0=stop, 2=reverse, 4=left, 6=right, 8=forward,\n1=SendReady, 9=SendError, 99=TaskComplete" << endl;
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

        // if Robot2 told me task complete
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

