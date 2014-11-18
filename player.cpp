#include "player.h"

Player::Player()
{
    //consutructor
}

Player::~Player()
{
    //destructor
}

Player::Player(float x, float y, ALLEGRO_COLOR color)
{
    this->setX(x);
    this->setY(y);
    this->setAlfa(0.0);
    this->setColor(color);
    for (int i=0; i<50; i++)
        setShadow(x,y,i);

}

void Player::zmiana_polozenia(int number){

    this->setX(getX() + speed*cos(this->getAlfa()));
    this->setY(getY() - speed*sin(this->getAlfa()));
    this->setShadow(getX(), getY(), number);
    for(int i=0;i<50;i++)
        al_draw_filled_circle(this->getShadowX(i), this->getShadowY(i), 4, this->getColor());
}

