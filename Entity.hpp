#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Data.hpp"

class Entity
{
    public:
        /**
        * @brief Default constructor
        */
        Entity();


        /**
        * @brief Constructor
        *
        * @param position
        * @param size
        * @param fill
        * @param outline
        */
        Entity(const sf::Vector2f position, const sf::Vector2f size, const sf::Color fill, const sf::Color outline); 

        /**
        * @brief Updates the entity's position and sets the visual representation accordingly
        *
        * @param dt Time between 2 update ticks
        */
        virtual void update(sf::Time dt, ActiveInput ai);

        /**
        * @brief Draws the entity
        *
        * @param target The target surface to draw on (most likely the render window)
        */
        virtual void draw(sf::RenderTarget &target);

        virtual void setColor(sf::Color c);

    protected:
        sf::RectangleShape mShape;

    private:
};

#endif
