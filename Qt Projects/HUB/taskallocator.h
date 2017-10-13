#ifndef TASKALLOCATOR_H
#define TASKALLOCATOR_H
#include <QFile>
#include <QtMath>
#include "bid.h"
#include "team.h"
#include "task.h"
#include "objective.h"
#include <QDebug>



class TaskAllocator : public QObject
{
    Q_OBJECT

public:
    TaskAllocator();

    int taskCount;
    int activeBots;

    double w;
    Task currentTask;
    int currentIndex; //index of current task in task list
    Bid humanBid;

    double calcDist(double x, double y);
    QList<Team> getWinner(){return winningTeams;}
    void addTask(Task t){tasks.append(t);
                        taskCount++;}
    void addBid(Bid b){bids.append(b);}
    void taskCompleted();
    QList<Team> taskAllocation();
    Task getTask(int i);
    void setCurrent(int i);
    QList<Task> getTasks(){return tasks;}
    QList<Bid> getBids(){return bids;}

public slots:
    void receiveOpResponse(bool available, double x, double y, int busy);

private:
    QList<Bid> bids; //Only robot bids
    QList<Bid> bids2; //Contains robot bids and human bid
    QList<Task> tasks;
    QList<Team> winningTeams;
    bool human;
    Team createTeam(double w,int k, QList<int> ignore);
    Team bestTeam(QList<Team> teams,double w);


signals:
    void operatorBidReceived(QString message);
    void tasksCollected();
    void taskAssigned(QString task);
    void winnerFound(QList<Team> teams);
    void tasksComplete();
    void logIt(QString s);
};

#endif // TASKALLOCATOR_H
