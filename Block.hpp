#include <SDL2/SDL.h>

class Block 
{
public: 
    Block (int posx, int posy);
    void draw(SDL_Renderer* render);
    SDL_Rect getRect();

private: 
    SDL_Rect rectangulo;
    
};