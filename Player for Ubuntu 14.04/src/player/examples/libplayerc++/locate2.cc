
/* 
 * 2 seperate "for;;" loops
 *   - locate box, -then go to it
 * 
 * NOT a good algorithm
 */

#include <libplayerc++/playerc++.h>
#include <iostream>

#include "args.h"

#define RAYS 32

// in meters / second
double speed = .25;
// distance from sensor to object
double minDist = .17;
// radius of roomba	
double minRadius = .33; 


PlayerCc::PlayerClient robot(gHostname, gPort);
PlayerCc::Position2dProxy pp(&robot, gIndex);
PlayerCc::LaserProxy lp(&robot, gIndex);
PlayerCc::RangerProxy rp(&robot, gIndex);


// parameters initialized to -1 so we know if error
int scanPoints = 682;
int thirtyDegrees = -1;
int fortyFiveDegrees = -1;
int right = -1; // -90 degrees from center
int left = -1; // 90 degrees from center
int middle = -1;
double maxRange = -1;
double newturnrate = 0; // in radians per seconds
int rightEye = -1;
int leftEye = -1;


// functions
int locateBox();

int
main(int argc, char **argv)
{
  parse_args(argc,argv);

  // we throw exceptions on creation if we fail
  try
  {

    std::cout << robot << std::endl;

    pp.SetMotorEnable (true);

     // read parameters
     robot.Read();
	scanPoints = lp.GetCount();
	thirtyDegrees = scanPoints/8;
	fortyFiveDegrees = scanPoints/5.3;
	right = thirtyDegrees; 
	left = scanPoints-1 - thirtyDegrees; 
	middle = scanPoints/2;
	maxRange = lp.GetMaxRange();
	rightEye = middle - thirtyDegrees;
	leftEye = middle + thirtyDegrees;

	// locate box
	double boxDist = locateBox();


	std::cout << "From index: " << rightEye
		<< " -> " << leftEye << std::endl;

	std::cout << "middle index= " << middle << std::endl;

	// turn roomba to face box
	bool facing = false;
	for (;;)
	{
		// make sure robot is reading
		robot.Read();

		std::cout << lp[middle] << std::endl;

		for( int i= middle-5; i<= middle+5; ++i)
		{
			if( lp[i] <= boxDist + .05 && lp[i] > .02 )
			{
				facing = true;
			}
		}

		if( facing )
		{
			// stop turning
			newturnrate = 0;
			pp.SetSpeed(speed, newturnrate);
			break;
		}
	}



    // go into read-think-act loop
    for(;;)
    {
	
      // this blocks until new data comes; 10Hz by default
      robot.Read();

	std::cout << lp[middle] << std::endl;
	
	// when reached that distance -> stop in front of the box
	if( lp[middle] <= minDist && lp[middle] > .02)
	{
		std::cout << "I FOUND A BOX!" << std::endl;
		break;
	}
	
     std::cout << "speed: " << speed
                << " turn: " << newturnrate << std::endl;

      // write commands to robot
      pp.SetSpeed(speed, newturnrate);

	
    } // end think-read-react loop
	


  } // end try 
  catch (PlayerCc::PlayerError & e)
  {
    std::cerr << e << std::endl;
    return -1;
  }
	

} // end main



// find closest non-continuous object
int locateBox()
{
	double boxDist = maxRange;
	int boxIndex = -1;
	// locate corner of nearest obstacle 
	for (int i=rightEye; i<leftEye; ++i)
	{
		double pointDistance = lp[i];
		// return smallest datapoint
		// >.02 cuz sometimes range returns weirdly low numbers for no reason
		if( (pointDistance < boxDist) && (pointDistance > .02) )
		{
			boxDist = pointDistance;
			boxIndex = i;
		}
	}

	//update turnrate
	if( boxIndex > (middle+5) ) // if left of center
	{
		newturnrate = .1; // turn left

	}	
	else if( boxIndex < (middle-5) ) // if right of center
	{
		newturnrate = -.1; // turn right
	}

	// write commands to robot
	pp.SetSpeed(speed, newturnrate);

	std::cout << "Box at DataPoint: " << boxIndex 
			<< ", Distance: "<< boxDist << std::endl;

	return boxDist;
}








