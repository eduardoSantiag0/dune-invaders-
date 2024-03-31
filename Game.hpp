#include "SDL2/SDL.h"
#include "Spaceship.hpp"
#include "Laser.hpp"
#include "vector"
#include <array>
#include "Dunas.hpp"
#include "Alien.hpp"
// #include "TextureManager.hpp"
// #pragma once

class Game 
{
public:
    Game();
    ~Game();
    void run();
    void draw(SDL_Renderer* m_renderer);
    Spaceship m_spaceship;
    std::vector<Laser> lasersVector;
    std::vector <Dunas> asDunas;
    std::vector<Alien> Harkonens;
    int GetRandomValue(int min, int max);


private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_isRuning;
    int m_WIDTH_WINDOW;
    int m_HEIGHT_WINDOW;
    
    
    SDL_Rect m_background;
    SDL_Texture* background_texture;
    SDL_Texture* loadBackground(const char* filepath, SDL_Renderer* renderer);

    SDL_Texture* spaceshipTexture;
    
    std::vector<Dunas> CreateObstacles();
    std::vector<Alien> CreateEnemies();
    bool checkColisao(SDL_Rect a, SDL_Rect b);
    void MoveAliens();
    int m_aliensDirection;
    void MoveDownAliens(int distance);
    std::vector <Laser> alienLasers;
    void AlienShoot(Uint32 currTime);
    constexpr static Uint32 alienLaserShootInterval = 700;
    Uint32 timeLastAlienFired;
    void verColisoes();
    void GameOver();

    constexpr static Uint32 playerShootInterval = 900;
    Uint32 playerLastTimeFired;

    int player_hp;
    void drawPlayerHP(SDL_Renderer* renderer);
};