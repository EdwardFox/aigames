#include "Entity.hpp"

Entity::Entity() :
mShape()
, wall(false)
, start(false)
, end(false)
{
}

    
Entity::Entity(const sf::Vector2f position, const sf::Vector2f size, const sf::Color fill, const sf::Color outline, bool isStart, bool isEnd) {
    mShape.setSize(size);
    mShape.setPosition(position.x, position.y);
    mShape.setFillColor(fill);
    mShape.setOutlineColor(outline);
    mShape.setOutlineThickness(1.0f);

    setStart(isStart);
    setEnd(isEnd);

    if(isStart)
        setColor(NODE_START);

    if(isEnd)
        setColor(NODE_GOAL);
}

void Entity::update(sf::Time dt) 
{

}

void Entity::draw(sf::RenderTarget &target) 
{
    target.draw(mShape);
}

void Entity::setColor(sf::Color c) 
{
    mShape.setFillColor(c);
}

void Entity::setWall(bool w) {
    wall = w;
}

void Entity::setStart(bool s) {
    start = s;
}

void Entity::setEnd(bool e) {
    end = e;
}

bool Entity::isWall() {
    return wall;
}

bool Entity::isStart() {
    return start;    
}

bool Entity::isEnd() {
    return end;
}
