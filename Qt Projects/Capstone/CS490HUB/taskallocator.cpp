#include "taskallocator.h"


TaskAllocator::TaskAllocator()
{
    bids = QList<Bid>();
    tasks = QList<Task>();
    winningTeams = QList<Team>();
}
Task TaskAllocator::getTask(int i){
    Task t = tasks.at(i);
    return t;
}
void TaskAllocator::setCurrent(int i){

    currentTask = getTask(i);
    currentIndex = i;
    w = currentTask.getW();

}
//Delete this method
double TaskAllocator::calcDist(double x, double y) {
    int newX = currentTask.getX();
    int newY = currentTask.getY();
    return qSqrt(qPow(newX-x,2)+qPow(newY-y,2));
}

void TaskAllocator::taskCompleted(){
    //Delete task in task list
    tasks.removeAt(currentIndex);
    //Remove task from List in MainWindow
}
void TaskAllocator::receiveOpResponse(bool available, double x, double y, int busy)
{

    human = false;
    if(available) //Human is available
    {
        if(busy < 50){ //Human is also not very busy
            human= true; // Human is invovled
            double t = w/2;
            double d = qSqrt(qPow(currentTask.getX()-x,2)+qPow(currentTask.getY()-y,2));
            humanBid = Bid(-1,t,d);
            emit operatorBidReceived("Human bid received and added");

        }
        else {//If human says they are available, but they are busy, then we will not include human in the TaskAllocation
            emit operatorBidReceived("Human bid received, but will not participate");
        }
    }

    QList<Team> teams = taskAllocation();

    emit winnerFound(teams);

}

QList<Team> TaskAllocator::taskAllocation(){
    bool teamFound = false;
    bool teamFoundWH = false; // Team including operator
    QList<Team> t;

    if(!human) {
        teamFoundWH = true; //Human is not participating, so do not need to find team with human
    }

    for(int i = 1; i <= bids.size(); i++) {

        if(!teamFound) { //if we dont have a robot team, find one
            QList<int> ignore;

            t.insert(0,createTeam(w,i,ignore));

            if(t[0].size() != 0) { //a team was made
                teamFound = true;
            }
        }
    }
    if(human){
        bids.append(humanBid);
        for(int i = 1; i <= bids.size(); i++) {

            if(!teamFoundWH) { //if we dont have a robot team with human, find one
                QList<int> ignore;
                ignore.append(bids.size());
                t.insert(1,createTeam(w,i,ignore));
                if(t[1].size() != 0) { //a team was made
                    teamFoundWH = true;
                }
            }
        }
    bids.removeLast();
    }
    return t;
}
//ignore is the index that has already been in team, k is team size
Team TaskAllocator::createTeam(double w, int k,QList<int> ignore){

    QList<Team> possibleTeams;
    if(k==1) { //Base case: Team size = 1
        for(int i = 0; i< bids.size(); i++) {
            Team temp;

            if(ignore.contains(i)) { //this index is in the team
                continue;
            }

            /*
             * MAKE THIS T multiplied by 2 because single robot pushes on each side
             */
            double t = bids[i].getStr();
            if(t >= w){ // If this robot is able to push the box by itself, we have a team

                temp.add(bids[i]);
                possibleTeams.append(temp);
            }
        }
        if(possibleTeams.size() == 0){
            Team t;
            return t;
        }
        return bestTeam(possibleTeams,w);
    }
    else { //Team size > 1

        for(int i =0; i < bids.size(); i++) {
            if(ignore.contains(i)) { //this index is in the team
                continue;
            }
            Team temp;

            temp.add(bids[i]);
            ignore.append(i);
            possibleTeams.append(temp + createTeam(w - bids[i].getStr(), k-1, ignore));
            ignore.removeOne(i);
            //possibleTeams.append(temp);
        }

        for(int i = 0; i < possibleTeams.size(); i++){
            //possibleTeams.get(i).toString();
        }
        if(possibleTeams.size() == 0){
            Team t;
            return t;
        }
        return bestTeam(possibleTeams,w);
    }
}
Team TaskAllocator::bestTeam(QList<Team> teams, double w){
    Team best = teams[0];
    //Team current;

    for(int i = 1; i < teams.length(); i++){
        Team current = teams[i];
        double w1 = best.getTeamStrength();
        double w2 = current.getTeamStrength();
        double d1;
        double d2;

        //If strength isnt enough to push box
        if(w1 - w< 0) {
            best = current; //Best cannot push box
            continue;
        }
        if(w2 - w< 0) { //Current cannot push box
            continue;
        }

        if(w1 < w2) {//then W1's strength is closer to the weight of the box
            //Best stays the same
            continue;
        }
        else if(w1 > w2) { //then W2's strength is closer to the weight of the box
            best = current;
            continue;
        }
        else { // w1 = w2
            d1 = best.getTeamDist(currentTask.getX(),currentTask.getY());
            d2 = current.getTeamDist(currentTask.getX(),currentTask.getY());

            if(d1 < d2) { //Team 1 is closer to the box
                continue;
            }
            else if(d1 > d2) {
                best = current;
                continue;
            }
        }
    }
    return best;
}
