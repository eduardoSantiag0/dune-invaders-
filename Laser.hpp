#include <SDL2/SDL.h>

class Laser 
{
private: 
    int m_speed;
    SDL_Rect m_laser;
    bool m_active;
public:
    Laser();
    void move ();
    void draw(SDL_Renderer* renderer);
    bool setActive(bool activo);
    bool getActive () const;
    void setPosition (int x, int y, int h, int w);
    int getPos_Y() const;
};