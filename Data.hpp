#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

static const float BOX_SIZE = 50.0f;

struct ActiveInput
{
    sf::Vector2i mousePos = sf::Vector2i(0,0);
    bool mouseDown = false;
    bool mouseClicked = false;
};

#endif
