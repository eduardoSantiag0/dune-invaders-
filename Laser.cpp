#include <iostream>
#include "Laser.hpp"


Laser::Laser() {
    m_active = true;
    m_speed = 5;
}

void Laser::move(Tipo tipo) {
    if (tipo == Laser::Tipo::Player) {
        m_laser.y -= m_speed;
        if (m_laser.y + m_laser.h <= 0) {
            m_active = false;
        }
    } else if (tipo == Laser::Tipo::Alien) {
        m_laser.y += m_speed;
        if (m_laser.y + m_laser.h >= 480) {
            m_active = false;
        }

    }
}

void Laser::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 160, 47, 64, 255); 
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


SDL_Rect Laser::getRect() const {
    return m_laser;
}