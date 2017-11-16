/* Run Robots first, then Hub */


#include "locate.h"
#include "driver.h"

Driver *d;
int ID = 0;  // 0=HUB, 1=Robot1, 2=Robot2
bool toError = false;


void runAsHub();
void runAsRobot(int id);
void wait4Ready();


int main(int argc, char *argv[])
{
    d = new Driver();


    if(ID == 0){
        runAsHub();
    }
    else if(ID == 1 || ID == 2){
        runAsRobot(ID);
    }

}




void runAsHub()
{
    d->SendReady();

    // wait to see if robot's completed task
    for(;;)
    {
        if(d->needHelp())
        {
            int todo;
            cout << "Robot Needs Help!" << endl;
            cin >>  todo;

            d->SendReady();


        }

        sleep(1);
    }

}



void wait4Ready(){
    for(;;){

        if(d->isReady())
        {
            break;
        }
        else{
            sleep(1);
        }
    }
}




void runAsRobot(int id)
{
    // wait to start
    wait4Ready();

    Locate* l = new Locate(d, id, toError);
    bool success = l->run();

    if(!success){
        if(id == 1){
            // wait for HUB to tell you what to do
            wait4Ready();

            //l->pushBoxAlone();
            l->push(50);

        }
    }
    else{
        // TODO: stand by for teleoperation
    }

}
