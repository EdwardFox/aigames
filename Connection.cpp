#include "Connection.hpp"

Connection::Connection() : 
mCost(0)
, mFromNode(NULL)
, mToNode("")
{
    
}

Connection::Connection(float cost, std::unique_ptr<NodeRecord>* fromNode, std::string toNode) :
mCost(cost)
, mFromNode(fromNode)
, mToNode(toNode)
{
    
}
