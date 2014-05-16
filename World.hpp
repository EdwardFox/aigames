#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <map>
#include "Entity.hpp"
#include "Data.hpp"

class World
{
    public:
        typedef std::unique_ptr<Entity> entPtr;

    public:
        /**
        * @brief Default constructor
        */
        World(int width, int height);

        /**
        * @brief Updates the world and all its entities
        *
        * @param dt Time passed between 2 update ticks
        */
        void update(sf::Time dt);

        /**
        * @brief Draws the world and all entities
        *
        * @param target
        */
        void draw(sf::RenderTarget &target) const;

        /**
        * @brief Adds an entity at position x/y
        *
        * @param x X coordinate
        * @param y Y coordinate
        */
        void addEntity(std::string key, sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isEnd, bool isWall);

        std::map<std::string, std::unique_ptr<Entity>>& getEntities();

        Entity* getEntityAtPosition(int x, int y);

        void createWorld(int width, int height);
        void resetWorld(int width, int height);
        void clearPath();

        void setStartTile(Entity* ent);
        void setGoalTile(Entity* ent);

        void findPath(Algorithm alg, Heuristic heu);

    private:
        /**
        * @brief 
        */
        std::map<std::string, entPtr> mEntities;

        Entity* mStartTile;
        Entity* mGoalTile;

        void runDijkstra();
        void runAStar(Heuristic heu);

        Entity* getLowestScore(std::map<std::string, Entity*> openList);
        std::vector<std::string> getValidNodes(Entity* ent, bool dia);
};

#endif
