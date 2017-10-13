#ifndef TEAM_H
#define TEAM_H

#include "bid.h"
#include <QObject>
#include <QtMath>

class Team : public QObject
{
    Q_OBJECT
public:
    Team();
    Team(const Team &other);
    void add(Bid b) {bids.append(b);}
    Bid getBid(int i) const {return bids.at(i);}
    int size() const {return bids.size();}
    void remove(int i){ bids.removeAt(i);}
    double getTeamStrength();
    double getTeamDist(double x, double y);

    Team operator +(const Team& t);
    void operator =(const Team& t);

private:
    QList<Bid> bids;

};

#endif // TEAM_H
