#include "SDL2/SDL.h"
// #pragma once

class Spaceship
{
public: 
    SDL_Rect m_spaceship;
    Spaceship();
    void move (int new_pos);
    void draw(SDL_Renderer* renderer) const;
    SDL_Rect getRect() const;
    void reset();

private:
    int m_pontuacao;
    void paredeInvisivel();
};