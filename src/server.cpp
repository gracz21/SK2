#include "server.h"

#define QUEUE_SIZE 5

using namespace std;

int create_connection() {
	int nSocket;
	int nBind, nListen;
	int nFoo = 1;
	struct sockaddr_in stAddr;

	/* address structure */
	memset(&stAddr, 0, sizeof(struct sockaddr));
	stAddr.sin_family = AF_INET;
	stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	stAddr.sin_port = htons(1030);

	/* create a socket */
	nSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nSocket < 0) {
		fprintf(stderr, "Can't create a socket.\n");
    exit(1);
	}
	setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));

	/* bind a name to a socket */
	nBind = bind(nSocket, (struct sockaddr*)&stAddr, sizeof(struct sockaddr));
	if (nBind < 0) {
		fprintf(stderr, "Can't bind a name to a socket.\n");
		exit(1);
	}
	/* specify queue size */
	nListen = listen(nSocket, QUEUE_SIZE);
	if (nListen < 0) {
		fprintf(stderr, "Can't set queue size.\n");
	}
	
	//close(nSocket);
	return nSocket;
}

void get_rivals(int nSocket, int rivals[3]) {
	int num_of_rivals = 0, id = 1, nClientSocket, n, last;
	char bufor[50];
	socklen_t nTmp;
	struct sockaddr_in stClientAddr;
	
	while(num_of_rivals < 3) {
		/* block for connection request */
		nTmp = sizeof(struct sockaddr);
		nClientSocket = accept(nSocket, (struct sockaddr*)&stClientAddr, &nTmp);
		if (nClientSocket < 0) {
			fprintf(stderr, "Can't create a connection's socket.\n");
			exit(1);
		}

		printf("[connection from %s]\n", inet_ntoa((struct in_addr)stClientAddr.sin_addr));
		
		if((num_of_rivals + 1) == 3)
			last = 1;
		else
			last = 0;
		
		strcpy(bufor, "\0");
		n = sprintf(bufor, "%d,%d", id, last);
		cout << n << " " << bufor << endl;
		write(nClientSocket, bufor, n);
		
		rivals[num_of_rivals] = nClientSocket;
		num_of_rivals++;
		id++;
		//close(nClientSocket);
	}
	
	int i;
	for(i = 0; i < 2; i++) {
		strcpy(bufor, "\0");
		n = sprintf(bufor, "%d", 1);
		cout << n << " " << bufor << endl;
		write(rivals[i], bufor, n);
	}
}

void get_all_alfa(float r_alfa[4], int rivals[3], float alfa) {
	int i;
	char bufor[100];
	float tmp;
	r_alfa[0] = alfa;
	for(i = 0; i < 3; i++) {
		tmp = 0.0;
		strcpy(bufor, "\0");
		read(rivals[i], bufor, 100);
		sscanf(bufor, "%f", &tmp);
		r_alfa[i + 1] = tmp;
		cout << bufor << " " << r_alfa[i + 1] << endl;
	}
}

void send_all_alfa(float r_alfa[4], int rivals[3]) {
	int i;
	char bufor[100];
	for(i = 0; i < 3; i++) {
		strcpy(bufor, "\0");
		int n = sprintf(bufor, "%f,%f,%f,%f", r_alfa[0], r_alfa[1], r_alfa[2], r_alfa[3]);
		cout << n << " " << bufor << endl;
		write(rivals[i], bufor, n);
	}
}