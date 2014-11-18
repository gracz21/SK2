#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <iostream>
#include <allegro5/allegro_primitives.h>

#define speed 2
using namespace std;

class Player
{
    public:
        Player();
        Player(float x, float y, ALLEGRO_COLOR color);
        virtual ~Player();

        float getX() { return x; }
        void setX(float val) { x = val; }

        float getY() { return y; }
        void setY(float val) { y = val; }

        float getAlfa() { return alfa; }
        void setAlfa(float val) { alfa = val; }
        void incAlfa() { alfa += 0.0174; }

        ALLEGRO_COLOR getColor() { return color; }
        void setColor(ALLEGRO_COLOR val) { color = val; }

        float getShadowX(int number) { return shadow[number][0]; }
        float getShadowY(int number) { return shadow[number][1]; }
        void setShadow(float x, float y, int number) { shadow[number][0] = x; shadow[number][1] = y;  }

        float getLap() { return lap; }
        void setLap(float val) { lap = val; }
        void incLap() { lap++; }

        void zmiana_polozenia(int number);
        bool crash();

    protected:

    private:
        float x;
        float y;
        float alfa;
        ALLEGRO_COLOR color;
        float shadow[50][2];

        int lap;

};

#endif // PLAYER_H
