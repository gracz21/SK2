#include "client.h"

using namespace std;

struct sockaddr_in init_struct(char* server) {
	struct sockaddr_in sck_addr;
	
	//char* server = "127.0.0.1";

	memset(&sck_addr, 0, sizeof(sck_addr));
	sck_addr.sin_family = AF_INET;
	inet_aton(server, &sck_addr.sin_addr);
	sck_addr.sin_port = htons(join_port);
	
	return sck_addr;
}

int init_sck() {
	int sck;
	if((sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror ("Nie można utworzyć gniazdka");
		exit(EXIT_FAILURE);
	}
	
	return sck;
}

int join(int sck) {
	char bufor[10];
	int id, last;
	
	//cout << "Łączenie na porcie " << join_port << " do gry serwera " << server << endl;
	
	read(sck, bufor, 10);
	sscanf(bufor, "%d,%d", &id, &last);
	cout << "Prelast: " << last << endl;
	//close(sck);
	
	while(last == 0) {
		strcpy(bufor, "\0");
		read(sck, bufor, 10);
		sscanf(bufor, "%d", &last);
		cout << "Last: " << last << endl;
	}
	
	cout << "Dołączono do gry z id: " << id << endl;
	return id;
}

void send_alfa(float alfa, int sck) {
	char bufor[20];
	int n = sprintf(bufor, "%f", alfa);
	cout << "send_alfa_bufor: " << bufor << endl;
	write(sck, bufor, n);
}

void get_rivals_alfa(float r_alfa[4], int id, int sck) {
	char bufor[100];
	read(sck, bufor, 100);
	cout << "get_alfa_bufor: " << bufor << endl;
	sscanf(bufor, "%f,%f,%f,%f", &r_alfa[0], &r_alfa[1], &r_alfa[2], &r_alfa[3]);
}