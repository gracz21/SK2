#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "port_list.h"

using namespace std;

int get_connection(char* server);
int join(int sck);
void send_alfa(float alfa, int sck);
void get_rivals_alfa(float r_alfa[3], int id, int sck);