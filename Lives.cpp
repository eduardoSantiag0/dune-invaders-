#include "Lives.hpp"
#include <iostream>

Lives::Lives(int posx, int posy)
{
    heart_rect = {posx, posy, 30, 30};
}

Lives::~Lives()
{
    std::cout << "Menos uma vida\n";
}