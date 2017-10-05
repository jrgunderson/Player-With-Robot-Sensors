#include "talk.h"

#define MAXBUF 1024 // maximum length of the buffer

#define H 0 // used in help
#define R 1 // used in request

char *ip_addr1;
char *ip_addr2;
char *ip_addr3;

int sfd1; //Robot
int sfd2; //Other Robot or Phone
int sfd3; //Desktop

extern "C"{
    int itoa(int n, char s[]);
    int create_listen(int, int);
    int create_send(char *, int, int);
    int listen_to_robot(int sockfd, char *msg);
    int talk_to_one(int sockfd, char *msg, int);
}


Talk::Talk(char * ip1,char * ip2,char * ip3, int p)
{\

  int nbytes = 0;
  char msg[MAXBUF];

  port = p;

  ip_addr1 = ip1;
  ip_addr2 = ip2;
  ip_addr3 = ip3;

  // initiate communication
  int lfd = create_listen(port, H); // listening fd
  //int bfd = create_broadcast(6665, H); // broadcast fd
  int sfd1 = create_send(ip_addr1, port, H); // single fd #3
  int sfd2 = create_send(ip_addr2, port, H); // single fd #4
  int sfd3 = create_send(ip_addr3, port, H); // single fd #4


  //Always listen
  while (1) {
    nbytes = listen_to_robot(lfd, msg);
    if (nbytes == 0) continue;
    printf("I received message: %s\n", msg);
    parse_msg(msg);
    sleep(3);
  }
}

//For Robot
void Talk::send_Bid(int rn, int str, int dist){

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
void Talk::send_Ready(){

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
    send_cmd(sfd1,msg);
}

//For Desktop
void Talk::send_Task(){
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
void Talk::send_Start(){
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
void Talk::send_Error(char *emsg){
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
void Talk::send_cmd(int sfd, char *msg){
    int nbytes = 0;

    printf("sending message: %s\n", msg);
    nbytes = talk_to_one(sfd, msg, H);
}


void Talk::parse_msg(char *msg){
    char *ptr, *token;

    token = strtok(msg, "!");
    while (token != NULL) {
      if (token[0] = 'C') {
        printf("This is a C type of message\n");
      }
      ptr = strstr(token, "C");
      ptr++;
      printf(ptr);
      printf("port number %d\n", atoi(ptr));
      ptr = strstr(token, "$");
      ptr++;
      printf("x position is %d\n", atoi(ptr));
      token = strtok(NULL, "!");
    }
}


