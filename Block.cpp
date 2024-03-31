#include "Block.hpp"

Block::Block (int m_pos_x, int m_pos_y) {   
    rectangulo = {m_pos_x, m_pos_y, 5, 5};
}

void Block::draw (SDL_Renderer* render) {
    // SDL_SetRenderDrawColor(render, 253, 114, 78, 255);
    SDL_SetRenderDrawColor(render, 239, 114, 45, 255);
    SDL_RenderFillRect(render, &rectangulo);
}


 SDL_Rect Block::getRect() {
    return rectangulo;
 }