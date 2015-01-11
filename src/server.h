#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "port_list.h"

int create_connection();
void get_rivals(int nSocket, int rivals[3]);
void get_all_alfa(float r_alfa[4], int rivals[3], float alfa);
void send_all_alfa(float r_alfa[4], int rivals[3]);