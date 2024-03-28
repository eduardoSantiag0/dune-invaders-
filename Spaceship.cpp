#include "Spaceship.hpp"
#include "TextureManager.hpp"
#include <iostream>


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Spaceship::Spaceship() : m_spaceshipTexture(nullptr) 
{
    m_spaceship = {240, 400, 44, 28};
    std::cout << "Nave Criada\n";
}

void Spaceship::paredeInvisivel()
{
    if (m_spaceship.x < 0) {
        m_spaceship.x = 0;
    }
    else if (m_spaceship.x + m_spaceship.w >= WINDOW_WIDTH) {
        m_spaceship.x = WINDOW_WIDTH - m_spaceship.w;
    }
}

void Spaceship::move(int new_pos) 
{
    m_spaceship.x += new_pos; 
    paredeInvisivel();    
}

void Spaceship::draw (SDL_Renderer* renderer)
{
    // SDL_SetRenderDrawColor(renderer, 78, 250, 195, 255);
    // SDL_RenderFillRect(renderer, &m_spaceship);

    if (!m_spaceshipTexture) { 
        m_spaceshipTexture = getTexture("src/images/sprites/spaceship/spaceship_teste_2.png", renderer);
        if (!m_spaceshipTexture) {
            std::cerr << "Failed to load spaceship texture." << SDL_GetError() << std::endl;
            return;
        }
    }
    SDL_RenderCopy(renderer, m_spaceshipTexture, NULL, &m_spaceship);
}

SDL_Rect Spaceship::getRect() const 
{
    return m_spaceship;
}

void Spaceship::reset() 
{
    m_spaceship.x = 240;
}

SDL_Texture* Spaceship::getTexture(const char* filepath, SDL_Renderer* renderer) {
    SDL_Texture* spaceshipTexture = TextureManager::LoadTexture(filepath, renderer);

    return spaceshipTexture;
    // return TextureManager::LoadTexture(filepath, renderer);
}