/*
 * communicator.cpp
 * Ian Stodart @ 2017
 */

#include "communicator.h"

#define MAXBUF 1024 // maximum length of the buffer

#define H 0 // used in help
#define R 1 // used in request


char *ip_addr;
int sfd;
int lfd;

bool toStart;
bool startBroken;
bool isReady;
bool isError;
bool needHelp;
bool isSuccessful;
int this_move;

extern "C"{
    int itoa(int n, char s[]);
    int create_listen(int, int);
    int create_send(char *, int, int);
    int listen_to_robot(int sockfd, char *msg);
    int Communicator_to_one(int sockfd, char *msg, int);
    int talk_to_one(int sockfd, char *msg, int);
}
Communicator::Communicator(char *ip, int p)
{
    port = p;

    ip_addr = ip;

    //cout << ip_addr << ", " << port << " \n";
}

//For Robot
void Communicator::send_Bid(int rn, int str, int dist){

    // create a message
    char *msg = NULL;
    char *char_rn = NULL;
    char *char_str = NULL;
    char *char_dist = NULL;

    msg = (char *) malloc(60*sizeof(char));
    char_rn = (char *) malloc(10*sizeof(char));
    char_str = (char *) malloc(10*sizeof(char));
    char_dist = (char *) malloc(10*sizeof(char));


    itoa((int)rn, char_rn);
    itoa((int)str, char_str);
    itoa((int)dist, char_dist);

    strcpy(msg, "B");
    strcat(msg, "$");
    strcat(msg, char_rn);
    strcat(msg, "$");
    strcat(msg, char_str);
    strcat(msg, "$");
    strcat(msg, char_dist);
    strcat(msg, "!");

    send_cmd(sfd, msg);
}


//For Desktop
void Communicator::send_Start(int e){
    // create a message
    char *msg = NULL;
    char &c = to_string(e)[0];

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "S");
    strcat(msg, &c);
    strcat(msg, "!");

    send_cmd(sfd, msg);

}

bool Communicator::getStart()
{
    return toStart;
}
bool Communicator::errorStart()
{
    return startBroken;
}


//For Desktop
void Communicator::send_Task(){
    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "T");
    strcat(msg, "!");

    send_cmd(sfd,msg);
}


//For Robot
void Communicator::send_Ready(){

    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "R");
    strcat(msg, "!");
    send_cmd(sfd,msg);
}

bool Communicator::getReady()
{
    return isReady;
}


//For All
void Communicator::send_Error(char *emsg){
    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "E");
    strcat(msg, "$");
    strcat(msg, emsg);
    strcat(msg, "!");

    send_cmd(sfd, msg);
}


bool Communicator::getError()
{
    return isError;
}


void Communicator::send_Help(){

    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "H");
    strcat(msg, "!");

    send_cmd(sfd,msg);
}


bool Communicator::getHelp()
{
    return needHelp;
}


//For Robot
void Communicator::send_Success(){

    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "X");
    strcat(msg, "!");
    send_cmd(sfd,msg);
}

bool Communicator::getSuccess()
{
    return isSuccessful;
}


//From Phone or Desktop to Either Robot
void Communicator::send_Move(int i){

    // create a message
    char *msg = NULL;
    char &c = to_string(i)[0];

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "M");
    strcat(msg, "$");
    strcat(msg, &c);
    strcat(msg, "!");

    send_cmd(sfd,msg);
}

int Communicator::getMove()
{
    return this_move;
}

void Communicator::setMove(int m)
{
    this_move = m;
}



// send command
void Communicator::send_cmd(int sfd, char *msg){
    int nbytes = 0;

    printf("sending message: %s\n", msg);
    nbytes = talk_to_one(sfd, msg, H);
}

// parses receiving messages into its corresponding types
void Communicator::parse_msg(char *msg){
    char *ptr, *token;

    token = strtok(msg, "!");
    while (token != NULL) {
        if ((token[0] == 'B')) {
            printf("This is a B type of message\n");
            ptr = strstr(token, "$");
            ptr++;
            int id = atoi(ptr);
            ptr++;
            ptr++;
            int str = atoi(ptr);
            ptr++;
            ptr++;
            int d = atoi(ptr);
            token = NULL;
            emit(bidReceived(id,str,d));
        }
        else if ((token[0] == 'R')) {
            isReady = true;
            printf("This is a R type of message\n");
            token = NULL;
            emit(startReceived());
            sleep(1);
        }
        else if ((token[0] == 'T')) {
            printf("This is a T type of message\n");
            token = NULL;
            emit(taskReceived());
            sleep(1);
        }
        else if ((token[0] == 'S')) {
            char &c = token[1];
            printf("This is a S type of message\n");
            toStart = true;
            startBroken = atoi(&c);
            token = NULL;
            emit(startReceived());
            sleep(1);
        }
        else if ((token[0] == 'E')) {
            isError = true;
            printf("This is a E type of message\n");
            ptr = strstr(token, "$");
            ptr++;
            token = NULL;
            emit(errorReceived(ptr));
            sleep(1);
        }
        else if ((token[0] == 'M')) {
            ptr = strstr(token, "$");
            ptr++;
            this_move = atoi(ptr);

            printf("This is a M type of message\n");
            token = NULL;
            emit(moveReceived(this_move));
            sleep(1);
        }
        else if ((token[0] == 'H')) {
            needHelp = true;
            printf("This is a H type of message\n");
            token = NULL;
            emit(helpReceived());
            sleep(1);
        }
        else if ((token[0] == 'X')) {
            isSuccessful = true;
            printf("This is a X type of message\n");
            token = NULL;
            emit(successReceived());
            sleep(10);
        }
    }
}

// continuously listens for messages
void Communicator::startListen(){

    int nbytes = 0;
    char msg[MAXBUF];

    lfd = create_listen(port,H);

    while (1) {
        toStart = false;
        isReady = false;
        isError = false;
        needHelp = false;
        isSuccessful = false;
        this_move = -1;

        nbytes = listen_to_robot(lfd, msg);

        if (nbytes == 0) continue;
        //printf("I received message: %s\n", msg);
        parse_msg(msg);
        sleep(3);
    }
}

void Communicator::startSpeak(){

    sfd = create_send(ip_addr, port, H);
}

