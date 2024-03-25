//todo Retangulo Spaceship
//todo Mover esquerda e direita com A e D
//todo Atirar com Space
#include "SDL2/SDL.h"
// #pragma once

class Spaceship
{

public: 
    SDL_Rect m_spaceship;
    Spaceship();
    void move (int new_pos);
    void draw(SDL_Renderer* renderer) const;
    int getPos_X() const;
    int getPos_Y() const;
private:
    int m_pontuacao;
    void paredeInvisivel();
};