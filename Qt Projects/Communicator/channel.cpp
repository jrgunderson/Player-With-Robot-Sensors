// wraps multiple Drivers into 1 Channel object

#include "channel.h"

char hostIP[] = "10.42.0.1";
char r1IP[] = "10.42.0.42";
char r2IP[] = "10.42.0.11";

int host_r1 = 4950;
int host_r2 = 4951;
int r1_r2 = 4952;


Channel::Channel(int id)
{
    if(id == 0)
    {
        d1 = new Driver(r1IP, host_r1); // robot1
        d2 = new Driver(r2IP, host_r2); // robot2
    }
    else if(id == 1)
    {
        d1 = new Driver(r2IP, r1_r2); // host
        d2 = new Driver(hostIP, host_r1); // robot2
    }
    else if(id == 2)
    {
        d1 = new Driver(r2IP, r1_r2); // host
        d2 = new Driver(hostIP, host_r2); // robot1
    }

}
