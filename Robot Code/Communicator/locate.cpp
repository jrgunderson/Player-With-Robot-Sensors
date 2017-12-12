
/*
 * Task 1: - move towards box
 *
 * Task 2: - adjust until front facing box
 *
 * Task 3: - move to respective corner of box
 *      a) Robot1 goes to Right side first
 *      b) Robot2 then goes to Left side
 *
 * Task 4: - push
 *      a) if Robot1 stops
 *      b) Robot2 will also stop
 *
 */

#include "args.h"
#include "locate.h"
#include <ctime>


PlayerCc::PlayerClient robot(gHostname, gPort);
PlayerCc::Position2dProxy pp(&robot, gIndex);
PlayerCc::LaserProxy lp(&robot, gIndex);
PlayerCc::RangerProxy rp(&robot, gIndex);

time_t timer;

const int YES = 0;

// constructor
Locate::Locate(Driver* driver, int id, int pushfor)
{
    ID = id;
    d = driver;
    pushFor = pushfor;
    toError = 0;
}

// start full autonomous mode
int Locate::run()
{
    int success;
    timer = time(0);

    std::cout << robot << std::endl;

    // throw exceptions on creation if fail
    try{

        pp.SetMotorEnable (true);

        robot.Read();

        // read parameters
        maxRange = lp.GetMaxRange();
        scanPoints = lp.GetCount();
        middle = scanPoints/2;
        int thirtyDegrees = scanPoints/8;
        right = thirtyDegrees; // -90 degrees from center
        left = scanPoints-1 - thirtyDegrees; // 90 degrees from center
        int fortyFiveDegrees = scanPoints/5.3;
        rightEye = middle - fortyFiveDegrees;
        leftEye = middle + fortyFiveDegrees;

        std::cout << rightEye << " -> " << leftEye << std::endl;


        // initialize variables
        int index = -1;
        double boxSize = scanPoints;

        if(ID == 2){
            cout << "waiting for other robot" << endl;
            wait2start();// second robot waits for first to tell it, it can start
        }


        //index = avoidWalls();
         index = locateBox();


        // tell me info about the box
        int rightBoxIndex = getBoxRightIndex(index);
        int leftBoxIndex = getBoxLeftIndex(index);
        index = (leftBoxIndex + rightBoxIndex)/2;

        std::cout << "Box from index: " << rightBoxIndex << " -> " << leftBoxIndex << std::endl;
        std::cout << "Middle at: " << index << std::endl;

        boxSize = 2*std::sqrt( std::pow(lp[rightBoxIndex],2) + std::pow(lp[index],2) );
        std::cout << "Size: " << boxSize << " meters" << std::endl;



        // turn until datapoint reads shortest distance from box
        // this indicates robot is aligned front-facing
        if( index < middle )
        {
            adjustRight(middle);
        }
        else{

            adjustLeft(middle);
        }

        if(ID == 1){
            success = pushRight(pushFor);
        }
        else{
            success = pushLeft(pushFor);
        }


        clear();

      } // end try
      catch (PlayerCc::PlayerError & e)
      {
        std::cerr << e << std::endl;
      }


    return success;
}


// clear system
void Locate::clear()
{
    for(int i=0; i<10; ++i)
    {
        robot.Read();
        //robot.StopThread();
        //robot.Stop();
        pp.SetMotorEnable(false);
    }
}

void Locate::slow()
{
    robot.Read();
    pp.SetSpeed( speed/2, newturnrate/2 );
}

void Locate::stop()
{
    robot.Read();
    pp.SetSpeed(0.0, 0.0);
}

void Locate::moveBackards()
{
    robot.Read();
    pp.SetSpeed(-cap/2, 0.0);
}

void Locate::moveForwards()
{
    robot.Read();
    pp.SetSpeed(cap/2, 0.0);
}

void Locate::moveRight()
{
    robot.Read();
    pp.SetSpeed(0.0, -cap/2);
}

void Locate::moveLeft()
{
    robot.Read();
    pp.SetSpeed(0.0, cap/2);
}


// n = number of rounds to push for
// returns 0 if successfull
//          else if unsuccessfull -> returns # of iterations remaining to push
int Locate::pushLeft(int n)
{
    goToLeftSide();

    std::cout << "It took me: " << (time(0)-timer) << " seconds to get here" << std::endl;

    d->SendReady(); // send that you're ready to push!
    wait4ready(); // wait for other robot to acknowledge it is ready


    // finally start pushing
    for(int i=n; i>=0; --i)
    {
        robot.Read();
        pp.SetSpeed(cap, 0.0);


        // if other robot malfunctions
        if(d->isError())
        {
		  wait(1);
            cout << "HELP! WHAT TO DO!?" << endl;
            return i; // return how many iterations there are left to push
        }

    }

    return YES;
}



// n = number of rounds to push for
// returns 0 if successfull
//          else if unsuccessfull -> returns # of iterations remaining to push
int Locate::pushRight(int n)
{

    goToRightSide();

    std::cout << "It took me: " << (time(0)-timer) << " seconds to get here" << std::endl;

    wait4ready(); // wait for ready message from other robot to push
    d->SendReady(); // tell other robot you received their ready message

    // finally start pushing
    for(int i=n; i>=0; --i)
    {
        robot.Read();
        pp.SetSpeed(cap, 0.0);


        // introduce error 1/2 into pushing
        if(toError){
            if(i <= n/2)
            {
                d->Error();
                introduceError();
                return i;
            }
        }
    }

    return YES;
}


// 1) send error, 2) get out of way, 3) turn off motor
void Locate::introduceError()
{
    //d->Error();
    wait(5);

    // go backwards
    for(int i=0; i<30; ++i)
    {
        robot.Read();
        pp.SetSpeed(-cap, 0.0);
    }

    // 'shut-down' robot
    wait(1);
    pp.SetMotorEnable(false);

}


// n = how long to wait for
void Locate::wait(int n )
{
    for(int i=0; i<n; ++i)
    {
        robot.Read();
        pp.SetSpeed(0.0, 0.0);
    }
}


// wait for 'ready' message or 'change in box orientation' to push
// or wait for 'end' message to stop
bool Locate::wait4ready()
{
    for(;;)
    {
        if(d->isSuccessful())
        {
            return true;
        }

        else if( d->isReady() )
        {
            break;
        }

        else{
            wait(1);
        }
    }

    return false;
}

// do nothing until start signal recieved
void Locate::wait2start()
{
    for(;;)
    {

        if( d->toStart() )
        {
            toError = d->startBroken();
            break;
        }

        else{
            wait(1);
        }

    }
}

// n =  number of times to go back and forth
void Locate::pushBoxAlone(int n)
{
    for( int i=0; i<n; ++i)
    {
        goToRightSide();
        push(20);
        goToLeftSide();
        push(25);
    }
}


// t = iterations to push box for
void Locate::push(int t)
{

    // ensure push defaults
    if(newturnrate != 0)
    {
        newturnrate = 0;
    }
    if(speed <= 0)
    {
        speed = cap;
    }

    // push
    bool over = false;
    for(int i=0; i<t; ++i)
    {
        robot.Read();
        pp.SetSpeed(speed, newturnrate);


        // will pause if receive error
        if( d->isError() )
        {
            over = wait4ready();

            // will exit if received End_Task signal while waiting
            if(over){
                break;
            }
        }
    }

    // set speed back to zero
    speed = 0;
    robot.Read();
    pp.SetSpeed(speed, newturnrate);

}\


// send robot to right side of box
void Locate::goToRightSide()
{
    // assuming robot front-facing box -> turn left 90 degrees
    turnRight(middle);
    adjustRight(left);

    // tell other robot it can start
    if(ID == 1)
    {
        d->SendStart(toError); // actually doesn't matter if
    }                          // other robot knows if error will be introduced

    // assuming robot's eyesight is parallel to box
    // move forward until "right eye" opens up
    moveForwardFromLeft(leftEye);

    // assuming robot's eyesight is parallel to box -> turn right 90 degrees
    turnLeft(left);
    adjustLeft(middle);
}


// send robot to left side of box
void Locate::goToLeftSide()
{
    // assuming robot front-facing box -> turn left 90 degrees
    turnLeft(middle);
    adjustLeft(right);

    // assuming robot's eyesight is parallel to box
    // move forward until "right eye" opens up
    moveForwardFromRight(rightEye);

    // assuming robot's eyesight is parallel to box -> turn right 90 degrees
    turnRight(right);
    adjustRight(middle);
}


// move forward assuming box on right side
void Locate::moveForwardFromRight(int dp)
{

    std::cout << "\nMoving Forward\n" << std::endl;


    if(newturnrate != 0)
    {
        newturnrate = 0;
    }
    if(speed <= 0)
    {
        speed = cap;
    }


    double boxDist = 999;
    for( ;; )
    {
        robot.Read();

        // box ends once no longer incrementally increasing consecutive distances
        for( int i=dp-5; i<dp+5; ++i ) // in case it passed the end when looping
        {

             std::cout << lp[i-1] << " - " << lp[i] << " > .5?" << std::endl;

            if( std::abs(lp[i+1]- lp[i]) > .5 || lp[i+1] == 0 )
            {
                speed = 0;
                robot.Read();
                pp.SetSpeed(speed, newturnrate);
                break;
            }

        }

        if(speed == 0)
        {
            break;
        }


        // ajust if robot getting too close to box |or| getting to far away
        double distAvg = 0;
         for( int i=right-5; i<right+5; ++i )
         {

            distAvg += lp[i];

         }
        if( distAvg < boxDist )
        {
            newturnrate = .1;
        }
        else if( distAvg > boxDist )
        {
            newturnrate = -.1;
        }
        else{
            newturnrate = 0;
        }

        std::cout << "\noldDist: " << boxDist << ", vs newDist: " << distAvg << std::endl;

        std::cout << "speed: " << speed << ", turnrate: " << newturnrate << std::endl;


        pp.SetSpeed(speed, newturnrate);

        boxDist = distAvg;
    }
}


// move forward assuming box on left side
void Locate::moveForwardFromLeft(int dp)
{
    std::cout << "\nMoving Forward\n" << std::endl;


    if(newturnrate != 0)
    {
        newturnrate = 0;
    }
    if(speed <= 0)
    {
        speed = cap;
    }


    double boxDist = 999;
    for( ;; )
    {
        robot.Read();

        std::cout << dp << std::endl;

        // box ends once no longer incrementally increasing consecutive distances
        for( int i=dp+5; i>=dp-5; --i )
        {

            std::cout << lp[i-1] << " - " << lp[i] << " > .5?" << std::endl;

            if( std::abs(lp[i-1]- lp[i]) > .5 || lp[i-1] == 0  )
            {
                speed = 0;
                robot.Read();
                pp.SetSpeed(speed, newturnrate);
                break;
            }

        }

        if(speed == 0)
        {
            break;
        }


        // ajust if robot getting too close to box |or| getting to far away
        double distAvg = 0;
         for( int i=left-5; i<left+5; ++i )
         {

            distAvg += lp[i];

         }
         distAvg /= 10;
        if( distAvg < boxDist )
        {
            newturnrate = -.1;
        }
        else if( distAvg > boxDist )
        {
            newturnrate = .1;
        }
        else{
            newturnrate = 0;
        }

        std::cout << "\noldDist: " << boxDist << ", vs newDist: " << distAvg << std::endl;

        std::cout << "speed: " << speed << ", turnrate: " << newturnrate << std::endl;

        pp.SetSpeed(speed, newturnrate);

        boxDist = distAvg;
    }
}


// turn right
void Locate::turnRight(int dp)
{
    std::cout << "\nTurning Right\n" << std::endl;

    if(newturnrate > -cap)
    {
        newturnrate = -cap;
    }
    if(speed != 0)
    {
        speed = 0;
    }

    double eye = lp[dp];
    for( ;; )
    {
        robot.Read();

        std::cout << "Eye see: "<< eye << std::endl;
        std::cout << lp[dp] << std::endl;

        // box ends once no longer incrementally increasing consecutive distances
        if( std::abs(lp[dp] - eye) > .5 || lp[dp] <= .01 )
        {
            newturnrate = 0;
            robot.Read();
            pp.SetSpeed(speed, newturnrate);
            break;
        }

        std::cout << "turnrate: " << newturnrate << std::endl;
        pp.SetSpeed(speed, newturnrate);

        eye = lp[dp];
    }
}

// turn left
void Locate::turnLeft(int dp)
{
    std::cout << "\nTurning Left\n" << std::endl;

    if(newturnrate < cap)
    {
        newturnrate = cap;
    }
    if(speed != 0)
    {
        speed = 0;
    }

    double eye = lp[dp];
    for( ;; )
    {
        robot.Read();

        std::cout << "Eye see: "<< eye << std::endl;
        std::cout << lp[dp] << std::endl;

        // box ends once no longer incrementally increasing consecutive distances
        if( std::abs(lp[dp] - eye) > .5 || lp[dp] <= .01 )
        {
            newturnrate = 0;
            robot.Read();
            pp.SetSpeed(speed, newturnrate);
            break;
        }

        pp.SetSpeed(speed, newturnrate);

        eye = lp[dp];
    }
}


// robot adjusts to front face box perfectly perpendicularly
// compares distances from dp -> LeftBoxIndex
void Locate::adjustLeft(int dp)
{
    std::cout << "\nAdjusting Left\n" << std::endl;

    if(newturnrate <= 0)
    {
        newturnrate = cap;
    }
    if(speed != 0)
    {
        speed = 0;
    }

    double avg1 = 999;
    double avg2 = 999;
    int trial = 0;

    for( ;; )
    {
        robot.Read();

        // compare with upcoming values
        double avg = 0;
        int end = getBoxLeftIndex(dp);

        std::cout << dp << " -> " << end << std::endl;

        // datapoint at which box ends will continously change as robot turns
        for(int i=dp; i<end; ++i )
        {

            avg += lp[i];

        }
        avg = avg/(end-dp+1);
        std::cout << "\navg:  " << avg << std::endl;
        std::cout << "avg1: "<< avg1 << ", avg2: " << avg2 << std::endl;


        // break if consistently increasing
        if(avg >= avg1 && avg1 >= avg2)
        {
            newturnrate = 0;
            robot.Read();
            pp.SetSpeed(speed, newturnrate);
            break;
        }

        if(trial == 0)
        {
            avg1 = avg;
            ++trial;
        }
        else{
            avg2 = avg1;
            avg1 = avg;
        }

        pp.SetSpeed(speed, newturnrate);

    }
}


// robot adjusts to front face box perfectly perpendicularly
// compares distances from dp -> RightBoxIndex
void Locate::adjustRight(int dp)
{
    std::cout << "\nAdjusting Right\n" << std::endl;

    if(newturnrate >= 0)
    {
        newturnrate = -cap;
    }
    if(speed != 0)
    {
        speed = 0;
    }

    double avg1 = 999;
    double avg2 = 999;
    int trial = 0;

    for( ;; )
    {
        robot.Read();

        // compare with upcoming values
        double avg = 0;
        int end = getBoxRightIndex(dp);

        // datapoint at which box ends will continously change as robot turns
        for(int i=dp; i>=end; --i )
        {

            avg += lp[i];

        }
        avg = avg/(dp-end+1);
        std::cout << "\navg:  " << avg << std::endl;
        std::cout << "avg1: "<< avg1 << ", avg2: " << avg2 << std::endl;


        // break if consistently increasing
        if(avg >= avg1 && avg1 >= avg2)
        {
            newturnrate = 0;
            robot.Read();
            pp.SetSpeed(speed, newturnrate);
            break;
        }

        if(trial == 0)
        {
            avg1 = avg;
            ++trial;
        }
        else{
            avg2 = avg1;
            avg1 = avg;
        }

        pp.SetSpeed(speed, newturnrate);

    }
}


// returns index of closest object
int Locate::shortestIndex(int r, int l)
{
    // find index at smallest distance
    double minObjDist = maxRange; // initialize to max distance
    int shortestIndex = -1;
    for (int i=r; i<l; ++i)
    {
        double pointDistance = lp[i];
        // search for shortest datapoint
        // >.02 cuz sometimes range returns weirdly low numbers for no reason
        if( pointDistance > .02 && pointDistance < minObjDist )
        {
            minObjDist = pointDistance;
            shortestIndex = i;
        }
    }

    return shortestIndex;
}


// finds right index of box (from given index)
int Locate::getBoxRightIndex(int index)
{
    int rightBoxIndex = -1;
    for( int i = index; i>0; --i )
    {

        // box ends once no longer incrementally consecutive increasing distances
        // or when data "breaks" past the Max Range of sensor (indicating box end)
        if( std::abs(lp[i-1] - lp[i]) > .5 || lp[i] == 0 )
        {
            rightBoxIndex = i;
            break;
        }
    }
    return rightBoxIndex;
}

// finds left index of box (from given index)
int Locate::getBoxLeftIndex(int index)
{
    int leftBoxIndex = -1;
    for( int i = index; i<681; ++i )
    {

        // box ends once no longer incrementally consecutive increasing distances
        // or when data "breaks" past the Max Range of sensor (indicating box end)
        if( std::abs(lp[i+1] - lp[i]) > .5 || lp[i] == 0 )
        {
            leftBoxIndex = i;
            break;
        }
    }
    return leftBoxIndex;
}


// returns size of box if index is to the left of the robot's center
int Locate::getSizeFromLeft(int index)
{
    return getBoxLeftIndex(index) - index;
}


// returns size of box if index is to the right of the robot's center
int Locate::getSizeFromRight(int index)
{
    return index - getBoxRightIndex(index);
}


// returns middle index for box directly in front of sensor
int Locate::getMiddleIndex(int index)
{
    return (getBoxLeftIndex(index) + getBoxRightIndex(index)) / 2;
}


// returns size of box if directly in front of laser sensor
int Locate::getBoxSize( int index)
{
    return getBoxLeftIndex(index) - getBoxRightIndex(index);
}


// algorithm to move away from walls but towards a box
// until box within certain range
int Locate::avoidWalls()
{
    // initialize variables
    int index = -1;
    int boxSize = scanPoints;
    bool isWall = true;

    // go into read-think-act loop 1 (move until cleared all walls)
    for(;;)
    {
        robot.Read();


        // locate corner of nearest obstacle (presumably a box)
        index = shortestIndex(rightEye, leftEye);
        double minObjDist = lp[index];

        std::cout << "\nCorner index " << index << " @ dist: " << minObjDist << std::endl;

        boxSize = getBoxSize(index);
        index = getMiddleIndex(index);


        // turn the robot until front facing middle of box
        // turn rate increases as it gets closer to object
        if( index > middle ) // if left of center
        {
            newturnrate = 1/(6*minObjDist); // turn left

        }
        else if( index < middle ) // if right of center
        {
            newturnrate = -1/(6*minObjDist); // turn right
        }
        else{
            newturnrate = 0;
        }


        std::cout << "Size of Box: " << boxSize
                << ", Middle index: "<< index << std::endl;

        std::cout << "speed: " << speed
                  << " turn: " << newturnrate
                  << std::endl;

        std::cout << "isWall? " << isWall << std::endl;


        // turn away from wall
        if( boxSize > minWallSize )
        {
            isWall = true;
            newturnrate = -newturnrate;
        }
        else{
            isWall = false;
        }


        // write commands to robot
        pp.SetSpeed(speed, newturnrate);


        // stop scanning once finite object a reached certain distance
        if( minObjDist <= minRadius && !isWall )
        {
            std::cout << "I FOUND A BOX!" << std::endl;
            break;
        }

    } // end think-read-react loop 1

    return index;
}


// move towards box but overshoot center of box by a little
// so when robot turns to face box it is exactly at center
int Locate::locateBoxOffset()
{
    int index = -1;
    int boxSize = scanPoints;

    // go into read-think-act loop 2
    for(;;)
    {
        robot.Read();

        // locate corner of nearest obstacle (presumably a box)
        index = shortestIndex(rightEye, leftEye);
        double minObjDist = lp[index];

        std::cout << "\nCorner index " << index << " @ dist: " << minObjDist << std::endl;


        // slow down as robot aproaches box
        double newSpeed = std::pow(minObjDist,2);

        if(newSpeed < speed)
        {
            speed = newSpeed;
        }
        else if( newSpeed < .15 )
        {
            speed = .15;
        }


        int rightSize = -1;
        int leftSize = -1;

        // if index in middle view of roomba
        if (index > middle -5 && index < middle +5 )
        {
            boxSize = getBoxSize(index);
        }
        // need to figure out which corner box is facing
        else{
            leftSize = getSizeFromLeft(index);
            rightSize = getSizeFromRight(index);
        }

        int offsetIndex = index;

        // calculate middle data point for front of box
        if( leftSize > rightSize ) // if left of center
        {
            offsetIndex = (boxSize/2) + index +5;
            boxSize = leftSize;
            std::cout << "Left size: " << boxSize << std::endl;

        }
        else if( rightSize > leftSize ) // if right of center
        {
            offsetIndex = index - (boxSize/2) -5;
            boxSize = rightSize;
            std::cout << "Right size: " << boxSize << std::endl;
        }
        else{
            //index = getMiddleIndex(index);
            std::cout << "Middle size: " << boxSize << std::endl;
        }


        // turn the robot until front facing middle of box
        // turn rate increases as it gets closer to object
        if( offsetIndex > middle ) // if left of center
        {
            newturnrate = 1/(6*minObjDist); // turn left

        }
        else if( offsetIndex < middle ) // if right of center
        {
            newturnrate = -1/(6*minObjDist); // turn right
        }
        else{
            newturnrate = 0;
        }

        // cap turnrate
        if( newturnrate > cap )
        {
            newturnrate = cap;
        }
        if( newturnrate < -cap )
        {
            newturnrate = -cap;
        }


        std::cout << "Offset middle at DataPoint: " << offsetIndex
                << ", Distance: "<< minObjDist << std::endl;

        std::cout << "speed: " << speed
                  << " turn: " << newturnrate  << std::endl;

        // write commands to robot
        pp.SetSpeed(speed, newturnrate);


        // stop scanning once finite object a reached certain distance
        if( minObjDist <= minDist )
        {
            std::cout << "I FOUND CENTER OF BOX!\n" << std::endl;
            speed = 0;  // newturnrate = -newturnrate;
            robot.Read();
            pp.SetSpeed(speed, newturnrate);
            break;
        }

    } // end think-read-react loop 2

    return index;
}


// just a basic algorithm to move towards box
int Locate::locateBox()
{
    // initialize variables
    int index = -1;
    int boxSize = scanPoints;

    for(;;)
    {
        robot.Read();

        // locate corner of nearest obstacle (presumably a box)
        index = shortestIndex(rightEye, leftEye);
        double minObjDist = lp[index];

        std::cout << "\nCorner index " << index << " @ dist: " << minObjDist << std::endl;

        boxSize = getBoxSize(index);
        index = getMiddleIndex(index);

        // slow down as robot aproaches box
        double newSpeed = std::pow(minObjDist,2);

        if(newSpeed < speed)
        {
            speed = newSpeed;
        }
        else if( newSpeed < cap )
        {
            speed = cap;
        }


        // turn the robot until front facing middle of box
        // turn rate increases as it gets closer to object
        if( index > middle ) // if left of center
        {
            newturnrate = 1/(6*minObjDist); // turn left

        }
        else if( index < middle ) // if right of center
        {
            newturnrate = -1/(6*minObjDist); // turn right
        }
        else{
            newturnrate = 0;
        }


        // cap turnrate
        if( newturnrate > cap )
        {
            newturnrate = cap;
        }
        if( newturnrate < -cap )
        {
            newturnrate = -cap;
        }


        std::cout << "Size of Box: " << boxSize
                << ", Middle index: "<< index << std::endl;

        std::cout << "speed: " << speed
                  << " turn: " << newturnrate
                  << std::endl;



        // write commands to robot
        pp.SetSpeed(speed, newturnrate);


        // stop scanning once finite object a reached certain distance
        if( minObjDist <= minDist )
        {
            std::cout << "I FOUND CENTER OF BOX!\n" << std::endl;
            speed = 0;  // newturnrate = -newturnrate;
            robot.Read();
            pp.SetSpeed(speed, newturnrate);
            break;
        }
    }

    return index;
}


double Locate::sumOfMagnitudes(int start, int end)
{
    double sum = 0;
    for(int i=start; i<=end; ++i)
    {
        sum+=lp[i];
    }

    return sum;
}

// returns the distance from robot to right edge of box
// assumes robot front facing box (forming a right degree angle)
double Locate::getRightHypotenuse()
{
    double rh = lp[getBoxRightIndex(middle)];

    if(rh != 0)
    {
        return rh;
    }
    return -1;
}


// returns the distance from robot to left edge of box
// assumes robot front facing box (forming a right degree angle)
double Locate::getLeftHypotenuse()
{
    double lh = lp[getBoxLeftIndex(middle)];

    if(lh != 0)
    {
        return lh;
    }
    return -1;
}


// returns true if tilt detected in box's orientation
bool Locate::didTilt(int iLeft, int iRight)
{
    double threshold = .2;
    double rh = getRightHypotenuse();
    double lh = getLeftHypotenuse();

    if( rh != -1 && iRight != -1 && abs( rh - iRight ) > threshold )
    {
        return true;
    }
    else if( lh != -1 && iLeft != -1 && abs( lh - iLeft ) > threshold )
    {
        return true;
    }

    return false;
}
