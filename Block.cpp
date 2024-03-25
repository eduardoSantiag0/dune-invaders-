#include "Block.hpp"

Block::Block (int m_pos_x, int m_pos_y) : m_pos_x(m_pos_x), m_pos_y(m_pos_y)
{   
}

void Block::draw (SDL_Renderer* render) {
    SDL_Rect rectangulo = {m_pos_x, m_pos_y, 5, 5}; 

    SDL_SetRenderDrawColor(render, 243, 216, 63, 255);
    SDL_RenderFillRect(render, &rectangulo);
}

int Block::getPos_X () {
    return m_pos_x;
}

int Block::getPos_Y () {
    return m_pos_y;
}