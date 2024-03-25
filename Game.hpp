#include "SDL2/SDL.h"
#include "Spaceship.hpp"
#include "Laser.hpp"
#include "vector"
#include "Dunas.hpp"
// #pragma once

class Game 
{
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_WIDTH_WINDOW;
    int m_HEIGHT_WINDOW;
    std::vector<Dunas> CreateObstacles();
public:
    Game();
    ~Game();
    Spaceship m_spaceship;
    std::vector <Dunas> asDunas;
    void run();
    // void draw();
    // void update();

};