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

int lfd;

extern "C"{
    int itoa(int n, char s[]);
    int create_listen(int, int);
    int create_send(char *, int, int);
    int listen_to_robot(int sockfd, char *msg);
    int Communicator_to_one(int sockfd, char *msg, int);
    int talk_to_one(int sockfd, char *msg, int);
}
Communicator::Communicator(QObject *parent) : QObject(parent){

}

void Communicator::init(char * ip1,char * ip2,char * ip3, int p)
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
void Communicator::send_Bid(int rn, int str, double dist){

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
//For Robot
void Communicator::send_Ready(){

    // create a message
    char *msg = NULL;
    //char *char_from = NULL;
    //char *char_x = NULL;

    msg = (char *) malloc(60*sizeof(char));
    //char_from = (char *) malloc(10*sizeof(char));
    //char_x = (char *) malloc(10*sizeof(char));

    //itoa((int)port, char_from);
    //itoa((int)x, char_x);

    strcpy(msg, "R");
    //strcat(msg, char_from);
    //strcat(msg, "$");
    //strcat(msg, char_x);
    strcat(msg, "!");
    send_cmd(sfd2,msg);
}

//For Desktop
void Communicator::send_Task(){
    // create a message
    char *msg = NULL;
    //char *char_from = NULL;
    //char *char_x = NULL;

    msg = (char *) malloc(60*sizeof(char));
    //char_from = (char *) malloc(10*sizeof(char));
    //char_x = (char *) malloc(10*sizeof(char));

    //itoa((int)port, char_from);
    //itoa((int)x, char_x);

    strcpy(msg, "T");
    //strcat(msg, char_from);
    //strcat(msg, "$");
    //strcat(msg, char_x);
    strcat(msg, "!");

    send_cmd(sfd1,msg);
    send_cmd(sfd2,msg);
}

//For Desktop
void Communicator::send_Start(){
    // create a message
    char *msg = NULL;
    //char *char_from = NULL;
    //char *char_x = NULL;

    msg = (char *) malloc(60*sizeof(char));
    //char_from = (char *) malloc(10*sizeof(char));
    //char_x = (char *) malloc(10*sizeof(char));

    //itoa((int)port, char_from);
    //itoa((int)x, char_x);

    strcpy(msg, "S");
    //strcat(msg, char_from);
    //strcat(msg, "$");
    //strcat(msg, char_x);
    strcat(msg, "!");

    send_cmd(sfd1, msg);
    send_cmd(sfd2, msg);
}

//For All
void Communicator::send_Error(char *emsg){
    // create a message
    char *msg = NULL;
    //char *char_from = NULL;
    //char *char_x = NULL;

    msg = (char *) malloc(60*sizeof(char));

    strcpy(msg, "B");
    strcat(msg, "$");
    strcat(msg, emsg);
    strcat(msg, "!");

    send_cmd(sfd1,"E");
    send_cmd(sfd2,"E");
    send_cmd(sfd3,"E");
}

//From Phone or Desktop to Either Robot
//C will be F, B, L, or R
void Communicator::send_Move(int i, int m){

    // create a message
    char *msg = NULL;
    //char *char_from = NULL;
    char *char_m = NULL;

    msg = (char *) malloc(60*sizeof(char));
    //char_from = (char *) malloc(10*sizeof(char));
    //char_x = (char *) malloc(10*sizeof(char));

    //itoa((int)port, char_from);
    itoa((int)m, char_m);

    strcpy(msg, "M");
    //strcat(msg, char_from);
    strcat(msg, "$");
    strcat(msg, char_m);
    strcat(msg, "!");

    if(i == 0){ //Robot 1
        send_cmd(sfd1,msg);
    }
    else if(i == 1){ //Robot 2
        send_cmd(sfd2,msg);
    }
}

void Communicator::send_cmd(int sfd, char *msg){
    int nbytes = 0;

    qDebug() << "Sending message";
    qDebug() << msg;
    nbytes = talk_to_one(sfd, msg, H);
    //qDebug() << "Number of Bytes ";
    //qDebug() << nbytes;
}


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
            printf("This is a E type of message\n");
            ptr = strstr(token, "$");
            ptr++;
            emit(errorReceived(ptr));
        }
        else if ((token[0] == 'M')) {
            printf("This is a M type of message\n");
            ptr = strstr(token, "$");
            ptr++;
            int m = atoi(ptr);
            token = NULL;
            emit(moveReceived(m));
        }
    }
}
void Communicator::startListen(){
    int nbytes = 0;
    char msg[MAXBUF];

    lfd = create_listen(port,H);
    while (1) {
        nbytes = listen_to_robot(lfd, msg);
        if (nbytes == 0) continue;
        printf("I received message: %s\n", msg);
        parse_msg(msg);
        sleep(3);
    }
}

/*      ptr = strstr(token, "C");
      ptr++;
      printf(ptr);
      printf("port number %d\n", atoi(ptr));
      ptr = strstr(token, "$");
      ptr++;
      printf("x position is %d\n", atoi(ptr));
      token = strtok(NULL, "!");*/
