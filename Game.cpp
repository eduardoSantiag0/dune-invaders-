#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include <vector>
#include<cstdlib>

#define SCREEN_FPS 30

bool Game::checkColisao(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //* Cenário em que não tem colisão 
    // Um dos lados de A estão fora de B
    // 
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB ||  leftA >= rightB ) {
        return false;
    }


    //* Tem colisao
    // Nenhum dos lados de A estão fora de B;
    //
    return true;
}

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

// Cria um Vetor de Aliens
// Vetor de Aliens = Hakonen
std::vector<Alien> Game::CreateEnemies() {
    std::vector<Alien> aliens;
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column ++) {
            int alientype;
            if (row == 0) {
                alientype = 3;
            } else if (row == 1 ||  row == 2) {
                alientype = 2;
            } else {
                alientype = 1;
            }
            
            float x = 25 + column * 30;
            float y = 55 + row * 20;
            aliens.push_back (Alien(alientype, x, y));
        }
    }
    return aliens;
}

Game::Game () 
    : m_WIDTH_WINDOW(640), m_HEIGHT_WINDOW(480), m_aliensDirection(1) 
{
    // SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow("Dune Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_WIDTH_WINDOW, m_HEIGHT_WINDOW, 0);
    if (m_window == nullptr) {
        std::cout << "Nao foi  possivel abrir a janela\n";
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr) {
        std::cout << "Nao foi  possivel abrir o render \n";
        return;
    }
    SDL_Surface* icon = SDL_LoadBMP("./src/images/icons/dune_v0.1.bmp");
    SDL_SetWindowIcon(m_window, icon);
    SDL_FreeSurface(icon);

    m_spaceship = Spaceship(); 
    asDunas = CreateObstacles();
    Harkonens = CreateEnemies();

    timeLastAlienFired = 0.0;
    playerLastTimeFired = 0.0;
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
    


    bool m_isRuning = true;
    while (m_isRuning)
    {
        frameStart = SDL_GetTicks();
        Uint32 currentAlientShootTime = SDL_GetTicks();
        Uint32 playerCurrentShootTime = SDL_GetTicks();

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
                                if (playerCurrentShootTime - playerLastTimeFired >= playerShootInterval) { 
                                    Laser newLaser;
                                    newLaser.setPosition (m_spaceship.getRect().x + m_spaceship.getRect().w / 2, m_spaceship.getRect().y  - m_spaceship.getRect().h / 2, 4, 15);
                                    lasersVector.push_back(newLaser);
                                    playerLastTimeFired = SDL_GetTicks();
                                } 
                                break;
                        }
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    m_isRuning = false;
                    break;
                default:
                    break;
            }
        }   
        
        
        SDL_RenderClear(m_renderer);

        //! Desenhando
        //
        draw(m_renderer);

        MoveAliens();
        AlienShoot(currentAlientShootTime);

        for(auto& laser : alienLasers) {
            laser.move(Laser::Tipo::Alien);
        }


        // Atirar
        //

        for (auto it = lasersVector.begin(); it != lasersVector.end(); ) {
            it->draw(m_renderer);
            it->move(Laser::Tipo::Player);
            if (it->getPos_Y() <= 0) {
                it = lasersVector.erase(it);
            } else {
                ++it;
            }
        }
    
        // Alien Atirando
        //
        for (auto it = alienLasers.begin(); it != alienLasers.end(); ) {
            it->draw(m_renderer);
            it->move(Laser::Tipo::Alien);
            if (it->getPos_Y() <= 0) {
                it = alienLasers.erase(it);
            } else {
                ++it;
            }
        }

        verColisoes();

        SDL_RenderPresent(m_renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < targetFrameTime) 
            SDL_Delay(targetFrameTime - frameTime);
        
        // update();
    }
}

void Game::draw(SDL_Renderer* m_renderer) {
        //* Color BG
        SDL_SetRenderDrawColor(m_renderer, 250, 187, 100, 255); 

        //* Draw Spaceship
        m_spaceship.draw(m_renderer);
        
        //* Draw Dunes
        for (auto& duna : asDunas) {
            duna.draw(m_renderer);
        }

        //* Cria o vetor de inimigos
        for (auto& enemy : Harkonens) {
            enemy.draw(m_renderer);
        }

        //* Laser Inimigo
        for(auto& laser : alienLasers) {
            laser.draw(m_renderer);
        }

}

void Game::MoveAliens() {
    for (auto& alien : Harkonens) {
        if (alien.getRect().x + alien.getRect().w > m_WIDTH_WINDOW) {
            m_aliensDirection = -1;
            MoveDownAliens(2);
        }
        if (alien.getRect().x < 0) {
            m_aliensDirection = 1;
            MoveDownAliens(2);
        }
        alien.move(m_aliensDirection);
    }

}

void Game::MoveDownAliens(int distance) 
{ 
    for (auto& alien : Harkonens) {
        int pos_y_atual = alien.getRect().y;
        pos_y_atual += distance;
        alien.setPositionY(pos_y_atual);
    }

}

void Game::AlienShoot(Uint32 currTime) 
{
    if (currTime - timeLastAlienFired >= alienLaserShootInterval) 
    {
        int randomIndex = GetRandomValue(0, Harkonens.size() - 1);

        Alien& alien = Harkonens[randomIndex]; 

        Laser newEnemyLaser;
        
        newEnemyLaser.setPosition(alien.getRect().x + alien.getRect().w / 2, alien.getRect().y + alien.getRect().h, 4, 10);
        
        alienLasers.push_back(newEnemyLaser); 
        
        timeLastAlienFired = SDL_GetTicks();
    }
}


int Game::GetRandomValue(int min, int max) 
{
    int range = max - min + 1;
    return rand() % range + min;
}


void Game::verColisoes() {
    
    //* LaserPlayer 
    for (auto laserPlayerIterator = lasersVector.begin(); laserPlayerIterator != lasersVector.end();) {
        bool apagarLaser = false;
        for (auto enemyIterator = Harkonens.begin(); enemyIterator != Harkonens.end() && !apagarLaser;) {
            if (checkColisao(laserPlayerIterator->getRect(), enemyIterator->getRect())) {
                enemyIterator = Harkonens.erase(enemyIterator); // Erase the alien
                laserPlayerIterator = lasersVector.erase(laserPlayerIterator); // Erase the laser
                apagarLaser = true;
                break; // Exit the loop since the laser is erased
            } else {
                ++enemyIterator;
            }
        }

        // Proceed with obstacle collision only if the laser wasn't erased
        if (!apagarLaser) {
            for (auto& obstacle : asDunas) {
                auto it = obstacle.blocks.begin();
                while (it != obstacle.blocks.end()) {
                    if (checkColisao(it->getRect(), laserPlayerIterator->getRect())) {
                        it = obstacle.blocks.erase(it); // Erase the obstacle block
                        apagarLaser = true;
                        laserPlayerIterator = lasersVector.erase(laserPlayerIterator); // Erase the laser
                        break; // Exit the loop since the laser is erased
                    } else {
                        ++it;
                    }
                }
                if (apagarLaser) break; // Exit the loop if the laser was erased after hitting an obstacle
            }
        }

        // Increment the iterator only if no erasure has occurred
        if (!apagarLaser) {
            ++laserPlayerIterator;
        }
    }


    //* Laser Alien
    for (auto alienLaserIt = alienLasers.begin(); alienLaserIt != alienLasers.end();) {
        bool laserRemoved = false;

        for (auto& obstacle : asDunas) {
            for (auto blockIt = obstacle.blocks.begin(); blockIt != obstacle.blocks.end() && !laserRemoved;) {
                if (checkColisao(alienLaserIt->getRect(), blockIt->getRect())) {
                    // Here we erase the block and the laser upon collision
                    blockIt = obstacle.blocks.erase(blockIt); // Erase the dune block
                    alienLaserIt = alienLasers.erase(alienLaserIt); // Erase the alien laser
                    laserRemoved = true; // Mark the laser as removed to skip further checks
                    break; // Exit the innermost loop since the laser is erased
                } else {
                    ++blockIt;
                }
            }
            if (laserRemoved) break; // Exit the loop if the laser was erased after hitting a block
        }

        if (!laserRemoved) {
            ++alienLaserIt; // Only increment if no erasure has occurred
        }
    }

    //* Aliens com Objetos
    for (auto& alien : Harkonens) {
        for(auto& obstacle: asDunas) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()) {
                if(checkColisao(it -> getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it ++;
                }
            }
        }
        if (checkColisao(m_spaceship.getRect(), alien.getRect())) {
            GameOver();
        }
    }


}

void Game::GameOver() {
    m_isRuning = false;
}