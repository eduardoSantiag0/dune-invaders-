#include <SDL2/SDL.h>

class Lives
{
private:
    SDL_Rect heart_rect;
public:
    Lives(int posx, int posy);
    ~Lives();
};


