#include "driver.h"

pthread_t thread;
Communicator* com;

Driver::Driver()
{
    char ip1[] = "10.110.255.74"; //Robot 1 or Other Robot
    char ip2[] = "10.110.255.74"; //Robot 2 or Phone
    char ip3[] = "10.110.255.74"; //Desktop

    // open thread
    thread = pthread_self();
    if (thread == 0)
    {
        cout << "ERROR: Problem Creating Thread" << endl;
    }
    else{
        cout << "Thread Created..." << endl;
    }


    com = new Communicator(ip1,ip2,ip3, 6665);
    com->send_Ready();
    sleep(10);
    com->send_Task();
    sleep(10);
    com->send_Bid(1,5,12);
}
