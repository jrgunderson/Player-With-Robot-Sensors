#ifndef TASK_H
#define TASK_H


class Task
{
public:
    Task();
    Task(double newW, double newX, double newY);
    double getW(){return w;}
    double getX(){return x;}
    double getY(){return y;}
private:
    double w,x,y;
};

#endif // TASK_H
