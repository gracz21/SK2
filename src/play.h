#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "player.h"
#include "server.h"
#include "client.h"

#define ScreenWidth 800
#define ScreenHeight 600
#define FPS 60

using namespace std;

class Player {
	public:
		Player();
		~Player();
		
		void menu();
		string enter_nick();
		void choice();
		
		bool get_done();
	private:
		ALLEGRO_DISPLAY *display;
		ALLEGRO_BITMAP *tlo;
		ALLEGRO_FONT *draft;
		ALLEGRO_FONT *secret;
		ALLEGRO_FONT *comforta;
		ALLEGRO_TIMER *timer;
		ALLEGRO_EVENT_QUEUE *event_queue;
		
		Player *player[4];
		
		bool done;
		bool name;
		bool sORc;
		bool game;
		bool draw;
		bool counting_down;
		bool pressed;
		bool get_ip;
		bool server;
		bool waiting;
		bool create;
		
		int number;
		int sck;
}

#endif