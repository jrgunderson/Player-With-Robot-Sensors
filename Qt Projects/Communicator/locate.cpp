
/*
 * Task 1: - move towards box
 *
 * Task 2: - adjust until front facing box
 *
 * Task 3: - push box by alternating between corners
 *
 */

#include "locate.h"
#include "args.h"
#include <ctime>
#include "driver.h"


PlayerCc::PlayerClient robot(gHostname, gPort);
PlayerCc::Position2dProxy pp(&robot, gIndex);
PlayerCc::LaserProxy lp(&robot, gIndex);
PlayerCc::RangerProxy rp(&robot, gIndex);
time_t timer;
Driver* d;


Locate::Locate(){

}

void Locate::run()
{
    timer = time(0);

    std::cout << robot << std::endl;

    sleep(3);

    d = new Driver();

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


        // finally we can start pushing the box
        //pushBox(3); // for pushing the box by itself

        //pushRight(50);
        pushLeft(200);  // hard coded the timing for cooperative pushing



      } // end try
      catch (PlayerCc::PlayerError & e)
      {
        std::cerr << e << std::endl;
      }


    std::cout << "THE END " << std::endl;


    // clear system
    for(int i=0; i<10; ++i)
    {
        robot.Read();
        //robot.StopThread();
        //robot.Stop();
        pp.SetMotorEnable(false);
    }

}




// n = number of rounds to push for
void Locate::pushLeft(int n)
{
    goToLeftSide();
    wait(1);

    std::cout << "It took me: " << (time(0)-timer) << " seconds to get here" << std::endl;

    // wait for input to start pushing
    //waitForInput();

    // wait for ready message from other robot to push
    for(;;){

        if(d->isReady())
        {
            break;
        }
        else{
            wait(1);
        }
    }

    // magnitude of the box perpendicular
    double boxMag = sumOfMagnitudes(getBoxRightIndex(middle), getBoxLeftIndex(middle));

    // finally start pushing
    for(int i=0; i<n; ++i)
    {
        robot.Read();
        pp.SetSpeed(cap, 0.0);

//        // if other robot pushes its side too far
//        double newBoxMag = sumOfMagnitudes(getBoxRightIndex(middle), getBoxLeftIndex(middle));
//        std::cout << "Old Mag: " << boxMag << ", New Mag: " << newBoxMag << std::endl;

//        if( std::abs(boxMag - newBoxMag) > 1 )
//        {
//            std::cout << " Error Detected! " << std::endl;
//            wait(1);
//            waitForInput();
//        }

//        boxMag = newBoxMag;
    }

}



// n = number of rounds to push for

void Locate::pushRight(int n)
{
    goToRightSide();
    wait(1); // should be bound to wait for least amount of time possible

    std::cout << "It took me: " << (time(0)-timer) << " seconds to get here" << std::endl;

    // wait for input to start pushing
    //waitForInput();

	d->Ready();

    // get current distance to neighboring roomba
    double boxMag = sumOfMagnitudes(getBoxRightIndex(middle), getBoxLeftIndex(middle));

    // finally start pushing
    for(int i=0; i<n; ++i)
    {
        robot.Read();
        pp.SetSpeed(cap, 0.0);

//        // if other robot pushes its side too far
//        double newBoxMag = sumOfMagnitudes(getBoxRightIndex(middle), getBoxLeftIndex(middle));
//        std::cout << "Old Mag: " << boxMag << ", New Mag: " << newBoxMag << std::endl;

//        if( std::abs(boxMag - newBoxMag) > 1 )
//        {
//            std::cout << " Error Detected! " << std::endl;
//            wait(1);
//            waitForInput();
//        }

//        boxMag = newBoxMag;
    }
}


void Locate::waitForInput()
{
    char input;
    while( input != 'y')
    {
        std::cout << "Should i start pushing?" << std::endl;

        // prevents from crashing if wrong input type
        if( !(std::cin >> input) )
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
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



// n =  number of times to go back and forth
void Locate::pushBox(int n)
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
    if(newturnrate != 0)
    {
        newturnrate = 0;
    }
    if(speed <= 0)
    {
        speed = cap;
    }

    for(int i=0; i<t; ++i)
    {
        robot.Read();
        pp.SetSpeed(speed, newturnrate);
    }

    speed = 0;
    robot.Read();
    pp.SetSpeed(speed, newturnrate);

}


// send robot to right side of box
void Locate::goToRightSide()
{
    // assuming robot front-facing box -> turn left 90 degrees
    turnRight(middle);
    adjustRight(left);

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


// finds right index of box
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

// finds left index of box
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


// algorithm move away from walls but towards a box
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
