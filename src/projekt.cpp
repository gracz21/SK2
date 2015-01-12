#include "projekt.h"

int main(){ 

    init();
    ALLEGRO_DISPLAY *display;
	display = al_create_display(ScreenWidth, ScreenHeight);
    al_set_window_position(display,470,0);
    al_set_window_title(display, "Żużel");
	if (!display){
		al_show_native_message_box(0, 0, 0, "Could not create Allegro window", 0, 0);
	}

    ALLEGRO_BITMAP *tlo = al_load_bitmap("assets//tlo.png");
    ALLEGRO_FONT *draft = al_load_font("assets//last draft.ttf", 200, 0);
    ALLEGRO_FONT *secret = al_load_font("assets//Top Secret.ttf", 50, 0);
    ALLEGRO_FONT *comforta = al_load_font("assets//Comfortaa_Regular.ttf", 50, 0);
    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_start_timer(timer);

    bool  done = false, menu = true, name = false, sORc = false, game = false, draw = false, counting_down = false,
    pressed=false, get_ip = false, server = false, waiting = false, create = false;
    int number;
    enum options {PLAY, EXIT};
    int option = PLAY;


///////////////////////////////// POCZATEK PROGRAMU ////////////////////////////////////////////////////////////////
    while(!done) {
    number = 0;
///////// ------------------ MENU --------------------- /////////
        while(menu){

            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_RIGHT:
                        if (option == PLAY)
                            option = EXIT;
                        else
                            option = PLAY;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        if (option == PLAY)
                            option = EXIT;
                        else
                            option = PLAY;
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if (option==PLAY){
                            menu = false;
                            name = true;
                        } else{
                            menu = false;
                            done = true;
                        }
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        menu = false;
                        done = true;
                        break;
                }
            }
            else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                menu = false;
                done = true;
            }

            if (events.type == ALLEGRO_EVENT_TIMER)
                draw = true;

            if (draw)
            {
                draw = false;
                al_draw_text(draft, al_map_rgb(139, 69, 19), ScreenWidth/2, 20, ALLEGRO_ALIGN_CENTRE, "Zuzel");
                al_draw_text(secret, al_map_rgb(200,200,200), 250, 338, ALLEGRO_ALIGN_CENTRE, "{PLAY}");
                al_draw_text(secret, al_map_rgb(200,200,200), 550, 338, ALLEGRO_ALIGN_CENTRE, "{EXIT}");
                if (option == PLAY)
                    al_draw_rectangle(150, 330, 350, 400, al_map_rgb(139, 69, 19), 7.0);
                else
                    al_draw_rectangle(450, 330, 650, 400, al_map_rgb(139, 69, 19), 7.0);

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }
        }

        Player *player[4];
        player[0] = new Player(400,390, al_map_rgb(255,0,0), "CZERWONY");
        player[1] = new Player(400, 415, al_map_rgb(0,255,0), "ZIELONY");
        player[2] = new Player(400, 440, al_map_rgb(255,255,0), "ZOLTY");
        player[3] = new Player(400, 465, al_map_rgb(0,255,255), "BLEKITNY");

///////// ---------------NAZWA UZYTKOWNIKA------------- /////////
        int kod = 0; bool ok = false, remove = false, press = false; string nick = "";
        while(name){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                kod = events.keyboard.keycode;
                if (ALLEGRO_KEY_ENTER == kod)
                    ok = true;
                else if (ALLEGRO_KEY_ESCAPE == kod){
                    name = false;
                    menu = true;
                } else if (kod == 63){
		    remove = true;
	            press = true;
		} else {
                    kod += 64;
                    press = true;
                }
            } else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                name = false;
                done = true;
            }

            if (events.type == ALLEGRO_EVENT_TIMER)
            {
                if (press){
		    if(remove){
			if (nick.length() > 0)
		 	     nick.erase( nick.length() - 1, 1 );
			remove = false;
		    }else
                    	nick = nick + char(kod);		    
                    press = false;
                }
                al_draw_text(comforta, al_map_rgb(50,50,50), 400, 250, ALLEGRO_ALIGN_CENTRE, "Enter your name:");
                al_draw_text(comforta, al_map_rgb(200,200,200), 400, 350, ALLEGRO_ALIGN_CENTRE, nick.c_str());
                al_draw_text(secret, al_map_rgb(200,200,200), 400, 500, ALLEGRO_ALIGN_CENTRE, "{ OK }");
                al_draw_rectangle(300, 493, 500, 560, al_map_rgb(139, 69, 19), 7.0);
                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));

                if(ok){
                    sORc = true;
                    name = false;
                    menu = false;
                }
            }
        }

///////// --------------- WYBOR SERWER/KLIENT ------------- /////////
        enum options {SERWER, KLIENT};
        int option = SERWER;
        while(sORc){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_RIGHT:
                        if (option == SERWER)
                            option = KLIENT;
                        else
                            option = SERWER;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        if (option == SERWER)
                            option = KLIENT;
                        else
                            option = SERWER;
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if (option==SERWER){
                            server = true;
			    create = true;
                        } else{ 
			    server = false;                           
                            get_ip = true;
                        }
                        sORc = false;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        sORc = false;
                        menu = false;
                        name = true;
                        break;
                }
            }
            else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sORc = false;
                done = true;
            }

            if (events.type == ALLEGRO_EVENT_TIMER)
                draw = true;

            if (draw)
            {
                draw = false;
                al_draw_text(comforta, al_map_rgb(50,50,50), ScreenWidth/2, 150, ALLEGRO_ALIGN_CENTRE, "Do you want to");
                al_draw_text(comforta, al_map_rgb(50,50,50), ScreenWidth/2, 200, ALLEGRO_ALIGN_CENTRE, "create game or find existing ?");
                al_draw_text(secret, al_map_rgb(200,200,200), 250, 338, ALLEGRO_ALIGN_CENTRE, "{Create}");
                al_draw_text(secret, al_map_rgb(200,200,200), 550, 338, ALLEGRO_ALIGN_CENTRE, "{Find}");
                if (option == SERWER)
                    al_draw_rectangle(110, 330, 390, 400, al_map_rgb(139, 69, 19), 7.0);
                else
                    al_draw_rectangle(450, 330, 650, 400, al_map_rgb(139, 69, 19), 7.0);

                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));
            }
        }


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
		    	counting_down = true;
                    	waiting = false;
                } else{
			me = join(sck);					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! NOWE
		    	waiting = false;
		}
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
    al_destroy_bitmap(tlo);
    al_destroy_font(draft);
    al_destroy_font(secret);
    al_destroy_font(comforta);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}
