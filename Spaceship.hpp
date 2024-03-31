#include "SDL2/SDL.h"
// #pragma once

class Spaceship
{
public: 
    SDL_Rect m_spaceship;
    Spaceship();
    void move (int new_pos);
    void draw(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
    void reset();
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);

private:
    int m_pontuacao;
    SDL_Texture* spaceshipTexture;
    void paredeInvisivel();
    SDL_Texture* m_spaceshipTexture;

};