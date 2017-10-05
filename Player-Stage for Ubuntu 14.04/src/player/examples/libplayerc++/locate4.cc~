
/*
 * Read-Think-Act loop 1: - move away from walls and move towards center of box until certain dist
 *
 * Read-Think-Act loop 2: - once cleared walls, continue to move towards center of box
 * 
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <cmath>

#include "args.h"

#define RAYS 32

double speed = .3;  // in meters per second	
double minDist = .25;
double minRadius = .75;


PlayerCc::PlayerClient robot(gHostname, gPort);
PlayerCc::Position2dProxy pp(&robot, gIndex);
PlayerCc::LaserProxy lp(&robot, gIndex);
PlayerCc::RangerProxy rp(&robot, gIndex);


// functions
int getSizeLeft(int index);
int getSizeRight(int index);
int getSizeStraight(int index);
int getMiddleIndex(int index);

int main(int argc, char **argv)
{
  parse_args(argc,argv);

  // we throw exceptions on creation if we fail
  try
  {
	std::cout << robot << std::endl;

	pp.SetMotorEnable (true);

	robot.Read();

	// read parameters
	int scanPoints = lp.GetCount();
	int thirtyDegrees = scanPoints/8;
	int fortyFiveDegrees = scanPoints/5.3;
	int right = thirtyDegrees; // -90 degrees from center
	int left = scanPoints-1 - thirtyDegrees; // 90 degrees from center
	int straight = scanPoints/2;
	double maxRange = lp.GetMaxRange();
	// size that is definitely not a box
	int minWallSize = 200;
	
	int leftEye = straight + thirtyDegrees;
	int rightEye = straight - thirtyDegrees;

	std::cout << rightEye << " -> " << leftEye << std::endl;

	double newturnrate = 0; // in radians per seconds

	// initialize variables
	int index = -1;
	int boxSize = scanPoints;
	bool isWall = true;
	

	// go into read-think-act loop 1 (move until cleared all walls)
    	for(;;)
    	{
		robot.Read();

		// keep initializing to max distance
		double minObjDist = maxRange;

		// locate corner of nearest obstacle (presumably a box) 
		for (int i=rightEye; i<leftEye; ++i)
		{
			double pointDistance = lp[i];
			// search for shortest datapoint
			// >.02 cuz sometimes range returns weirdly low numbers for no reason
			if( pointDistance > .02 && pointDistance < minObjDist )
			{
				minObjDist = pointDistance;
				index = i;
			}
		}

		std::cout << "\nCorner index " << index << std::endl;


		int rightSize = -1;
		int leftSize = -1;

		// if index in middle view of roomba
		if (index > straight -5 && index < straight +5 )
		{
			boxSize = getSizeStraight(index);
		}
		// need to figure out which corner box is facing
		else{
			leftSize = getSizeLeft(index);
			rightSize = getSizeRight(index);
		}

		
		// calculate middle data point for front of box
		if( leftSize > rightSize ) // if left of center
		{
			boxSize = leftSize;
			index = (boxSize/2) + index;
			std::cout << "Left size: " << boxSize << std::endl;

		}	
		else if( rightSize > leftSize ) // if right of center
		{
			boxSize = rightSize;
			index = index - (boxSize/2);
			std::cout << "Right size: " << boxSize << std::endl;
		}
		else{
			//index = getMiddleIndex(index);
			std::cout << "Middle size: " << boxSize << std::endl;
		}


		// turn the robot until front facing middle of box
		// turn rate increases as it gets closer to object
		//if( index > (straight+5) ) // if left of center
		if( index > straight ) // if left of center
		{
			newturnrate = 1/(8*minObjDist); // turn left 

		}	
		//else if( index < (straight-5) ) // if right of center
		else if( index < straight ) // if right of center
		{
			newturnrate = -1/(8*minObjDist); // turn right
		}
		else{
			newturnrate = 0;
		}


		std::cout << "Middle of Box at DataPoint: " << index 
				<< ", Distance: "<< minObjDist << std::endl;

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



	// go into read-think-act loop 2 (overshoot center of box by a little)
    	for(;;)
    	{
		robot.Read();

		// keep initializing to max distance
		double minObjDist = maxRange;

		// locate corner of nearest obstacle (presumably a box) 
		for (int i=rightEye; i<leftEye; ++i)
		{
			double pointDistance = lp[i];
			// search for shortest datapoint
			// >.02 cuz sometimes range returns weirdly low numbers for no reason
			if( pointDistance > .02 && pointDistance < minObjDist )
			{
				minObjDist = pointDistance;
				index = i;
			}
		}

		std::cout << "\nCorner index " << index << std::endl;


		int rightSize = -1;
		int leftSize = -1;

		// if index in middle view of roomba
		if (index > straight -5 && index < straight +5 )
		{
			boxSize = getSizeStraight(index);
		}
		// need to figure out which corner box is facing
		else{
			leftSize = getSizeLeft(index);
			rightSize = getSizeRight(index);
		}

		int offsetIndex = index;		

		// calculate middle data point for front of box
		if( leftSize > rightSize ) // if left of center
		{
			index = (boxSize/2) + index;
			boxSize = leftSize;
			std::cout << "Left size: " << boxSize << std::endl;

		}	
		else if( rightSize > leftSize ) // if right of center
		{
			index = index - (boxSize/2);
			boxSize = rightSize;
			std::cout << "Right size: " << boxSize << std::endl;
		}
		else{
			//index = getMiddleIndex(index);
			std::cout << "Middle size: " << boxSize << std::endl;
		}


		// turn the robot until front facing middle of box
		// turn rate increases as it gets closer to object
		//if( index > (straight+5) ) // if left of center
		if( offsetIndex > straight ) // if left of center
		{
			newturnrate = 1/(8*minObjDist); // turn left 

		}	
		//else if( index < (straight-5) ) // if right of center
		else if( offsetIndex < straight ) // if right of center
		{
			newturnrate = -1/(8*minObjDist); // turn right
		}
		else{
			newturnrate = 0;
		}


		// cap turnrate at .15
		if( newturnrate > .2 )
		{
			newturnrate = .2;
		}
		if( newturnrate < -.2 )
		{
			newturnrate = -.2;
		}


		std::cout << "Middle of Box at DataPoint: " << index 
				<< ", Distance: "<< minObjDist << std::endl;

		std::cout << "speed: " << speed
				  << " turn: " << newturnrate  << std::endl;

		// write commands to robot
		pp.SetSpeed(speed, newturnrate);


		// stop scanning once finite object a reached certain distance
		if( lp[index] <= minDist )
		{
			std::cout << "I FOUND CENTER OF BOX!" << std::endl;
			speed = 0;  newturnrate = -newturnrate;
			break;
		}
	
    	} // end think-read-react loop 2


	// get system caught up with robot && turn back towards box
	for( int i=0; i<5; ++i )
	{
		robot.Read();
		pp.SetSpeed(speed, newturnrate);
	}
	


	int rightBoxIndex = -1;
	for( int i = index; i>0; --i )
	{
		if( lp[i-1] <= 0.01 ){ continue; }

		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i-1] - lp[i]) > .5 )
		{
			rightBoxIndex = i;
			break;
		}
	}
	
	int leftBoxIndex = -1;
	for( int i = index; i<681; ++i )
	{
		if( lp[i+1] <= 0.01 ){ continue; }
		
		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i+1] - lp[i]) > .5 )
		{
			leftBoxIndex = i;
			break;
		}
	}

	
	std::cout << "Box from index: " << rightBoxIndex << " -> " << leftBoxIndex << std::endl;
	

	

  } // end try 
  catch (PlayerCc::PlayerError & e)
  {
    std::cerr << e << std::endl;
    return -1;
  }
	
} // end main


// returns size of box if index is to the left of the robot's center
int getSizeLeft(int index)
{
	for( int i = index; i<681; ++i )
	{
		if( lp[i+1] <= 0.01 ){ continue; }
		
		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i+1] - lp[i]) > .5 )
		{
			return i+1 - index; // size = total length in dataPoints
		}
	}

	// if reached this point, then continuous
	return 999;
}	

// returns size of box if index is to the right of the robot's center
int getSizeRight(int index)
{
	for( int i = index; i>0; --i )
	{
		if( lp[i-1] <= 0.01 ){ continue; }

		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i-1] - lp[i]) > .5 )
		{
			return index - i-1; // size = total length in dataPoints
		}
	}

	// if reached this point, then continuous
	return 999;
}

// returns middle index for box directly in front of sensor
int getMiddleIndex(int index)
{
	int endIndex = -1;
	int startIndex = -1;
	for( int i = index; i<681; ++i )
	{
		if( lp[i+1] <= 0.01 ){ continue; }

		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i+1] - lp[i]) > .5  )
		{
			endIndex = i+1;
			break;
		}
	}
	for( int i = index; i>0; --i )
	{
		if( lp[i-1] <= 0.01 ){ continue; }

		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i-1] - lp[i]) > .5 )
		{
			startIndex = i-1;
			break;
		}
	}

	int size = endIndex - startIndex;

	return (size/2) + startIndex;
}

// returns size of box if directly in front of laser sensor
int getSizeStraight( int index)
{
	int endIndex = -1;
	int startIndex = -1;
	for( int i = index; i<681; ++i )
	{
		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i+1] - lp[i]) > .5 )
		{
			endIndex = i+1;
			break;
		}
	}
	for( int i = index; i>0; --i )
	{
		// box ends once no longer incrementally increasing consecutive distances
		if( std::abs(lp[i-1] - lp[i]) > .5 )
		{
			startIndex = i-1;
			break;
		}
	}

	return endIndex - startIndex;
}






