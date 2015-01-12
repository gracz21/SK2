#include "projekt.h"
#include "play.h"

int main(){ 
	Play play1;

///////////////////////////////// POCZATEK PROGRAMU ////////////////////////////////////////////////////////////////
    while(!play1.get_done()) {
    number = 0;
///////// ------------------ MENU --------------------- /////////
        


///////// ---------------NAZWA UZYTKOWNIKA------------- /////////


///////// --------------- WYBOR SERWER/KLIENT ------------- /////////



//////////////////      KLIENT - PODANIE IP
	int sck;
	ok = false; 
	string ip = "";
        while(get_ip){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                kod = events.keyboard.keycode;
                if (ALLEGRO_KEY_ENTER == kod)
                    ok = true;
                else if (ALLEGRO_KEY_ESCAPE == kod){
		    sORc = true;
                    get_ip = false;
                } else if (kod == 63){
		    remove = true;
	            press = true;
		}else{
		    if(kod < 37)
		         kod += 10;
                    if (kod == 73 || kod == 90)
			kod = 35;
		    kod += 11;		    
                    press = true;
                }
            } else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                get_ip = false;
                done = true;
            }

            if (events.type == ALLEGRO_EVENT_TIMER)
            {
                if (press){
		    if(remove){
			if (ip.length() > 0)
			     ip.erase( ip.length() - 1, 1 );
			remove = false;
		    }else
                    	ip = ip + char(kod);		    
                    press = false;
                }
                al_draw_text(comforta, al_map_rgb(50,50,50), 400, 250, ALLEGRO_ALIGN_CENTRE, "Enter IP:");
                al_draw_text(comforta, al_map_rgb(200,200,200), 400, 350, ALLEGRO_ALIGN_CENTRE, ip.c_str());
                al_draw_text(secret, al_map_rgb(200,200,200), 400, 500, ALLEGRO_ALIGN_CENTRE, "{ OK }");
                al_draw_rectangle(300, 493, 500, 560, al_map_rgb(139, 69, 19), 7.0);
                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));

                if(ok){
                    create = true;
                    get_ip = false;
                }
            }
        }
//create = false;
//////////////////      TWORZENIE POŁĄCZENIA					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
	char ip_char[100];	
	struct sockaddr_in sck_addr;
	if(create){	
	   if(server){
	      	sck = create_connection();					
   	   } else {
	     	memcpy( ip_char, ip.data(), ip.size() );			
    	     	ip_char[ip.size()] = '\0';
	     	sck_addr = init_struct(ip_char);
		sck = init_sck();
		if(connect(sck, (struct sockaddr*)&sck_addr, sizeof(sck_addr)) < 0) {
			perror ("Brak polaczenia");
			exit(EXIT_FAILURE);
		}
           }
	   cout << "Stworzono polaczenie" << endl;
	   create = false;
	   waiting = true;
	}
//waiting = true;
//////////////////      CZEKANIE
        int rivals[3];
	int me = 0;
       while(waiting){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);
            if (events.type == ALLEGRO_EVENT_TIMER)
            {
                al_draw_text(comforta, al_map_rgb(50,50,50), 400, 250, ALLEGRO_ALIGN_CENTRE, "Wait for opponents...");
                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));

                if(server){
                    	get_rivals(sck, rivals);			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
                    	waiting = false;
                } else{
			me = join(sck);					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
		    	waiting = false;
		}
		counting_down = true;
            }

        }

///////// POBIERANIE IDENTYFIKATORÓW KAŻDEGO GRACZA { 0, 1, 2, 3 }


///////// ---------ODLICZANIE DO STARTU ------------ /////////
        player[me]->setName(nick);               
        int counter = 240;
        while(counting_down){
            menu = true;
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if (events.type == ALLEGRO_EVENT_TIMER)
            {
                counter--;
                al_draw_bitmap(tlo, 0, 0, ALLEGRO_FLIP_HORIZONTAL);

                al_draw_text(comforta, al_map_rgb(200,200,200), 20, 10, 0, player[me]->getName().c_str());

                al_draw_filled_circle(400, 390, 5, al_map_rgb(255,0,0));
                al_draw_filled_circle(400, 415, 5, al_map_rgb(0,255,0));
                al_draw_filled_circle(400, 440, 5, al_map_rgb(255,255,0));
                al_draw_filled_circle(400, 465, 5, al_map_rgb(0,255,255));

		string my_color = "Jesteś " + player[me]->getKolor() +"M";
                if ((counter<240) && (counter>180))
                    al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, my_color.c_str());
                else if ((counter<181) && (counter>120))
                    al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "- 3 -");
                else if ((counter<121) && (counter>60))
                    al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "- 2 -");
                else if ((counter<61) && (counter>0))
                    al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "- 1 -");
                else{
                    counting_down = false;
                    game = true;
                }
                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));

            }


        }


///////// ------------------ GRA --------------------- /////////
        counter = 180;
	float r_alfa[4];
        string winners[4] = {"!@#","!@#","!@#","!@#"};
        while(game){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT:
                        pressed = true;
                        break;
                }
            }

            if(events.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT:
                        pressed = false;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        game = false;
                        menu = false;
                        break;
                }
            } else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                game = false;
                menu = false;
                done = true;
            }

            if (events.type == ALLEGRO_EVENT_TIMER)
                draw = true;

            if (draw)
            {
                draw = false;
                if (pressed == true){
                    player[me]->incAlfa();						//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
                    //player[1]->incAlfa();
                    //player[2]->incAlfa();
                    //player[3]->incAlfa();
                }
                if (number < 49)
                    number++;
                else
                    number = 0;
	
		// WYSYŁANIE / POBIERANIE KĄTA ALFA KAŻDEGO Z GRACZY			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
		if(server){
			get_all_alfa(r_alfa, rivals, player[me]->getAlfa());
			send_all_alfa(r_alfa, rivals);
		} else {
			send_alfa(player[me]->getAlfa(), sck);
			get_rivals_alfa(r_alfa, sck);
		}

		// ZMIANA ALFY								//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
		//!Nie powinno przypisywac player[me]
		player[0]->setAlfa(r_alfa[0]);
                player[1]->setAlfa(r_alfa[1]);
                player[2]->setAlfa(r_alfa[2]);
                player[3]->setAlfa(r_alfa[3]);		

                al_draw_bitmap(tlo, 0, 0, ALLEGRO_FLIP_HORIZONTAL);

                player[0]->next_step(winners, number);
                player[1]->next_step(winners, number);
                player[2]->next_step(winners, number);
                player[3]->next_step(winners, number);

                if(!draw_laps(player[me]->getLap(), comforta, winners, player[me]->getName())){	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
                    counter--;
                    if (counter < 1)
                        game = false;
                }

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }

        }
    }
    return 0;
}
