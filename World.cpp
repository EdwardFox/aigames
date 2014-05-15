#include "World.hpp"
#include "Game.hpp"
#include <stdexcept>

World::World(int width, int height) :
mEntities()
{
    createWorld(width, height);
}

void World::update(sf::Time dt)
{
    for(const auto& ent : mEntities)
    {
        ent.second->update(dt);
    }
}

void World::draw(sf::RenderTarget &target) const
{
    for(const auto& ent : mEntities)
    {
        ent.second->draw(target);
    }
}

void World::addEntity(std::string key, sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isEnd)
{
    mEntities[key] = std::unique_ptr<Entity>(new Entity(position, size, fill, outline, isStart, isEnd));
}

std::map<std::string, std::unique_ptr<Entity>>& World::getEntities()
{
    return mEntities;
}

void World::createWorld(int width, int height)
{
    int rows = width / (int)BOX_SIZE + 1;
    int columns = height / (int)BOX_SIZE + 1;

    for(int i = 0; i < columns; ++i)
    {
        for(int j = 0; j < rows; ++j)
        {
            sf::Vector2f position(j*BOX_SIZE, i*BOX_SIZE);
            sf::Vector2f size(BOX_SIZE, BOX_SIZE);
            sf::Color fill(255, 255, 255, 255);
            sf::Color outline(0, 0, 0, 255);
            std::string pos = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);

            if(i == columns/2) {
                if(j == rows/3) {
                    addEntity(pos, position, size, fill, outline, true, false);
                } else if(j == (int)(rows/1.5)) {
                    addEntity(pos, position, size, fill, outline, false, true);
                } else {
                    addEntity(pos, position, size, fill, outline, false, false);
                }
            } else {
                addEntity(pos, position, size, fill, outline, false, false);
            }
        }
    }
}

void World::deleteWorld() {
    mEntities.clear();
}

Entity* World::getEntityAtPosition(int x, int y) {
    //std::cout << "Input: " << x << "x" << y << std::endl;

    int row = x / (int)BOX_SIZE;
    int column = y / (int)BOX_SIZE;

    //std::cout << "Amount: " << row << "x" << column << std::endl;

    row *= BOX_SIZE;
    column *= BOX_SIZE;

    //std::cout << "Calculated: " << row << "x" << column << std::endl;

    std::string pos = std::to_string(row) + "_" + std::to_string(column);

    try {
        return mEntities.at(pos).get();    
    } catch(std::out_of_range c) {
        return NULL;
    }

}
