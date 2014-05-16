#include "World.hpp"
#include "Game.hpp"
#include <stdexcept>

World::World(int width, int height) :
mEntities()
, mStartTile(NULL)
, mGoalTile(NULL)
{
    createWorld(width, height);
}

void World::update(sf::Time dt)
{
    for(const auto& ent : mEntities)
    {
        ent.second->update(dt);
    }

    findPath(Algorithm::ASTAR, Heuristic::EUCLIDEAN);
}

void World::draw(sf::RenderTarget &target) const
{
    for(const auto& ent : mEntities)
    {
        ent.second->draw(target);
    }
}

void World::addEntity(std::string key, sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline, bool isStart, bool isEnd, bool isWall)
{
    mEntities[key] = std::unique_ptr<Entity>(new Entity(position, size, fill, outline, isStart, isEnd, isWall));
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

            // Start && End
            if(i == columns/2) {
                if(j == rows/3) {
                    addEntity(pos, position, size, fill, outline, true, false, false);
                    mStartTile = mEntities.at(pos).get();
                } else if(j == (int)(rows/1.5)) {
                    addEntity(pos, position, size, fill, outline, false, true, false);
                    mGoalTile = mEntities.at(pos).get();
                } else {
                    addEntity(pos, position, size, fill, outline, false, false, false);
                }
            } else {
                addEntity(pos, position, size, fill, outline, false, false, false);
            }
        }
    }
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

void World::setStartTile(Entity* ent)
{
    mStartTile = ent;
}

void World::setGoalTile(Entity* ent)
{
    mGoalTile = ent;
}

void World::findPath(Algorithm alg, Heuristic heu)
{
    clearPath();

    switch(alg)
    {
        case Algorithm::DIJKSTRA:
            runDijkstra();
            break;
        case Algorithm::ASTAR:
            runAStar(heu);
            break;
        default:
            break;
    }
}

void World::runDijkstra()
{

}

void World::runAStar(Heuristic heu)
{
    Entity* start = mStartTile;
    start->state = NodeState::OPEN;

    std::map<std::string, Entity*> openList;
    openList[start->getIndex()] = start;

    Entity* current = NULL;

    while(openList.size() > 0)
    {
        current = getLowestScore(openList);

        if(current == mGoalTile)
            break;

        current->state = NodeState::CLOSED;
        auto neighbors = getValidNodes(current, false);

        for(auto& neighbor : neighbors)
        {
            Entity* neigh = NULL;
            try 
            {
                neigh = mEntities.at(neighbor).get();
            }
            catch(std::out_of_range ex)
            {
                continue; 
            }

            if(neigh->state == NodeState::CLOSED)
                continue;

            if(neigh->state == NodeState::OPEN)
            {
                float currentScore = current->costSoFar+1;
                if(currentScore < neigh->costSoFar)
                {
                    neigh->costSoFar = currentScore;
                    neigh->parent = current;
                }
            }

            if(neigh->state == NodeState::UNVISITED)
            {
                openList[neigh->getIndex()] = neigh;
                neigh->costSoFar = current->costSoFar + 1;
                neigh->parent = current;
            }
        }
        openList.erase(current->getIndex());
    }

    if(current != mGoalTile)
    {
        // No solution
    } else {
        while(current != mStartTile)
        {
            if(current != mGoalTile)
            {
                current->setColor(sf::Color::Yellow);
                current->isPath = true;
            }
            current = current->parent;
        }
    }
}

Entity* World::getLowestScore(std::map<std::string, Entity*> openList)
{
    Entity* result = NULL;
    for(auto& ent : openList)
    {
        if(result == NULL)
        {
            result = ent.second;
        }

        if(ent.second->costSoFar < result->costSoFar)
            result = ent.second;
    }

    return result;
}

std::vector<std::string> World::getValidNodes(Entity* ent, bool dia)
{
    std::vector<std::string> neighbors = ent->getNeighbors(dia);

    std::vector<std::string> valid;

    for(auto& neigh : neighbors)
    {
        Entity* ent = NULL;

        try
        {
            ent = mEntities.at(neigh).get();
        }
        catch (std::out_of_range ex)
        {
            continue;
        }
        
        if(!ent->isWall())
            valid.push_back(neigh);
    }

    return valid;
}

void World::resetWorld(int width, int height)
{
    mEntities.clear();
    createWorld(width, height);
}

void World::clearPath()
{
    for(auto& ent : mEntities)
    {
        ent.second->costSoFar = 0;
        ent.second->parent = NULL;
        ent.second->state = NodeState::UNVISITED;

        if(ent.second->isPath && !ent.second->isWall())
            ent.second->setColor(NODE_FREE);
    }
}
