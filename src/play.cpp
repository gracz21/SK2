#include "play.h"

bool draw_laps(int lap, ALLEGRO_FONT *comforta, string winners[], string name) {
    int ktory;
    for (int i=0; i<4;i++)
        if(winners[i] == name){
            lap = 5;
            ktory = i;
        }
    switch(lap)
    {
        case 1:
            al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "Okrążenie 1/4");
            return true;
        case 2:
            al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "Okrążenie 2/4");
            return true;
        case 3:
            al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "Okrążenie 3/4");
            return true;
        case 4:
            al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "Okrążenie 4/4");
            return true;
        default:
            ostringstream ss;
            ss << (ktory+1);
            string miejsce = "Zająłeś " + ss.str() +  ". miejsce!";
            al_draw_text(comforta, al_map_rgb(255,10,10), 400, 275, ALLEGRO_ALIGN_CENTRE, miejsce.c_str());
            return false;
        }
}

Play::Play() {
	if (!al_init())
		al_show_native_message_box(0, 0, 0, "Could not initialize Allegro 5", 0, 0);

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	display = al_create_display(ScreenWidth, ScreenHeight);
	al_set_window_position(display,470,0);
	al_set_window_title(display, "Żużel");

	if (!display) {
		al_show_native_message_box(0, 0, 0, "Could not create Allegro window", 0, 0);
	}

	tlo = al_load_bitmap("assets//tlo.png");
	draft = al_load_font("assets//last draft.ttf", 200, 0);
	secret = al_load_font("assets//Top Secret.ttf", 50, 0);
	comforta = al_load_font("assets//Comfortaa_Regular.ttf", 50, 0);
	timer = al_create_timer(1.0/FPS);
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_start_timer(timer);
/*
	player[0] = new Player(400,390, al_map_rgb(255,0,0), "CZERWONY");
	player[1] = new Player(400, 415, al_map_rgb(0,255,0), "ZIELONY");
	player[2] = new Player(400, 440, al_map_rgb(255,255,0), "ZOLTY");
	player[3] = new Player(400, 465, al_map_rgb(0,255,255), "BLEKITNY");
*/
	status = 0;
	me = 0;

	done = false;
}

void Play::menu() {
	enum options {PLAY, EXIT};
	int option = PLAY;

	while(status == 0) {
		al_wait_for_event(event_queue, &events);

		if(events.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(events.keyboard.keycode) {
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
					if (option==PLAY)
						status++;
					else {
						status = -1;
						done = true;
					}
				break;
				case ALLEGRO_KEY_ESCAPE:
					status = -1;
					done = true;
				break;
			}
		} else
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			status = -1;
			done = true;
		}

		if (events.type == ALLEGRO_EVENT_TIMER) {
			al_draw_text(draft, al_map_rgb(139, 69, 19), ScreenWidth/2, 20, ALLEGRO_ALIGN_CENTRE, "Zuzel");
			al_draw_text(secret, al_map_rgb(200,200,200), 250, 338, ALLEGRO_ALIGN_CENTRE, "{PLAY}");
			al_draw_text(secret, al_map_rgb(200,200,200), 550, 338, ALLEGRO_ALIGN_CENTRE, "{EXIT}");
            /*
            al_get_keyboard_state(&(keyboard));
			if (al_key_down(&(keyboard), ALLEGRO_KEY_LEFT))
                option = PLAY;
            else if (al_key_down(&(keyboard), ALLEGRO_KEY_RIGHT))
                option = EXIT;
            else if(al_key_down(&(keyboard), ALLEGRO_KEY_ENTER)){
					if (option==PLAY)
						status = 1;
					else {
						status = -1;
						done = true;
					}

            } else if (al_key_down(&(keyboard), ALLEGRO_KEY_ESCAPE)){
					status = -1;
					done = true;
            }
            */
			if (option == PLAY)
				al_draw_rectangle(150, 330, 350, 400, al_map_rgb(139, 69, 19), 7.0);
			else
				al_draw_rectangle(450, 330, 650, 400, al_map_rgb(139, 69, 19), 7.0);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
}

string Play::enter_nick() {
	int kod = 0;
	bool remove = false, press = false;
	nick = "";

	player[0] = new Player(400,390, al_map_rgb(255,0,0), "CZERWONY");
	player[1] = new Player(400, 415, al_map_rgb(0,255,0), "ZIELONY");
	player[2] = new Player(400, 440, al_map_rgb(255,255,0), "ZOLTY");
	player[3] = new Player(400, 465, al_map_rgb(0,255,255), "BLEKITNY");

	while(status == 1) {
		al_wait_for_event(event_queue, &events);
		if(events.type == ALLEGRO_EVENT_KEY_DOWN) {
			kod = events.keyboard.keycode;
			switch(kod) {
			case ALLEGRO_KEY_ENTER:
				status++;
				break;

			case ALLEGRO_KEY_ESCAPE:
				status--;
				break;

			case 63:
				remove = true;
				press = true;
				break;

			default:
				kod += 64;
				press = true;
				break;
			}
		} else
				if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					status = 0;
					done = true;
				}

		if (events.type == ALLEGRO_EVENT_TIMER) {

			if (press) {
				if(remove) {
					if (nick.length() > 0) {
						nick.erase( nick.length() - 1, 1 );
					}
					remove = false;
				} else {
					nick = nick + char(kod);
				}
				press = false;
			}

			al_draw_text(comforta, al_map_rgb(50,50,50), 400, 250, ALLEGRO_ALIGN_CENTRE, "Enter your name:");
			al_draw_text(comforta, al_map_rgb(200,200,200), 400, 350, ALLEGRO_ALIGN_CENTRE, nick.c_str());
			al_draw_text(secret, al_map_rgb(200,200,200), 400, 500, ALLEGRO_ALIGN_CENTRE, "{ OK }");
			al_draw_rectangle(300, 493, 500, 560, al_map_rgb(139, 69, 19), 7.0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	return nick;
}

void Play::choice() {
	enum options {SERWER, KLIENT};
	int option = SERWER;

	while(status == 2) {
		al_wait_for_event(event_queue, &events);
		if(events.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch(events.keyboard.keycode) {
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
				if (option == SERWER) {
					server = true;
					status += 2;
				} else {
					server = false;
					status++;
				}
				break;

			case ALLEGRO_KEY_ESCAPE:
				status--;
				break;
			}
		} else
				if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					status = 0;
					done = true;
				}

		if (events.type == ALLEGRO_EVENT_TIMER) {
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
}

string Play::write_IP() {
	int kod = 0;
	bool remove = false, press = false;
	ip = "";    //"192.168.1.103";

	while(status == 3) {
		al_wait_for_event(event_queue, &events);
		if(events.type == ALLEGRO_EVENT_KEY_DOWN) {
			kod = events.keyboard.keycode;
			if (ALLEGRO_KEY_ENTER == kod)
				status++;
			else if (ALLEGRO_KEY_ESCAPE == kod) {
				status--;
			} else if (kod == 63){
				remove = true;
				press = true;
			} else {
				if(kod < 37)
					kod += 10;
				if (kod == 73 || kod == 90)
					kod = 35;
					kod += 11;
					press = true;
			}
		} else
				if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					status = 0;
					done = true;
				}

		if (events.type == ALLEGRO_EVENT_TIMER) {
			if (press) {
				if(remove) {
					if (ip.length() > 0)
						ip.erase( ip.length() - 1, 1 );
					remove = false;
				} else
						ip = ip + char(kod);
				press = false;
			}

			al_draw_text(comforta, al_map_rgb(50,50,50), 400, 250, ALLEGRO_ALIGN_CENTRE, "Enter IP:");
			al_draw_text(comforta, al_map_rgb(200,200,200), 400, 350, ALLEGRO_ALIGN_CENTRE, ip.c_str());
			al_draw_text(secret, al_map_rgb(200,200,200), 400, 500, ALLEGRO_ALIGN_CENTRE, "{ OK }");
			al_draw_rectangle(300, 493, 500, 560, al_map_rgb(139, 69, 19), 7.0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	return ip;
}

void Play::waiting() {

	while(status == 5) {
		al_wait_for_event(event_queue, &events);
		if (events.type == ALLEGRO_EVENT_TIMER) {
			al_draw_text(comforta, al_map_rgb(50,50,50), 400, 250, ALLEGRO_ALIGN_CENTRE, "Wait for opponents...");
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));

			if(server)
				get_rivals(sck, rivals);
			else
				me = join(sck);

			status++;
		}
	}
	player[me]->setName(nick);
}

void Play::counting_down() {

	int counter = 240;
	while(status == 6) {
		al_wait_for_event(event_queue, &events);
		//menu = true; ???

		if (events.type == ALLEGRO_EVENT_TIMER) {
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
			else
				status++;

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
}

void Play::game() {
    int number = 0, counter = 180;
	float r_alfa[4];
	bool dead = false;
	string winners[4] = {"!@#","!@#","!@#","!@#"};
	while(status == 7) {
		al_wait_for_event(event_queue, &events);
		if (events.type == ALLEGRO_EVENT_TIMER) {
			al_get_keyboard_state(&(keyboard));
			if (al_key_down(&(keyboard), ALLEGRO_KEY_LEFT) && !dead)
				player[me]->incAlfa();
			if (number < 49)
				number++;
			else
				number = 0;

			if(server) {
				get_all_alfa(r_alfa, rivals, player[me]->getAlfa());
				send_all_alfa(r_alfa, rivals);
			} else {
				send_alfa(player[me]->getAlfa(), sck);
				get_rivals_alfa(r_alfa, sck);
			}

			for(int i = 0; i < 4; i++) {
				if(i != me)
					player[i]->setAlfa(r_alfa[i]);
			}

			al_draw_bitmap(tlo, 0, 0, ALLEGRO_FLIP_HORIZONTAL);

			player[0]->next_step(winners, number);
			player[1]->next_step(winners, number);
			player[2]->next_step(winners, number);
			player[3]->next_step(winners, number);


			if(!draw_laps(player[me]->getLap(), comforta, winners, player[me]->getName())) {
				dead = true;
			}

            /*
            if (al_key_down(&(keyboard), ALLEGRO_KEY_ESCAPE){
                for (int i=3; i>(-1); i--){
                    if((winners[i] == "!@#") && (!this->getAdded())) {
                        winners[i] = this->getName();
                        this->setAdded(true);
                    }
                }
                status = 0;
            }
            */
            if(!game_go_on(winners)){
                counter--;
                if (counter < 1){
                    status = 0;
                    close_socket();

                    al_destroy_event_queue(event_queue);
                    event_queue = al_create_event_queue();
                    al_register_event_source(event_queue, al_get_keyboard_event_source());
                    al_register_event_source(event_queue, al_get_timer_event_source(timer));
                    al_register_event_source(event_queue, al_get_display_event_source(display));
                    al_start_timer(timer);

                }
            }
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		} /*else
			if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                for (int i=3; i>(-1); i--){
                    if((winners[i] == "!@#") && (!this->getAdded())) {
                        winners[i] = this->getName();
                        this->setAdded(true);
                    }
                }

				status = -1;
				done = true;
			}
			*/
	}
}

bool Play::get_done() {
	return done;
}

void Play::set_done() {
	done = true;
}

int Play::get_sck() {
	return sck;
}

void Play::set_sck(int value) {
	sck = value;
}

bool Play::get_server() {
	return server;
}

void Play::status_inc() {
	status++;
}

void Play::set_status(int value) {
	status = value;
}

int Play::get_status() {
	return status;
}

bool Play::game_go_on(string winners[4]){
    for (int i = 0; i<4; i++)
        if (winners[i] == "!@#")
            return true;
    return false;
}

void Play::close_socket(){
        close(sck);
}


Play::~Play() {
	al_destroy_bitmap(tlo);
	al_destroy_font(draft);
	al_destroy_font(secret);
	al_destroy_font(comforta);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}
