#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.hpp"
#include "Data.hpp"
#include "Connection.hpp"
#include "PathfindingList.hpp"

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
        void addEntity(std::string key, sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isEnd);

        std::map<std::string, std::unique_ptr<Entity>>& getEntities();

        Entity* getEntityAtPosition(int x, int y);

        void createWorld(int width, int height);

        void deleteWorld();

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

        std::vector<std::shared_ptr<Connection>> getConnections(std::unique_ptr<NodeRecord>* fromNode);        
};

#endif
