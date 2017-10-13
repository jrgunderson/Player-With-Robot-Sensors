#include "team.h"

Team::Team()
{
    bids = QList<Bid>();
}
Team::Team(const Team &other)
{
    for(int i = 0; i < other.size(); i++){
        this->add(other.getBid(i));
    }
}
double Team::getTeamStrength(){
    double sum = 0;
    for(int i = 0; i < bids.size(); i++){
        Bid current = bids.at(i);
        sum = sum + current.getStr();
    }
    return sum;
}
double Team::getTeamDist(double x, double y){
    double sum = 0;
    for(int i = 0; i < bids.size(); i++){
        Bid current = bids.at(i);
        sum = sum + current.getD();
    }
    return sum;
}
Team Team::operator +(const Team& t) {
    Team temp;
    for(int i = 0; i < this->size(); i++){
        temp.add(this->getBid(i));
    }
    for(int i = 0; i < t.size(); i++){
        temp.add(t.getBid(i));
    }
    return temp;
}

void Team::operator =(const Team& t) {
    this->bids.clear();
    for(int i = 0; i < t.size(); i++){
        this->add(t.getBid(i));
    }
}
