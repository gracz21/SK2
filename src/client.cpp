#include "client.h"

using namespace std;

int get_connection(char* server) {
	struct sockaddr_in sck_addr;
	
	int sck;
	
	//char* server = "127.0.0.1";
	
	cout << "Łączenie na porcie " << join_port << " do gry serwera " << server << endl;

	memset(&sck_addr, 0, sizeof(sck_addr));
	sck_addr.sin_family = AF_INET;
	inet_aton(server, &sck_addr.sin_addr);
	sck_addr.sin_port = htons(join_port);

	if((sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror ("Nie można utworzyć gniazdka");
		exit(EXIT_FAILURE);
	}

	if(connect(sck, (struct sockaddr*)&sck_addr, sizeof(sck_addr)) < 0) {
		perror ("Brak połączenia");
		exit(EXIT_FAILURE);
	}
}

int join(int sck) {
	char bufor[10];
	int id, last;
	
	read(sck, bufor, 10);
	sscanf(bufor, "%d,%d", &id, &last);
	
	//close(sck);
	
	while(last == 0) {
		strcpy(bufor, "\0");
		read(sck, bufor, 10);
		sscanf(bufor, "%d", &last);
	}
	
	cout << "Dołączono do gry z id: " << id << endl;
	return id;
}

void send_alfa(float alfa, int sck) {
	char bufor[20];
	int n = sprintf(bufor, "%f", alfa);
	write(sck, bufor, n);
}

void get_rivals_alfa(float r_alfa[4], int id, int sck) {
	char bufor[100];
	read(sck, bufor, 10);
	sscanf(bufor, "%f,%f,%f,%f", &r_alfa[0], &r_alfa[1], &r_alfa[2], &r_alfa[3]);
}