#include <iostream>
#include "Laser.hpp"


Laser::Laser() {
    std::cout << "Laser criado\n";
    m_active = true;
    m_speed = 5;
}

void Laser::move() {
    m_laser.y -= m_speed;
    if (m_laser.y + m_laser.h <= 0) {
        std::cout << "Laser Destruido\n";
        m_active = false;
    }
}

void Laser::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &m_laser);
}

bool Laser::setActive(bool activo) {
    m_active = activo ;
}

bool Laser::getActive () const 
{
    return m_active;
}

void Laser::setPosition (int x, int y, int w, int h) {
    m_laser.x = x;
    m_laser.y = y;
    m_laser.w = w;
    m_laser.h = h;
}

int Laser::getPos_Y() const {
    return m_laser.y;
}