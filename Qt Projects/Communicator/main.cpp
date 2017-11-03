
//#include "locate.h"
#include "driver.h"

using namespace std;

Driver *d;
int main(int argc, char *argv[])
{

    d = new Driver();

    for(;;){
        d->Speak();
        sleep(2);

        cout << d->isReady() << endl;
    }

    //Locate* l = new Locate();
    //l->run();


}
