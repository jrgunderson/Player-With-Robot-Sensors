/*
Copyright (c) 2005, Brad Kratochvil, Toby Collett, Brian Gerkey, Andrew Howard, ...
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the Player Project nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * laserobstacleavoid.cc
 *
 * a simple obstacle avoidance demo
 *
 * @todo: this has been ported to libplayerc++, but not tested
 */

#include <libplayerc++/playerc++.h>
#include <iostream>

#include "args.h"

#define RAYS 32

int speedFactor = 1;  // to speed up testing increase to 2
double maxSpeed = 0 * speedFactor;
int maxTurnRate = 0 * speedFactor;	
double minDist = .33 + (.15*speedFactor); // radius of roomba + some threshold

int
main(int argc, char **argv)
{
  parse_args(argc,argv);

  // we throw exceptions on creation if we fail
  try
  {
    using namespace PlayerCc;

    PlayerClient robot(gHostname, gPort);
    Position2dProxy pp(&robot, gIndex);
    LaserProxy lp(&robot, gIndex);
	RangerProxy rp(&robot, gIndex);
	BlobfinderProxy bfp(&robot, 0);

    std::cout << robot << std::endl;

    pp.SetMotorEnable (true);

    // go into read-think-act loop
    for(;;)
    {
      double newspeed = 0;
      double newturnrate = 0;

      // this blocks until new data comes; 10Hz by default
      robot.Read();

	// parameters
	int scanPoints = lp.GetCount();
	double right = scanPoints/8;
	double left = scanPoints-1 - scanPoints/8;
	newspeed = maxSpeed;

	// test methods of laserProxy
	// zero angle is straight ahead
	std::cout << "Count of Scan Points: " << lp.GetCount()
		<< "\nRange at min angle: " << lp[0]
		<< "\nRange at zero angle: " << lp[lp.GetCount()/2]
		<< "\nRange at max angle: " << lp[lp.GetCount()-1]
		<< std::endl;
	std::cout << "Distance Ahead: "<< lp[scanPoints/2] 
		<< " Left: "<< lp[left]<< " Right: " << lp[right] << std::endl;


	// test methods of rangerProxy
	std::cout << "Max Range: " << rp.GetMaxRange() << " "<< rp.GetRangeCount() 
		<< std::endl;
	std::cout << "Distance Ahead: "<< rp[scanPoints/2] 
		<< " Left: "<< rp[left]<< " Right: " << rp[right] << std::endl;

	
     std::cout << "speed: " << newspeed
                << " turn: " << newturnrate
                << std::endl;

      // write commands to robot
      pp.SetSpeed(newspeed, newturnrate);
    }
  }
  catch (PlayerCc::PlayerError & e)
  {
    std::cerr << e << std::endl;
    return -1;
  }


} // end main


