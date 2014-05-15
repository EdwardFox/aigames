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
        Entity(const sf::Vector2f position, const sf::Vector2f size, const sf::Color fill, const sf::Color outline, bool isStart, bool isEnd); 

        /**
        * @brief Updates the entity's position and sets the visual representation accordingly
        *
        * @param dt Time between 2 update ticks
        */
        virtual void update(sf::Time dt);

        /**
        * @brief Draws the entity
        *
        * @param target The target surface to draw on (most likely the render window)
        */
        virtual void draw(sf::RenderTarget &target);

         
        /**
        * @brief 
        *
        * @param c
        */
        virtual void setColor(sf::Color c);

        virtual void setWall(bool w);
        virtual void setStart(bool s);
        virtual void setEnd(bool e);

        virtual bool isWall();
        virtual bool isStart();
        virtual bool isEnd();

    protected:
        sf::RectangleShape mShape;

    private:
        bool wall;
        bool start;
        bool end;
};

#endif
