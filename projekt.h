#include <iostream>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "player.h"

#define ScreenWidth 800
#define ScreenHeight 600
#define FPS 60


using namespace std;

/* *** TODO ***
 *  github              \/
 *  klasa player        \/
 *  łuk                 \/
 *  kolizje             \/
 *  opis okrążeń        \/
 *  nazwa użytkownika       \/
 *  orzekanie zwycięstwa    30
 *  orzekanie porażki       30
 *  powrot do menu          \/
 *  wysyłanie               --
 */


void end_race(){
    cout << "Koniec wyscigu" << endl;
    //al_rest(3.0);
}

bool draw_laps(int lap, ALLEGRO_FONT *comforta, string winners[], string name)
{
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
        }

}

void init()
{
    if (!al_init())
        al_show_native_message_box(0, 0, 0, "Could not initialize Allegro 5", 0, 0);

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
}
