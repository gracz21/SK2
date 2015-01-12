#include "player.h"
#include "server.h"
#include "client.h"


using namespace std;

/* *** TODO ***
 *  github              \/
 *  klasa player        \/
 *  łuk                 \/
 *  kolizje             \/
 *  opis okrążeń        \/
 *  nazwa użytkownika       \/
 *  orzekanie zwycięstwa    \/
 *  orzekanie porażki       \/
 *  powrot do menu          \/
 *  wysyłanie               --
 */


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