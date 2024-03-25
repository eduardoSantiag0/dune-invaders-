#include <SDL2/SDL.h>
#include <vector>
#include "Block.hpp"

class Dunas 
{
public:
    Dunas (int posx, int posy);
    void draw(SDL_Renderer* render);
    int m_pos_x;
    int m_pos_y;
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;
private:

};