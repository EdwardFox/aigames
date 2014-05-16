#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
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
        Entity(const sf::Vector2f position, const sf::Vector2f size, const sf::Color fill, const sf::Color outline, bool isStart, bool isEndi, bool isWall); 

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

        virtual std::vector<std::string> getNeighbors(bool diagonal = true);

        virtual std::string getIndex();

        NodeState state;
        Entity* parent;
        float costSoFar;
        bool isPath;

    protected:
        sf::RectangleShape mShape;

    private:
        bool wall;
        bool start;
        bool end;
};

#endif
