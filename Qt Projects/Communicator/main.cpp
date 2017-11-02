/* Pseudo-Hub */

//#include "locate.h"
#include "driver.h"

using namespace std;

Driver *d;
int main(int argc, char *argv[])
{

    d = new Driver();

    for(;;){
        d->Command1();
        d->Command2();
        sleep(2);
    }

    //Locate();


}
