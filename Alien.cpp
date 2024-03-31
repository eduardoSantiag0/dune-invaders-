#include <iostream>
#include "Alien.hpp"

Alien::Alien (int m_type, int pos_x, int pos_y) : m_type(m_type), m_dir(1), m_speed(2), m_alien({pos_x, pos_y, 20, 15}), m_alienTexture(nullptr)
{
    switch (m_type)
    {
    case 1:
        m_red = 245;
        m_green = 221;
        m_blue = 188;
        break;
    
    case 2:
        m_red = 217;
        m_green = 248;
        m_blue = 255;
        break;
    
    case 3:
        m_red = 255;
        m_green = 205;
        m_blue = 255;
        break;
    
    default:
        break;
    }

}


void Alien::move(int direction) {
    m_dir = direction;
    if (m_alien.x + m_alien.w >= 640) {
        m_dir = -1;
    } else if (m_alien.x < 0) {
        m_dir = 1;
    }

    m_alien.x += m_speed * m_dir;

}

void Alien::draw (SDL_Renderer* renderer) 
{
    if (!m_alienTexture) { 
        m_alienTexture = getTexture("src/images/sprites/Harkonen_teste_3.png", renderer);
    }
    SDL_RenderCopy(renderer, m_alienTexture, NULL, &m_alien);

}


SDL_Rect Alien::getRect() const {
    return m_alien;
}


int Alien::getType() const {
    return m_type;
}


void Alien::setPositionY(int y) {
    m_alien.y = y;
}



SDL_Texture* Alien::getTexture(const char* filepath, SDL_Renderer* renderer) {
    SDL_Texture* alienTexture = TextureManager::LoadTexture(filepath, renderer);

    return alienTexture;
}