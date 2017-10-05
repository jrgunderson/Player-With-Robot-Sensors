
/* 
 * iRobot will locate a box then go to it
 */

#include <libplayerc++/playerc++.h>
#include <iostream>

#include "args.h"

#define RAYS 32

// in meters / second
double speed = .3;
// distance from sensor to object	
double minDist = .17; 
// radius of roomba
double minRadius = .33;

PlayerCc::PlayerClient robot(gHostname, gPort);
PlayerCc::Position2dProxy pp(&robot, gIndex);
PlayerCc::LaserProxy lp(&robot, gIndex);
PlayerCc::RangerProxy rp(&robot, gIndex);


int main(int argc, char **argv)
{
  parse_args(argc,argv);

  // we throw exceptions on creation if we fail
  try
  {

    std::cout << robot << std::endl;

    pp.SetMotorEnable (true);

      // read parameters
      robot.Read();

	// parameters
	int scanPoints = lp.GetCount();
	int thirtyDegrees = scanPoints/8;
	int fortyFiveDegrees = scanPoints/5.3;
	int right = thirtyDegrees; // -90 degrees from center
	int left = scanPoints-1 - thirtyDegrees; // 90 degrees from center
	int straight = scanPoints/2;
	double maxRange = lp.GetMaxRange();
	double newturnrate = 0; // in radians per seconds

	int leftEye = straight + thirtyDegrees;
	int rightEye = straight - thirtyDegrees;

	std::cout << "maxRange: " << maxRange << std::endl;
	std::cout << "From index: " << rightEye << " -> " << leftEye << std::endl;
	

    // go into read-think-act loop
    for(;;)
    {

      // this blocks until new data comes; 10Hz by default
      robot.Read();
	
	double min = maxRange;
	int index = -1;
	// locate corner of nearest obstacle (presumably a box) 
	// only use datapoints from 30 degrees to -30 degrees
	for (int i=rightEye; i<leftEye; ++i)
	{
		double pointDistance = lp[i];
		// return shortest datapoint
		// >.02 cuz sometimes range returns weirdly low numbers for no reason
		if( (pointDistance < min) && (pointDistance > .02) )
		{
			min = pointDistance;
			index = i;
		}
	}
		
	// if box in front of middle 20 datapoints
	// go towards the box until certain distance away

	// turn the robot until front facing box
	// turn rate shouldn't be fast
	if( index > (straight+5) ) // if left of center
	{
		newturnrate = .1; // turn left
		
	}	
	else if( index < (straight-5) ) // if right of center
	{
		newturnrate = -.1; // turn right
	}

	std::cout << "Box at DataPoint: " << index 
			<< ", Distance: "<< min << std::endl;
	
	// when reached that distance -> stop in front of the box
	if( min <= minDist )
	{
		std::cout << "I FOUND A BOX!" << std::endl;
		break;
	}
	
     std::cout << "speed: " << speed
                << " turn: " << newturnrate
                << std::endl;

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












