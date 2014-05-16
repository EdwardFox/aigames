#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include "Data.hpp"

struct NodeRecord;

class Connection
{
    public:
        Connection();
        Connection(float cost, std::unique_ptr<NodeRecord>* fromNode, std::string toNode);

        float mCost;
        std::unique_ptr<NodeRecord>* mFromNode;
        std::string mToNode;
};

struct NodeRecord
{
    NodeRecord() : node(""), connection(std::shared_ptr<Connection>()), costSoFar(0)
    {
        
    }

    std::string node;
    std::shared_ptr<Connection> connection;
    float costSoFar;
};

#endif
