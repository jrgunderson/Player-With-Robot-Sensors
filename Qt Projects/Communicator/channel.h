#ifndef CHANNEL_H
#define CHANNEL_H

#include "driver.h"

class Channel
{
public:

    Driver *d1;
    Driver *d2;

    Channel(int id);

};

#endif // CHANNEL_H
