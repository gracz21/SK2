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
    this->setLap(1);
    this->setColor(color);
    for (int i=0; i<50; i++)
        setShadow(x,y,i);

}

void Player::zmiana_polozenia(int number){
    if(!this->crash())
    {
        this->setX(getX() + speed*cos(this->getAlfa()));
        this->setY(getY() - speed*sin(this->getAlfa()));
        this->setShadow(getX(), getY(), number);
        if ((this->getX() >= 398) && (this->getX() < 400 ) && (this->getY() > 360 ))
                this->incLap();
        for(int i=0;i<50;i++)
            al_draw_filled_circle(this->getShadowX(i), this->getShadowY(i), 4, this->getColor());
    } else
        al_draw_filled_circle(this->getX(), this->getY(), 4, this->getColor());
}

bool Player::crash(){
    float x = getX();// + speed*cos(this->getAlfa());
    float y = getY();// - speed*sin(this->getAlfa());

    if ((y < 115) || (y > 486))
        return true;
    if ((x > 188) && (x < 614) && (y < 366) && (y > 237))
        return true;
    if (pow((x-188),2) + pow((y-301),2) < 3600)
        return true;
    if (pow((x-614),2) + pow((y-301),2) < 3600)
        return true;
    if ((pow((x-188),2) + pow((y-301),2) > 33856) && (x < 188))
        return true;
    if ((pow((x-614),2) + pow((y-301),2) > 33856) && (x > 614))
        return true;
    //if ((pow((x-614),2) + pow((y-301),2) < 33856) && (y>366))
    //    return true;
    return false;

}

