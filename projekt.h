#include <iostream>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define ScreenWidth 800
#define ScreenHeight 600
#define FPS 60
#define speed 2
#define shadow 50

using namespace std;

/* *** TODO ***
 *  github              15
 *  klasa player        15
 *  łuk                 5
 *  kolizje             25
 *  opis okrążeń        30
 *  wpisywanie nazwy użytkownika    60
 *  orzekanie zwycięstwa    30
 *  powrot do menu          30
 *  wysyłanie               --
 */

void zmiana_polozenia(float &x, float &y, float alfa, float tab[][2], int &number){
    if (number < shadow-1)
        number++;
    else
        number = 0;
    x += speed*cos(alfa);
    y -= speed*sin(alfa);
    tab[number][0] = x;
    tab[number][1] = y;
    for(int i=0;i<shadow;i++)
        al_draw_filled_circle(tab[i][0], tab[i][1], 5, al_map_rgb(255,0,0));
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
