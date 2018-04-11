
/* This class controls all of the Robot's movements
 *  && uses Driver to send messages as well as react to incoming messages
 *
 *
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
 * * Tasks 1-3 are in autonomous read-think-act loops
 */

#include "args.h"
#include "locate.h"


PlayerCc::PlayerClient *robot;
PlayerCc::Position2dProxy *pp;
PlayerCc::LaserProxy *lp;
PlayerCc::RangerProxy *rp;
time_t timer;
const int YES = 0; // for clarity, variable that translates 0 -> succesfull push


// constructor
Locate::Locate(Driver* driver, int id, int pushfor)
{
    PlayerCc::PlayerClient robot(gHostname, gPort);
    PlayerCc::Position2dProxy pp(&robot, gIndex);
    PlayerCc::LaserProxy lp(&robot, gIndex);
    PlayerCc::RangerProxy rp(&robot, gIndex);

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

    print(robot);

    // throw exceptions on creation if fail
    try{

        pp->SetMotorEnable(true);

        robot->Read();

        // read Laser Ranger parameters
        maxRange = lp->GetMaxRange(); // furthest distance laser can read
        scanPoints = lp->GetCount(); // total datapoints on laser
        middle = scanPoints/2;
        int thirtyDegrees = scanPoints/8;
        right = thirtyDegrees; // -90 degrees from center
        left = scanPoints-1 - thirtyDegrees; // 90 degrees from center
        int fortyFiveDegrees = scanPoints/5.3;
        rightEye = middle - fortyFiveDegrees; // 'eyes' used to narrow robot's vision
        leftEye = middle + fortyFiveDegrees;

        print(rightEye, " -> ", leftEye);


        int index = -1; // index on laser where box is located
        double boxSize = scanPoints; // initialize box size to max

        // second robot waits for first to tell it, it can start
        if(ID == 2){
            print("waiting for other robot");
            wait2start();
        }

        // TASK 1
        index = avoidWalls(); // move towards box while avoiding walls
        index = locateBox();  // move towards box after 'locking on'


        // tell me info about the box
        int rightBoxIndex = getBoxRightIndex(index);
        int leftBoxIndex = getBoxLeftIndex(index);
        index = (leftBoxIndex + rightBoxIndex)/2;

        print("Box from index: ", rightBoxIndex, " -> ", leftBoxIndex);
        print("Middle at: ", index);

        boxSize = 2*sqrt( std::pow(lp->GetRange(rightBoxIndex),2) + pow(lp->GetRange(index),2) );
        print("Size: ", boxSize, " meters");



        // TASK 2: turn until datapoint reads shortest distance from box
        // this indicates robot is aligned front-facing
        if( index < middle )
        {
            adjustRight(middle);
        }
        else
        {
            adjustLeft(middle);
        }

        // TASKS 3 & 4
        if(ID == 1){ // robot1 move to the right side & push
            success = pushRight(pushFor); // in here Robot1 calls over Robot2
        }
        else{ // robot2 move to the left side & push
            success = pushLeft(pushFor);
        }

        clear(); // clear out sensor data


    } // end try
    catch (PlayerCc::PlayerError & e)
    {
        std::cerr << e << std::endl;
    }

    // returns 0 if successful, else returns remainder of distance box needs to be pushed
    return success;
}


// clear system
void Locate::clear()
{
    for(int i=0; i<10; ++i)
    {
        robot->Read();
        pp->SetMotorEnable(false);
    }
}

void Locate::slow()
{
    robot->Read();
    pp->SetSpeed( speed*(4/5.0), newturnrate*(4/5.0) );
}

void Locate::stop()
{
    robot->Read();
    pp->SetSpeed(0.0, 0.0);
    speed = 0.0;
    newturnrate = 0.0;
}

void Locate::moveBackards()
{
    speed = -cap;
    newturnrate = 0.0;
    robot->Read();
    pp->SetSpeed(speed, newturnrate);
}

void Locate::moveForwards()
{
    speed = cap;
    newturnrate = 0.0;
    robot->Read();
    pp->SetSpeed(speed, newturnrate);
}

void Locate::moveRight()
{
    speed = 0.0;
    newturnrate = -cap;
    robot->Read();
    pp->SetSpeed(speed, newturnrate);
}

void Locate::moveLeft()
{
    speed = 0.0;
    newturnrate = cap;
    robot->Read();
    pp->SetSpeed(speed, newturnrate);
}


// n = number of rounds to push for
// returns 0 if successfull
//          else if unsuccessfull -> returns # of iterations remaining to push
int Locate::pushLeft(int n)
{
    goToLeftSide();

    print( "It took me: ", (time(0)-timer), " seconds to get here");

    d->SendReady(); // send that you're ready to push!
    wait4ready(); // wait for other robot to acknowledge it is ready


    // finally start pushing
    for(int i=n; i>=0; --i)
    {
        robot->Read();
        pp->SetSpeed(cap, 0.0);


        // if other robot malfunctions
        if(d->isError())
        {
            stop();
            print( "HELP! WHAT TO DO!?" );
            return i; // return how many iterations there are left to push
        }

    }
    // return 0 iterations remaining to push (successfully pushed for planned distance)
    return YES;
}



// n = number of rounds to push for
// returns 0 if successfull
//          else if unsuccessfull -> returns # of iterations remaining to push
int Locate::pushRight(int n)
{

    goToRightSide();

    print("It took me: ", (time(0)-timer), " seconds to get here");

    wait4ready(); // wait for ready message from other robot to push
    d->SendReady(); // tell other robot you received their ready message

    // finally start pushing
    for(int i=n; i>=0; --i)
    {
        robot->Read();
        pp->SetSpeed(cap, 0.0);


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
    // return 0 iterations remaining to push (successfully pushed for planned distance)
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
        robot->Read();
        pp->SetSpeed(-cap, 0.0);
    }

    // pseudo 'shut-down' robot
    wait(1);
    pp->SetMotorEnable(false);

}


// n = how long to wait for
void Locate::wait(int n )
{
    for(int i=0; i<n; ++i)
    {
        robot->Read();
        pp->SetSpeed(0.0, 0.0);
    }
}


// wait for 'ready' or 'end' message
// returns true if exiting current task
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
            return false;
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
// returns 0 if pushed successfull
int Locate::pushBoxAlone(int n)
{
    int stop = false;
    for( int i=0; i<n; ++i)
    {
        stop = goToRightSide();
        stop = push(20);
        stop = goToLeftSide();
        stop = push(25);
    }

    // any number other than 0 means task interrupted
    return stop;
}


// t = iterations to push box for
// returns iterations remaining if interrupted
int Locate::push(int t)
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
    for(int i=t; i>=0; --i)
    {
        robot->Read();
        pp->SetSpeed(speed, newturnrate);


        // will pause if receive error
        if( d->isError() )
        {
            over = wait4ready();

            // will exit if received End_Task signal while waiting
            if(over){
                return i;
            }
        }
    }

    // set speed back to zero
    speed = 0;
    robot->Read();
    pp->SetSpeed(speed, newturnrate);

    return YES; // return 0 iterations remaining to push
}


// send robot to right side of box
// returns 'true' if quitting task
bool Locate::goToRightSide()
{
    // assuming robot front-facing box -> turn right 90 degrees
    turnRight(middle);
    adjustRight(left); // adjust until left datapoint perpendicular to box

    // tell other robot it can start
    if(ID == 1)
    {
        d->SendStart(toError); // actually doesn't matter if
    }                          // other robot knows if error will be introduced

    // assuming robot's eyesight is parallel to box
    // move forward until "right eye" opens up
    bool stop = moveForwardFromLeft(leftEye);

    // assuming robot's eyesight is parallel to box -> turn left 90 degrees
    turnLeft(left);
    adjustLeft(middle);

    return stop;
}


// send robot to left side of box
// returns 'true' if quitting task
bool Locate::goToLeftSide()
{
    // assuming robot front-facing box -> turn left 90 degrees
    turnLeft(middle);
    adjustLeft(right); // adjust until right datapoint perpendicular to box

    // assuming robot's eyesight is parallel to box
    // move forward until "right eye" opens up
    bool stop = moveForwardFromRight(rightEye);

    // assuming robot's eyesight is parallel to box -> turn right 90 degrees
    turnRight(right);
    adjustRight(middle);

    return stop;
}


// move forward assuming box on right side
// returns 'true' if quitting task
bool Locate::moveForwardFromRight(int dp)
{
    print("\nMoving Forward\n");


    if(newturnrate != 0)
    {
        newturnrate = 0;
    }
    if(speed <= 0)
    {
        speed = cap;
    }


    bool over = false; // flag for recieving task completion message
    double boxDist = 999;
    for(;;)
    {
        robot->Read();

        // box ends once no longer incrementally increasing consecutive distances
        for( int i=dp-5; i<dp+5; ++i ) // in case it passed the end when looping
        {

            print(lp->GetRange(i-1), " - ", lp->GetRange(i), " > .5?");

            if( abs(lp->GetRange(i+1)- lp->GetRange(i)) > .5 || lp->GetRange(i+1) == 0 )
            {
                speed = 0;
                robot->Read();
                pp->SetSpeed(speed, newturnrate);
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
            distAvg += lp->GetRange(i);
        }
        distAvg /= 10;

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

        print("\noldDist: ", boxDist, ", vs newDist: ", distAvg);
        print("speed: ", speed, ", turnrate: ", newturnrate);


        pp->SetSpeed(speed, newturnrate);

        boxDist = distAvg;


        // will pause if receive error
        if( d->isError() )
        {
            over = wait4ready();

            // will exit if received End_Task signal while waiting
            if(over){
                return true;
            }
        }
    }// end for(;;)
    return 0;
}


// move forward assuming box on left side
// returns 'true' if quitting task
bool Locate::moveForwardFromLeft(int dp)
{
    print("\nMoving Forward\n");


    if(newturnrate != 0)
    {
        newturnrate = 0;
    }
    if(speed <= 0)
    {
        speed = cap;
    }


    bool over = false; // flag for recieving task completion message
    double boxDist = 999;
    for(;;)
    {
        robot->Read();

        print( dp );

        // box ends once no longer incrementally increasing consecutive distances
        for( int i=dp+5; i>=dp-5; --i )
        {
            print(lp->GetRange(i-1), " - ", lp->GetRange(i), " > .5?");

            // box ends once jump in distance between laser indices
            if( abs(lp->GetRange(i-1)- lp->GetRange(i)) > .5 || lp->GetRange(i-1) == 0  )
            {
                speed = 0;
                robot->Read();
                pp->SetSpeed(speed, newturnrate);
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
            distAvg += lp->GetRange(i);
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

        print("\noldDist: ", boxDist, ", vs newDist: ", distAvg);
        print("speed: ", speed, ", turnrate: ", newturnrate);

        pp->SetSpeed(speed, newturnrate);

        boxDist = distAvg;


        // will pause if receive error
        if( d->isError() )
        {
            over = wait4ready();

            // will exit if received End_Task signal while waiting
            if(over){
                return true;
            }
        }
    }// end for(;;)
    return 0;
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

    double eye = lp->GetRange(dp);
    for( ;; )
    {
        robot->Read();

        print("Eye see: ", eye);
        print( lp->GetRange(dp) );

        // box ends once no longer incrementally increasing consecutive distances
        if( abs(lp->GetRange(dp) - eye) > .5 || lp->GetRange(dp) <= .01 )
        {
            newturnrate = 0;
            robot->Read();
            pp->SetSpeed(speed, newturnrate);
            break;
        }

        print( "turnrate: ", newturnrate);
        pp->SetSpeed(speed, newturnrate);

        eye = lp->GetRange(dp);
    }
}

// turn left
void Locate::turnLeft(int dp)
{
    print("\nTurning Left\n");

    if(newturnrate < cap)
    {
        newturnrate = cap;
    }
    if(speed != 0)
    {
        speed = 0;
    }

    double eye = lp->GetRange(dp);
    for(;;)
    {
        robot->Read();

        print("Eye see: ", eye);
        print( lp->GetRange(dp) );

        // box ends once no longer incrementally increasing consecutive distances
        if( abs(lp->GetRange(dp) - eye) > .5 || lp->GetRange(dp) <= .01 )
        {
            newturnrate = 0;
            robot->Read();
            pp->SetSpeed(speed, newturnrate);
            break;
        }

        pp->SetSpeed(speed, newturnrate);

        eye = lp->GetRange(dp);
    }
}


// robot adjusts to front face box perfectly perpendicularly
// compares distances from dp -> LeftBoxIndex
void Locate::adjustLeft(int dp)
{
    print("\nAdjusting Left\n");

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

    for(;;)
    {
        robot->Read();

        // compare with upcoming values
        double avg = 0;
        int end = getBoxLeftIndex(dp);

        print(dp, " -> ", end);

        // datapoint at which box ends will continously change as robot turns
        for(int i=dp; i<end; ++i )
        {
            avg += lp->GetRange(i);
        }
        avg = avg/(end-dp+1);

        print("\navg:  ", avg);
        print("avg1: ", avg1, ", avg2: ", avg2);


        // break if consistently increasing
        if(avg >= avg1 && avg1 >= avg2)
        {
            newturnrate = 0;
            robot->Read();
            pp->SetSpeed(speed, newturnrate);
            break;
        }

        // keeps track of previous 2 avgs
        if(trial == 0)
        {
            avg1 = avg; // only 1 previous avg to save
            ++trial;
        }
        else{
            avg2 = avg1;
            avg1 = avg;
        }

        pp->SetSpeed(speed, newturnrate);

    }
}


// robot adjusts to front face box perfectly perpendicularly
// compares distances from dp -> RightBoxIndex
void Locate::adjustRight(int dp)
{
    print("\nAdjusting Right\n");

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

    for(;;)
    {
        robot->Read();

        // compare with upcoming values
        double avg = 0;
        int end = getBoxRightIndex(dp);

        // datapoint at which box ends will continously change as robot turns
        for(int i=dp; i>=end; --i )
        {
            avg += lp->GetRange(i);
        }
        avg = avg/(dp-end+1);

        print("\navg:  ", avg);
        print("avg1: ", avg1, ", avg2: ", avg2);


        // break if consistently increasing
        if(avg >= avg1 && avg1 >= avg2)
        {
            newturnrate = 0;
            robot->Read();
            pp->SetSpeed(speed, newturnrate);
            break;
        }

        // keeps track of previous 2 avgs
        if(trial == 0)
        {
            avg1 = avg; // only 1 previous avg to save
            ++trial;
        }
        else{
            avg2 = avg1;
            avg1 = avg;
        }

        pp->SetSpeed(speed, newturnrate);

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
        double pointDistance = lp->GetRange(i);
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
        if( abs(lp->GetRange(i-1) - lp->GetRange(i)) > .5 || lp->GetRange(i) == 0 )
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
        if( abs(lp->GetRange(i+1) - lp->GetRange(i)) > .5 || lp->GetRange(i) == 0 )
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


// Autonomously move away from walls but towards a box
//      starts slow, but speed increases as it approaches box
// ..Until box within certain range
int Locate::avoidWalls()
{
    // initialize variables
    int index = -1;
    int boxSize = scanPoints;
    bool isWall = true;

    // go into read-think-act loop 1 (move until cleared all walls)
    for(;;)
    {
        robot->Read();


        // locate corner of nearest obstacle (presumably a box)
        index = shortestIndex(rightEye, leftEye);
        double minObjDist = lp->GetRange(index);

        print("\nCorner index ", index, "@ dist: ", minObjDist);

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
        else{ // box straight ahead
            newturnrate = 0;
        }

        print("Size of Box: ", boxSize, ", Middle index: ", index);
        print("speed: ", speed, " turn: ", newturnrate);

        print("isWall? ", isWall); // tell me if you're moving towards a wall


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
        pp->SetSpeed(speed, newturnrate);


        // stop scanning once finite object a reached certain distance
        if( minObjDist <= minRadius && !isWall )
        {
            print("I FOUND A BOX!");
            break;
        }

    } // end think-read-react loop 1

    return index;
}


// Autonomously locates box (slows down as it approaches)
int Locate::locateBox()
{
    // initialize variables
    int index = -1;
    int boxSize = scanPoints;

    for(;;)
    {
        robot->Read();

        // locate corner of nearest obstacle (presumably a box)
        index = shortestIndex(rightEye, leftEye);
        double minObjDist = lp->GetRange(index);

        print("\nCorner index ", index, " @ dist: ", minObjDist);

        boxSize = getBoxSize(index);
        index = getMiddleIndex(index);

        // slow down as robot aproaches box
        double newSpeed = pow(minObjDist,2);

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

        print("Size of Box: ", boxSize, ", Middle index: ", index);
        print("speed: ", speed, " turn: ", newturnrate);


        // write commands to robot
        pp->SetSpeed(speed, newturnrate);


        // stop scanning once finite object reached certain distance
        if( minObjDist <= minDist )
        {
            print("I FOUND CENTER OF BOX!\n");
            speed = 0;
            robot->Read();
            pp->SetSpeed(speed, newturnrate);
            break;
        }
    }

    return index;
}



//// To reduce typing  cout << <message, variable> << endl;
template<typename T1, typename T2, typename T3, typename T4>
void Locate::print( T1 a, T2 b, T3 c, T4 d )
{
    cout << a << b << c << d << endl;
}
