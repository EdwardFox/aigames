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
                    mStartTile = mEntities.at(pos).get();
                } else if(j == (int)(rows/1.5)) {
                    addEntity(pos, position, size, fill, outline, false, true);
                    mGoalTile = mEntities.at(pos).get();
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
    switch(alg)
    {
        case Algorithm::DIJKSTRA:
            runDijkstra();
            break;
        case Algorithm::ASTAR:
            break;
        default:
            break;
    }
}

void World::runDijkstra()
{
    // Initialize an empty connection
    std::unique_ptr<Connection> emptyConnection(new Connection());
    emptyConnection->mFromNode = NULL;

    // Initialize the start record
    std::unique_ptr<NodeRecord> startRecord(new NodeRecord());
    startRecord->node = mStartTile->getIndex();
    startRecord->connection = std::unique_ptr<Connection>(std::move(emptyConnection));
    startRecord->costSoFar = 0;

    // Initialize the lists
    PathfindingList open;
    open.records.push_back(std::move(startRecord));
    PathfindingList closed;

    std::vector<std::unique_ptr<NodeRecord>>::iterator current;

    // Iterate through processing each node
    while(open.records.size() > 0)
    {
        // Find the smallest element in the open list
        current = open.smallestElement();

        // If it is the goal node, terminate
        if((*current)->node == mGoalTile->getIndex())
            break;

        // Otherwise get its outgoing connections 
        std::vector<std::shared_ptr<Connection>> connections = this->getConnections(&(*current));
        float currentCost = (*current)->costSoFar;

        // Loop through each connection in turn
        //for(auto& con : connections)
        for(auto it = connections.begin(); it != connections.end(); ++it)
        {
            std::string endNode = (*it)->mToNode;
            float endNodeCost = currentCost + (*it)->mCost;
            std::unique_ptr<NodeRecord> endNodeRecord(new NodeRecord());


            // Skip if the node is closed
            if(closed.contains(endNode))
                continue;
            // ... or if it is open and we've found a worse route
            else if(open.contains(endNode))
            {
                // Here we find the record in the open list
                // corresponding to the endNode.
                std::vector<std::unique_ptr<NodeRecord>>::iterator it = open.find(endNode);
                //endNodeRecord = open.find(endNode);

                if((*it)->costSoFar <= endNodeCost)
                    continue;

                endNodeRecord = std::unique_ptr<NodeRecord>(std::move((*it)));

            // Otherwise we know we've got an unvisited
            // node, so make a record for it
            } else {
                endNodeRecord->node = endNode;
            }

            // We're here if we need to update the node
            // Update the cost and connection
            endNodeRecord->costSoFar = endNodeCost;
            endNodeRecord->connection = (*it);

            // And add it to the open list
            if(!open.contains(endNode))
                open.records.push_back(std::move(endNodeRecord));
        }

        // We've finished looking at the connections for
        // the current node, so add it to the closed list
        // and remove it from the open list
        closed.records.push_back(std::unique_ptr<NodeRecord>(current->release()));
        open.records.erase(current);
    }

    // We're here if we've either found the goal, or
    // if we've no more nodes to search, find which.
    if((*current)->node != mGoalTile->getIndex())
    {
        // We've run out of nodes without finding the
        // goal, so there's no solution
    } else {
        // Compile the list of connections in the path
        std::vector<std::unique_ptr<Connection>> path;

        std::unique_ptr<NodeRecord> traceback(std::move((*current)));

        // Work back along the path, accumulating
        // connections
        while(traceback->node != mStartTile->getIndex())
        {
            mEntities.at(traceback->node)->setColor(sf::Color::Yellow);

            //path.push_back((*current)->connection);
            //current = (*current)->connection->mFromNode;
            traceback = std::unique_ptr<NodeRecord>(std::move((*current)));
        }
    }
}

std::vector<std::shared_ptr<Connection>> World::getConnections(std::unique_ptr<NodeRecord>* fromNode)
{
    std::vector<std::shared_ptr<Connection>> connections;
    Entity* current = mEntities.at((*fromNode)->node).get();

    for(auto& neighbor : current->getNeighbors())
    {
        std::shared_ptr<Connection> con(new Connection(1, fromNode, neighbor));
        connections.push_back(con);
    }

    return connections;
}
