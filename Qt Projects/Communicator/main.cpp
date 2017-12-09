// change IP addresses in "drivers.cpp"


#include "channel.h"
#include <string>
#include "runasrobot.h"

int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2

int pushFor = 50; // number of iterations to push box for
bool toError = 0; // introduce error?


void runAsHub(Channel *c);


int main(int argc, char *argv[])
{
    Channel *c = new Channel(ID);

    if(ID == 0)
    {
        runAsHub(c);
    }

    else if(ID == 1){
        RunAsRobot(ID, c, pushFor, toError);
    }
    else if(ID == 2){
        RunAsRobot(ID, c, pushFor, toError);
    }

    // DEBUG
    else if(ID == 99)
    {
        cout << "Entering DEBUG mode" << endl;
        // Test Driver functions
    }


}

// State Machine for HUB
// HUB must NOT change drivers -> all communications to Robot2 must be relayed Robot1
void runAsHub(Channel *c)
{

    int todo;
    cout << "Press [1] when ready to commence trials" << endl;
    cin >>  todo;
    c->d1->SendStart(); // tell robot1 to start
    cout << "Let the trials begin!" << endl;


    // wait to see if robot's completed task
    bool taskComplete= false;
    for(;;)
    {           
        if(c->d1->needHelp())
        {
            cout << "Robot2 Needs Help!\n 1=push straight, 2=push alone, 3=teleoperate Robot1" << endl;

            // tell robot2 how to continue
            cin >>  todo;
            todo += 10; // convert to format for Robot1 to pass message to Robot2
            c->d2->Move(todo);


            // if teleoperating Robot1
            if(todo == 13)
            {
                 cout << "0=stop, 2=reverse, 4=left, 6=right, 8=forward,\n1=SendReady, 9=SendError, 99=TaskComplete" << endl;
                 for(;;){
                     cin >>  todo;
                     c->d1->Move(todo);

                     if(todo == 99){
                         taskComplete = true;
                         break;
                     }
                 }

            }

        }

        // if Robot2 told me task complete
        else if(c->d2->isSuccessful())
        {
            cout << "! TASK COMPLETE !" << endl;
            c->d1->SendSuccess(); // tell robot1 to stand down
            break;
        }

        // if HUB decided task is complete
        else if(taskComplete){
            break;
        }

        sleep(1); // slow down loop a little
    }

}

