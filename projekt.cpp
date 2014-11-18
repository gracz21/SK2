#include "projekt.h"

int main(){

    init();
    ALLEGRO_DISPLAY *display;
	display = al_create_display(ScreenWidth, ScreenHeight);
    al_set_window_position(display,1470,0);
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

    bool menu = true, game = false, draw = false, counting_down = false, pressed=false;
    enum options {PLAY, EXIT};
    int option = PLAY;

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
                        counting_down = true;
                    } else
                        menu = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    menu = false;
                    break;
            }
        }
        else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            menu = false;

        if (events.type == ALLEGRO_EVENT_TIMER)
        {
            draw = true;

        }

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

    int counter = 180;
    while(counting_down){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_TIMER)
        {
            counter--;
            al_draw_bitmap(tlo, 0, 0, ALLEGRO_FLIP_HORIZONTAL);

            al_draw_filled_circle(400, 390, 5, al_map_rgb(255,0,0));
            al_draw_filled_circle(400, 415, 5, al_map_rgb(0,255,0));
            al_draw_filled_circle(400, 440, 5, al_map_rgb(255,255,0));
            al_draw_filled_circle(400, 465, 5, al_map_rgb(0,255,255));

            if ((counter<180) && (counter>120))
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

    int number = 0;
    Player *czerwony = new Player(400,390, al_map_rgb(255,0,0));
    Player *zielony = new Player(400, 415, al_map_rgb(0,255,0));
    Player *zolty = new Player(400, 440, al_map_rgb(255,255,0));
    Player *niebieski = new Player(400, 465, al_map_rgb(0,255,255));

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
                    break;
            }
        } else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            game = false;

        if (events.type == ALLEGRO_EVENT_TIMER)
            draw = true;

        if (draw)
        {
            draw = false;
            if (pressed == true)
                czerwony->incAlfa();
            if (number < 49)
                number++;
            else
                number = 0;


            al_draw_bitmap(tlo, 0, 0, ALLEGRO_FLIP_HORIZONTAL);

            czerwony->zmiana_polozenia(number);
            //zielony->zmiana_polozenia(number);
            //zolty->zmiana_polozenia(number);
            //niebieski->zmiana_polozenia(number);


            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }

    }
    //al_rest(3.0);
    al_destroy_bitmap(tlo);
    al_destroy_font(draft);
    al_destroy_font(secret);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}
