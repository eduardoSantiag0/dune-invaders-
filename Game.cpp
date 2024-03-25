#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include <vector>

#define SCREEN_FPS 30

std::vector<Dunas> Game::CreateObstacles() 
{
    //? Como deixar gaps iguais entre cada Duna?
    // Calcular o width da Duna
    // Quantas colunas  o grid tem? grid[0].size() 
    int obstaclesWidth = Dunas::grid[0].size() * 3;
    // Number of Gap: 4
    float gap = (640 - (4 * obstaclesWidth)) / 5;

    for ( int i = 0; i < 4 ; i++) {
        float offsetX = (i + 1) * gap + i * obstaclesWidth;
        asDunas.push_back(Dunas (offsetX, 380 - 100));
    }

    return asDunas;
}


Game::Game () {
    SDL_Init(SDL_INIT_EVERYTHING);

    m_WIDTH_WINDOW = 640;
    m_HEIGHT_WINDOW = 480;

    m_window = SDL_CreateWindow("Dune Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_WIDTH_WINDOW, m_HEIGHT_WINDOW, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    m_spaceship = Spaceship(); 

    asDunas = CreateObstacles();
}

Game::~Game() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}



void Game::run () {
    const int targetFrameTime = 1000 / SCREEN_FPS;
    Uint32 frameStart;
    int frameTime;
    std::vector<Laser> lasersVector;

    bool isRunning = true;
    while (isRunning)
    {
        frameStart = SDL_GetTicks();
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_LEFT:
                            m_spaceship.move(-30);
                            break;
                        case SDLK_RIGHT:
                            m_spaceship.move(+30);
                            break;
                        case SDLK_SPACE: {
                            Laser newLaser;
                            newLaser.setPosition (m_spaceship.getPos_X() + 50, m_spaceship.getPos_Y(), 10, 20);

                            lasersVector.push_back(newLaser);

                            std::cout << "Tam de  lasersVector: " << lasersVector.size() << std::endl;
                        }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    isRunning = false;
                    break;
                default:
                    break;
            }
        }
        
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 242, 187, 126, 255); 

        //* Draw Spaceship
        m_spaceship.draw(m_renderer);
        
        //* Draw Dunes
        for (auto& duna: asDunas) {
            duna.draw(m_renderer);
        }

        for (auto it = lasersVector.begin(); it != lasersVector.end(); ) {
            it->draw(m_renderer);
            it->move();
            if (it->getPos_Y() <= 0) {
                it = lasersVector.erase(it);
                std::cout << "Erased! " << "\n";

            } else {
                ++it;
            }
        }


        SDL_RenderPresent(m_renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < targetFrameTime) 
            SDL_Delay(targetFrameTime - frameTime);
        
        // draw();
        // update();
    }
}

// void Game::draw() {


// }
// void Game::update() {

// }

