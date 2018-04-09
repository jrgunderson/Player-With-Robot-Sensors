#ifndef LOCATE_H
#define LOCATE_H

#include <iostream>
#include <cmath>
#include <ctime>
#include "driver.h"

#define RAYS 32

class Locate
{

public:

    double maxRange = -1;
    int scanPoints = -1;
    int right = -1;
    int left = -1;
    int middle = -1;
    int rightEye = -1;
    int leftEye = -1;

    Locate(Driver* driver, int id, int pushfor);
    int run();
    int avoidWalls();
    int locateBox();
    int locateBoxOffset();

    int getSizeFromLeft(int index);
    int getSizeFromRight(int index);
    int getBoxSize(int index);
    int getMiddleIndex(int index);
    int getBoxRightIndex(int index);
    int getBoxLeftIndex(int index);
    int shortestIndex(int r, int l);

    bool goToLeftSide();
    bool goToRightSide();
    bool moveForwardFromRight(int dp);
    bool moveForwardFromLeft(int dp);
    void turnLeft(int dp);
    void turnRight(int dp);
    void adjustLeft(int dp);
    void adjustRight(int dp);
    void turnAroundLeft();
    void turnAroundRight();

    int pushBoxAlone(int n);
    int push(int t);
    int pushRight(int n);
    int pushLeft(int n);

    void wait(int n);
    void wait2start();
    bool wait4ready();
    void introduceError();
    void clear();
    void moveBackards();
    void moveForwards();
    void moveLeft();
    void moveRight();
    void stop();
    void slow();

    double sumOfMagnitudes(int start, int end);
    double getRightHypotenuse();
    double getLeftHypotenuse();
    bool didTilt(int iLeft, int iRight);

private:

    double cap = .2;
    double speed = cap;  // in meters per second
    double newturnrate = 0; // in radians per seconds
    double minDist = .19;  // distance robot should stop in front of box
    double minRadius = .75; // distance when robot clears walls and has def located box
    int minWallSize = 200; // size that is definitely not a box
    Driver* d;
    int ID;
    int pushFor;
    bool toError;

};





#endif // LOCATE_H
