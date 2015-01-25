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

class Play {
	public:
		Play();
		~Play();

		void menu();
		string enter_nick();
		void choice();
		string write_IP();
		void waiting();
		void counting_down();
		void game();
		void set_done();
		void close_socket();
		bool get_done();
		int get_sck();
		void set_sck(int value);
		void set_status(int value);
		int get_status();
		bool get_server();
		void status_inc();
		ALLEGRO_TIMER *timer;
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_DISPLAY *display;
        ALLEGRO_BITMAP *tlo;
		ALLEGRO_FONT *draft;
		ALLEGRO_FONT *secret;
		ALLEGRO_FONT *comforta;
        ALLEGRO_EVENT events;
        ALLEGRO_KEYBOARD_STATE keyboard;
	private:

		Player *player[4];

		int status;
		int me;
		int rivals[3];

		bool done;
		bool server;

		int number;
		int sck;

		string nick;
		string ip;

        bool game_go_on(string winners[4]);
};

#endif
