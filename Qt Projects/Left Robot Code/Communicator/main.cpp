
#include "locate.h"
#include "driver.h"
#include <pthread.h>


using namespace std;

Driver *d;

void *PrintHello(void*);

// function to be executed by thread
void *PrintHello(void* id)
{
    // since incoming argument must be void type
    // cast back to non-void type
    long info = (long)id;

   cout << "Hello World! Thread ID, "<< id << endl;

   // close thread
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // only 1 thread
    pthread_t thread;

    // info to be passed
    int info = 1;

    // paraemters = (which thread, NULL=default, function thread is executing, pointer variable (NULL=no arguments))
    pthread_create(&thread, NULL, PrintHello, (void *)info);


    Locate();

}
