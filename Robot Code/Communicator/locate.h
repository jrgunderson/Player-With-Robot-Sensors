#ifndef LOCATE_H
#define LOCATE_H

#include <iostream>
#include <cmath>
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
    int getSizeFromLeft(int index);
    int getSizeFromRight(int index);
    int getBoxSize(int index);
    int getMiddleIndex(int index);
    int shortestIndex(int r, int l);
    void adjustLeft(int dp);
    void adjustRight(int dp);
    void moveForwardFromRight(int dp);
    void moveForwardFromLeft(int dp);
    int getBoxRightIndex(int index);
    int getBoxLeftIndex(int index);
    void turnLeft(int dp);
    void turnRight(int dp);
    void goToLeftSide();
    void goToRightSide();
    int pushRight(int n);
    int pushLeft(int n);
    void pushBoxAlone(int n);
    void push(int t);
    int avoidWalls();
    int locateBoxOffset();
    int locateBox();
    double sumOfMagnitudes(int start, int end);
    double getRightHypotenuse();
    double getLeftHypotenuse();
    bool didTilt(int iLeft, int iRight);
    void wait(int n);
    bool wait4ready();
    void wait2start();
    void introduceError();
    void clear();
    void moveBackards();
    void moveForwards();
    void moveLeft();
    void moveRight();
    void stop();
    void slow();

private:

    double cap = .2;
    double speed = .35;  // in meters per second
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
