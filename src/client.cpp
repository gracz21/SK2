#include "client.h"

using namespace std;

int main() {
	struct sockaddr_in sck_addr;
	
	char* server = "127.0.0.1";

	int sck, color;
	char bufor[10];

	cout << "Dołączenie na porcie " << join_port << " do gry serwera " << server << endl;

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

	read(sck, bufor, 10);
	color = strtol(bufor, NULL, 10);
	close(sck);

	cout << color << endl;
	return 0;
}