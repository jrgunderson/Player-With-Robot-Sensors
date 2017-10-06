
#include "locate.h"
#include "driver.h"
#include <pthread.h>


using namespace std;

Driver *d;

int main(int argc, char *argv[])
{
    // 1 thread
    pthread_t threads[1];

    // passing into thread
    string PrintHello = "PrintHello";

    // paraemters = (thread, NULL=default, what thread is executing, reference pointer NULL=no arguments)
    pthread_create(&threads, NULL, PrintHello, NULL);

    // close thread
    pthread_exit(NULL);

    Locate();

}
