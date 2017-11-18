/*
 * communicator.cpp
 * Ian Stodart @ 2017
 */

#include "communicator.h"

#define MAXBUF 1024 // maximum length of the buffer

#define H 0 // used in help
#define R 1 // used in request

char *ip_addr1;
char *ip_addr2;
char *ip_addr3;

int sfd1; //Robot
int sfd2; //Other Robot or Phone
int sfd3; //Desktop

bool isReady;
bool isError;
bool needHelp;
bool isSuccessful;
int this_move;

int lfd;

extern "C"{
    int itoa(int n, char s[]);
    int create_listen(int, int);
    int create_send(char *, int, int);
    int listen_to_robot(int sockfd, char *msg);
    int Communicator_to_one(int sockfd, char *msg, int);
    int talk_to_one(int sockfd, char *msg, int);
}
Communicator::Communicator(char * ip1,char * ip2,char * ip3, int p)
{
    port = p;

    ip_addr1 = ip1;
    ip_addr2 = ip2;
    ip_addr3 = ip3;

    //int bfd = create_broadcast(6665, H); // broadcast fd
    sfd1 = create_send(ip_addr1, port, H); // single fd #3
    sfd2 = create_send(ip_addr2, port, H); // single fd #4
    sfd3 = create_send(ip_addr3, port, H); // single fd #4
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

    send_cmd(sfd2, msg);
}


//For Desktop
void Communicator::send_Start(){
    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "S");
    strcat(msg, "!");

    send_cmd(sfd2, msg);
    send_cmd(sfd3, msg);

}


//For Desktop
void Communicator::send_Task(){
    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "T");
    strcat(msg, "!");

    send_cmd(sfd1,msg);
    send_cmd(sfd2,msg);
}


//For Robot
void Communicator::send_Ready(){

    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "R");
    strcat(msg, "!");
    send_cmd(sfd3,msg);
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

    strcpy(msg, "B");
    strcat(msg, "$");
    strcat(msg, emsg);
    strcat(msg, "!");

    strcpy(msg, "E");
    strcat(msg, "!");

    send_cmd(sfd1, msg);
    send_cmd(sfd2, msg);
    send_cmd(sfd3, msg);
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

    send_cmd(sfd1,msg);
    send_cmd(sfd2,msg);
    send_cmd(sfd3,msg);
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
    send_cmd(sfd3,msg);
}

bool Communicator::getSuccess()
{
    return isSuccessful;
}


//From Phone or Desktop to Either Robot
void Communicator::send_Move(int i){

    // create a message
    char *msg = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "M");
    strcat(msg, "$");
    strcat(msg, "0"+i);
    strcat(msg, "!");

    send_cmd(sfd3,msg);
}

int Communicator::getMove()
{
    return this_move;
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
            printf("This is a R type of message\n");
            isReady = true;
            token = NULL;
            emit(startReceived());
        }
        else if ((token[0] == 'T')) {
            printf("This is a T type of message\n");
            token = NULL;
            emit(taskReceived());
        }
        else if ((token[0] == 'S')) {
            printf("This is a S type of message\n");
            token = NULL;
            emit(startReceived());
        }
        else if ((token[0] == 'E')) {
            isError = true;
            printf("This is a E type of message\n");
            ptr = strstr(token, "$");
            ptr++;
            token = NULL;
            emit(errorReceived(ptr));
        }
        else if ((token[0] == 'M')) {
            printf("This is a M type of message\n");
            ptr = strstr(token, "$");
            ptr++;
            this_move = atoi(ptr);
            token = NULL;
            emit(moveReceived(this_move));
            //emit(errorReceived(ptr));
        }
        else if ((token[0] == 'H')) {
            printf("This is a H type of message\n");
            needHelp = true;
            token = NULL;
            emit(helpReceived());
        }
        else if ((token[0] == 'X')) {
            printf("This is a X type of message\n");
            isSuccessful = true;
            token = NULL;
            emit(successReceived());
        }
    }
}

// continuously listens for messages
void Communicator::startListen(){

    int nbytes = 0;
    char msg[MAXBUF];

    lfd = create_listen(port,H);

    while (1) {
        isReady = false;
        isError = false;
        needHelp = false;
        isSuccessful = false;
        this_move = -1;

        nbytes = listen_to_robot(lfd, msg);

        if (nbytes == 0) continue;
        printf("I received message: %s\n", msg);
        parse_msg(msg);
        sleep(3);
    }
}

