#include <SDL2/SDL.h>
#include <vector>
#include "TextureManager.hpp"

class Alien 
{
private: 
    int m_speed;
    int m_dir;
    int m_type;
    SDL_Texture* m_alienTexture;

    int m_red; 
    int m_green; 
    int m_blue; 
    
public: 
    Alien(int m_type, int pos_x, int pos_y);
    SDL_Rect m_alien;
    void move(int dir);
    void draw(SDL_Renderer* renderer);

    SDL_Rect getRect() const;
    int getType() const;
    void setPositionY(int y);
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);

};