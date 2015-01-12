#include play.h

//Konstruktor inicjalizujacy gre
Play::Play() {
	//Inicjalizacja Allegro
	if (!al_init())
		al_show_native_message_box(0, 0, 0, "Could not initialize Allegro 5", 0, 0);
	srand(time(NULL));
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	
	//Inicjalizacja pol gry
	display = al_create_display(ScreenWidth, ScreenHeight);
	al_set_window_position(display,470,0);
	al_set_window_title(display, "Żużel");
	if (!display)
		al_show_native_message_box(0, 0, 0, "Could not create Allegro window", 0, 0);
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
	
	//Inicjalizacja graczy
	player[0] = new Player(400,390, al_map_rgb(255,0,0), "CZERWONY");
	player[1] = new Player(400, 415, al_map_rgb(0,255,0), "ZIELONY");
	player[2] = new Player(400, 440, al_map_rgb(255,255,0), "ZOLTY");
	player[3] = new Player(400, 465, al_map_rgb(0,255,255), "BLEKITNY");
	
	done = false;
	name = false
	sORc = false;
	game = false;
	counting_down = false;
	pressed = false;
	get_ip = false;
	server = false;
	waiting = false;
	create = false;
}

//Metoda wyswietlajaca menu
void Play::menu() {
	enum options {PLAY, EXIT};
	int option = PLAY;
	bool menu = true;
	bool draw = false;
	
	while(menu) {
		ALLEGRO_EVENT events;
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
					if (option==PLAY){
						menu = false;
						name = true;
					} else {
						menu = false;
						done = true;
					}
				break;
				case ALLEGRO_KEY_ESCAPE:
					menu = false;
					done = true;
				break;
			}
		} else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			menu = false;
			done = true;
		}

		if (events.type == ALLEGRO_EVENT_TIMER)
			draw = true;

		if (draw) {
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
}

//Funkcja wyswietlajaca ekran do podania nicku gracza
string Player::enter_nick() {
	int kod = 0;
	bool ok = false, remove = false, press = false;
	string nick = "";
	
	while(name) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);
		if(events.type == ALLEGRO_EVENT_KEY_DOWN) {
			kod = events.keyboard.keycode;
			if (ALLEGRO_KEY_ENTER == kod)
				ok = true;
			else if (ALLEGRO_KEY_ESCAPE == kod){
				name = false;
				menu = true;
			} else if (kod == 63) {
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

			if(ok) {
				sORc = true;
				name = false;
				menu = false;
			}
		}
	}
	
	return nick;
}

//Metoda wyswietlajaca ekran wyboru zalozenia lub wyszykania gry
void Play::choice() {
	enum options {SERWER, KLIENT};
	int option = SERWER;
	while(sORc) {
		ALLEGRO_EVENT events;
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
					if (option==SERWER){
						server = true;
						create = true;
					} else { 
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
		} else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sORc = false;
			done = true;
		}
		if (events.type == ALLEGRO_EVENT_TIMER)
			draw = true;
		
		if (draw) {
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
}

bool Play::get_done() {
	return done;
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