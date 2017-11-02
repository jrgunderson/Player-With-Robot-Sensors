#ifndef LOCATE_H
#define LOCATE_H

#include <iostream>
#include <cmath>

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

    Locate();
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
    void pushBox(int n);
    void push(int t);
    int avoidWalls();
    int locateBoxOffset();
    int locateBox();
    void pushRight(int n);
    void pushLeft(int n);
    void wait(int n);
    void waitForInput();
    double sumOfMagnitudes(int start, int end);

private:

    double cap = .2;
    double speed = .35;  // in meters per second
    double newturnrate = 0; // in radians per seconds
    double minDist = .19;  // distance robot should stop in front of box
    double minRadius = .75; // distance when robot clears walls and has def located box
    int minWallSize = 200; // size that is definitely not a box

};





#endif // LOCATE_H