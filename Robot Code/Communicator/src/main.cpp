
#include <string>
#include <fstream>
#include "runasHub.h"
#include "runasrobot.h"

char ipRight[] = "10.42.0.42"; // IP address for Robot1
char ipLeft[] = "10.42.0.11"; // IP address for Robot2
char hostIP[] = "10.42.0.1"; // IP address for HUB

int pushFor = 75; // number of iterations to push box for
bool toError = 1; // HUB tell robotA to fail?


int getID();

int main(int argc, char *argv[])
{
    int ID = getID(); // 0=HUB, 1=Robot1(right), 2=Robot2(left)
    cout << "My ID is: " << ID << endl;

    if(ID == 0)
    {
        new RunAsHub(ipRight, toError);
    }

    else if(ID == 1){
        new RunAsRobot(ID, ipLeft, pushFor);
    }
    else if(ID == 2){
        new RunAsRobot(ID, hostIP, pushFor);
    }


}


// 0=HUB, 1=Robot1, 2=Robot2
int getID()
{
    int id = -1;

    ifstream inFile;

    // default path location is inside build folder
    inFile.open("../Communicator/myID.txt");
    if (!inFile) {
        cout << "Unable to open file ";
        exit(1); // terminate with error
    }

    inFile >> id;

    inFile.close();

    return id;
}
