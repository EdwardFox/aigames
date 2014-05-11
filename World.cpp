#include "World.hpp"
#include "Game.hpp"

World::World() :
mEntities()
{
    createWorld();
}

void World::update(sf::Time dt, ActiveInput ai)
{
    for(const auto& ent : mEntities)
    {
        ent.second->update(dt, ai);
    }
}

void World::draw(sf::RenderTarget &target) const
{
    for(const auto& ent : mEntities)
    {
        ent.second->draw(target);
    }
}

void World::addEntity(std::string key, sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline)
{
    mEntities[key] = std::unique_ptr<Entity>(new Entity(position, size, fill, outline));
}

std::map<std::string, std::unique_ptr<Entity>>& World::getEntities()
{
    return mEntities;
}

void World::createWorld()
{
    for(int i = 0; i < 15; ++i)
    {
        for(int j = 0; j < 20; ++j)
        {
            sf::Vector2f position(j*BOX_SIZE, i*BOX_SIZE);
            sf::Vector2f size(BOX_SIZE, BOX_SIZE);
            sf::Color fill(255, 255, 255, 255);
            sf::Color outline(0, 0, 0, 255);
            std::string pos = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);
            
            addEntity(pos, position, size, fill, outline);
        }
    }
}
