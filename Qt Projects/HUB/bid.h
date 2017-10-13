#ifndef BID_H
#define BID_H


class Bid
{
public:
    Bid();
    Bid(int i, double s, double newD);
    int getID(){return id;}
    double getStr(){return str;}
    double getD(){return d;}
private:
    int id; //Robot ID
    double str,d; //Strength of Robot, X coord, Y coord
};

#endif // BID_H
