#include "Entity.hpp"

Entity::Entity() :
mShape()
{
}

    
Entity::Entity(const sf::Vector2f position, const sf::Vector2f size, const sf::Color fill, const sf::Color outline) {
    mShape.setSize(size);
    mShape.setPosition(position.x, position.y);
    mShape.setFillColor(fill);
    mShape.setOutlineColor(outline);
    mShape.setOutlineThickness(1.0f);
}

void Entity::update(sf::Time dt, ActiveInput ai) 
{
    if(ai.mouseDown)
    {
        sf::FloatRect rect = mShape.getGlobalBounds();

        if(rect.contains(ai.mousePos.x, ai.mousePos.y))
        {
            this->setColor(sf::Color::Red);
        }
    }
}

void Entity::draw(sf::RenderTarget &target) 
{
    target.draw(mShape);
}

void Entity::setColor(sf::Color c) 
{
    mShape.setFillColor(c);
}
