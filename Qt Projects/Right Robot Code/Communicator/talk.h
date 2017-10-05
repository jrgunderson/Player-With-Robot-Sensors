#ifndef TALK_H
#define TALK_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>

class Talk
{
public:
    Talk(char * ip1,char * ip2,char * ip3, int p);
    void send_cmd(int sfd, char *msg);
    void parse_msg(char *msg);
    void send_Bid(int rn, int str, int dist);
    void send_Ready();
    void send_Task();
    void send_Start();
    void send_Error(char *emsg);
    int port;

private:

signals:

};

#endif // TALK_H
