#include "bid.h"

Bid::Bid()
{
    id = 0;
    str = 0;
    d = 0;
}
Bid::Bid(int i, double s, double newD)
{
    id = i;
    str = s;
    d = newD;
}

