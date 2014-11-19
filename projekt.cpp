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

    ALLEGRO_BITMAP *tlo = al_load_bitmap("tlo.png");
    ALLEGRO_FONT *draft = al_load_font("last draft.ttf", 200, 0);
    ALLEGRO_FONT *secret = al_load_font("Top Secret.ttf", 50, 0);
    ALLEGRO_FONT *comforta = al_load_font("Comfortaa_Regular.ttf", 50, 0);
    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_start_timer(timer);

    bool  done = false, menu = true, name = false, game = false, draw = false, counting_down = false, pressed=false;
    enum options {PLAY, EXIT};    int option = PLAY, number;

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

        Player *czerwony = new Player(400,390, al_map_rgb(255,0,0));
        Player *zielony = new Player(400, 415, al_map_rgb(0,255,0));
        Player *zolty = new Player(400, 440, al_map_rgb(255,255,0));
        Player *niebieski = new Player(400, 465, al_map_rgb(0,255,255));

///////// ---------------NAZWA UZYTKOWNIKA------------- /////////
        int counter = 339, kod = 0; bool ok = false, press = false; string nick = "";
        while(name){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                kod = events.keyboard.keycode;
                if (ALLEGRO_KEY_ENTER == kod)
                    ok = true;
                else {
                    kod += 64;
                    press = true;
                }
            }

            if (events.type == ALLEGRO_EVENT_TIMER)
            {
                counter--;
                ostringstream ss;
                ss << (counter/60);
                string str = ss.str();
                al_draw_text(draft, al_map_rgb(139, 69, 19), 400, 20, ALLEGRO_ALIGN_CENTRE, str.c_str());
                if (press){
                    nick = nick + char(kod);
                    press = false;
                }
                al_draw_text(comforta, al_map_rgb(50,50,50), 400, 250, ALLEGRO_ALIGN_CENTRE, "Enter your name:");
                al_draw_text(comforta, al_map_rgb(200,200,200), 400, 350, ALLEGRO_ALIGN_CENTRE, nick.c_str());
                al_draw_text(secret, al_map_rgb(200,200,200), 400, 500, ALLEGRO_ALIGN_CENTRE, "{ OK }");
                if(ok)
                    al_draw_rectangle(300, 493, 500, 560, al_map_rgb(139, 69, 19), 7.0);
                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0));

                if(counter < 1){
                    name = false;
                    if(ok)
                        counting_down = true;
                    else
                        menu = true;
                    czerwony->setName(nick);
                }
            }
        }

///////// ---------ODLICZANIE DO STARTU ------------ /////////
        counter = 240; menu = true;
        while(counting_down){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if (events.type == ALLEGRO_EVENT_TIMER)
            {
                counter--;
                al_draw_bitmap(tlo, 0, 0, ALLEGRO_FLIP_HORIZONTAL);

                al_draw_text(comforta, al_map_rgb(200,200,200), 20, 10, 0, czerwony->getName().c_str());

                al_draw_filled_circle(400, 390, 5, al_map_rgb(255,0,0));
                al_draw_filled_circle(400, 415, 5, al_map_rgb(0,255,0));
                al_draw_filled_circle(400, 440, 5, al_map_rgb(255,255,0));
                al_draw_filled_circle(400, 465, 5, al_map_rgb(0,255,255));

                if ((counter<240) && (counter>180))
                    al_draw_text(comforta, al_map_rgb(200,200,200), 400, 275, ALLEGRO_ALIGN_CENTRE, "Jesteś CZERWONYM");
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

        counter = 180;
///////// ------------------ GRA --------------------- /////////
        string winners[4] = {"!@#","!@#","!@#","!@#"};
        while(game){
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT:
                        //wysylanie wcisniecia
                        pressed = true;
                        break;
                }
            }

            if(events.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT:
                        //wysylanie puszczenia
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
                    czerwony->incAlfa();
                    niebieski->incAlfa();
                    zielony->incAlfa();
                    zolty->incAlfa();
                }
                if (number < 49)
                    number++;
                else
                    number = 0;

                al_draw_bitmap(tlo, 0, 0, ALLEGRO_FLIP_HORIZONTAL);

                czerwony->next_step(winners, number);
                zielony->next_step(winners, number);
                zolty->next_step(winners, number);
                niebieski->next_step(winners, number);
                for (int a = 0; a<4; a++)
                    cout << winners[a] << "\t";
                cout << endl;

                if(!draw_laps(czerwony->getLap(), comforta, winners, czerwony->getName())){
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
