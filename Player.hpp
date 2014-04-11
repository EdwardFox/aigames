#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Player
{
    public:
        Player();

        void handleEvent(const sf::Event& event);
};

#endif
