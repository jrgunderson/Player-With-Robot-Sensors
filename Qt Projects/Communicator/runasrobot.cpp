/*
 * State Machine for Robots
 *
 * Robot1 = Right Robot
 * Robot2 = Left Robot
 *
 * toError = Robot1 stops
*/

#include "runasrobot.h"

// remember d1 = HUB
//          d2 = other Robot
RunAsRobot::RunAsRobot(int id, Channel *c, int pushFor, bool toError)
{
    Locate* l = new Locate(c->d2, id, pushFor, toError);

    // wait to start
    if(id==1){
        cout << "waiting to start" << endl;
        l->wait2start();
    }

    int pushesRemain = l->run();


    // if Robot2 -> switch drivers to talk to HUB
    if(id == 2)
    {
         // if ERROR
         if(pushesRemain > 0)
         {
             c->d1->SendHelp();

             // wait for HUB to tell you what to do
             int move;
             for(;;)
             {
                 move = c->d1->getMove();
                 switch( move )
                 {
                     // just push box straight
                     case 1: l->push(pushesRemain); pushesRemain =0; break;

                     // push box alone (number of times to push each side)
                     case 2: l->pushBoxAlone(3); pushesRemain =0; break;

                     // wait for teleoperate to send signal
                     case 3:
                         l->wait4ready();
                         l->push(100);     // arbitrary push count,
                         pushesRemain = 0; // robot stops pushing when told to
                     break;
                 }
                 if(pushesRemain == 0){
                     break;
                 }
             }
         }

         // tell HUB task is complete
         c->d1->SendSuccess();
    }

    // Robot1 do this...
    else
    {
        bool giveup = false;

        // Regardless if ERROR or not...
        int move;
        for(;;)
        {
<<<<<<< HEAD
            l->stop();

            // if recieve signal from HUB (forwarded from Robot2) that finished task
            if(c->d2->isSuccessful())
=======
            // if recieve signal from HUB that finished task
            if(d->isSuccessful())
>>>>>>> parent of 1ec9d69... minor tweaks to teleop -> need to test
            {
                break;
            }

<<<<<<< HEAD
            // respond to teleoperation
            // forward messages from HUB to Robot2
            else
            {
                move = c->d2->getMove();

                // only make a move if move to be made
                if(move != -1)
                {
                    switch( move )
                    {
                        // teleoperation controls
                        case 0: l->stop(); c->d2->Error(); break; // to stop and have other robot stop with you
=======
            // else respond to teleoperation
            // OR forward messages from HUB to Robot2
            else{
                move = d->getMove();
                switch( move )
                {
                    // teleoperation controls
                    case 0: l->stop(); d->Error(); break; // to stop and have other robot stop with you
>>>>>>> parent of 1ec9d69... minor tweaks to teleop -> need to test

                    case 2: l->moveBackards(); sleep(1); break;

                    case 4: l->moveLeft(); sleep(1); break;

                    case 6: l->moveRight(); sleep(1); break;

                    case 8: l->moveForwards(); sleep(1); break;

<<<<<<< HEAD
                        // robot2 messages
                        case 1: c->d2->SendReady(); break;

                        case 9: c->d2->Error(); break;

                        case 11: c->d2->Move(1); sleep(1); giveup = true; break;
                        case 12: c->d2->Move(2); sleep(1); giveup = true; break;
                        case 13: c->d2->Move(3); sleep(1); break;

                        case 99: c->d2->SendSuccess(); giveup = true; break;
=======
                    // robot2 messages
                    case 1: d->SendReady(); break;

                    case 9: d->Error(); break;

                    case 11: d->Move(1); sleep(1); giveup = true; break;
                    case 12: d->Move(2); sleep(1); giveup = true; break;
                    case 13: d->Move(3); sleep(1); break;

                    case 99: d->SendSuccess(); giveup = true; break;
>>>>>>> parent of 1ec9d69... minor tweaks to teleop -> need to test

                    default: l->stop(); break;
                }
			 // stop between each move
                l->stop();
            }

            if(giveup){
                break;
            }

        }
    }



}

