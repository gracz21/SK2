#include <iostream>
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
 *  klasa player        15
 *  łuk                 5
 *  kolizje             25
 *  opis okrążeń        30
 *  wpisywanie nazwy użytkownika    60
 *  orzekanie zwycięstwa    30
 *  powrot do menu          30
 *  wysyłanie               --
 */


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
