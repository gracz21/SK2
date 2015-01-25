#include "projekt.h"

int main() {
	Play play1;

	string ip;
	while(!play1.get_done()) {
		switch(play1.get_status()) {
		case 0:
			play1.menu();
			break;

		case 1:
			play1.enter_nick();
			break;

		case 2:
			play1.choice();
			break;

		case 3:
			ip = play1.write_IP();
			break;

		case 4:
			char ip_char[100];
			struct sockaddr_in sck_addr;
			if(play1.get_server()) {
				play1.set_sck(create_connection());
                play1.status_inc();
			} else {
				memcpy(ip_char, ip.data(), ip.size() );
				ip_char[ip.size()] = '\0';
				sck_addr = init_struct(ip_char);
				play1.set_sck(init_sck());
				if(connect(play1.get_sck(), (struct sockaddr*)&sck_addr, sizeof(sck_addr)) < 0) {
					cout << "BŁĄD POŁACZENIA" << endl;
					play1.set_status(0);
					//cout << "status " << play1.get_status() << endl;
				}
				else{
                    play1.status_inc();
                    cout << "Stworzono polaczenie" << endl;
                }
			}


			break;

		case 5:
			play1.waiting();
			break;

		case 6:
			play1.counting_down();
			break;

		case 7:
			play1.game();
			break;
		}
	}

	return 0;
}
