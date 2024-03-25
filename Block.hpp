#include <SDL2/SDL.h>

class Block 
{
public: 
    Block (int posx, int posy);
    void draw(SDL_Renderer* render);
    int getPos_X();
    int getPos_Y();

private: 
    int m_pos_x;
    int m_pos_y;
    
};