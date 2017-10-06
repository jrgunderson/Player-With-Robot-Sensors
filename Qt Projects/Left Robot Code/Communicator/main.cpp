
#include "locate.h"
#include "driver.h"
#include <pthread.h>


using namespace std;

Driver *d;

// passing into thread
void PrintHello(void *threadid)
{
   cout << "Hello World! Thread ID, " << threadid << endl;

   // close thread
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // only 1 thread
    pthread_t threads[1];

    // info to be passed
    string info = "YAY!";

    // paraemters = (which thread, NULL=default, function thread is executing, pointer variable (NULL=no arguments))
    pthread_create(&threads, NULL, PrintHello, (void *)info);


    Locate();

}
