
#include "locate.h"
#include "driver.h"
#include <pthread.h>


using namespace std;

Driver *d;

// function to be executed by thread
void PrintHello(void *threadid)
{
    // since incoming argument must be void type
    // cast back to non-void type
    int info = (int)threadid;

   cout << "Hello World! Thread ID, " << info << endl;

   // close thread
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // only 1 thread
    pthread_t threads[1];

    // info to be passed
    int info = 1;

    // paraemters = (which thread, NULL=default, function thread is executing, pointer variable (NULL=no arguments))
    pthread_create(&threads[1], NULL, PrintHello, (void *)info);


    Locate();

}
