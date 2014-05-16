#include "PathfindingList.hpp"
#include <assert.h>

PathfindingList::PathfindingList() : records()
{
    
}

bool PathfindingList::contains(std::string node)
{
    for(auto& rec : records)
    {
        if(rec->node == node)
            return true;
    }
    return false;
}

std::vector<std::unique_ptr<NodeRecord>>::iterator PathfindingList::smallestElement()
{
    std::vector<std::unique_ptr<NodeRecord>>::iterator minimal;
    bool first = true;
    for(std::vector<std::unique_ptr<NodeRecord>>::iterator it = records.begin(); it != records.end(); ++it)
    {
        if(first)
        {
            minimal = it;
            first = false;
        }

        if((*it)->costSoFar < (*minimal)->costSoFar)
            minimal = it;

        if((*minimal)->costSoFar == 0)
            break;
    }

    return minimal;
}

std::vector<std::unique_ptr<NodeRecord>>::iterator PathfindingList::find(std::string node)
{
    for(std::vector<std::unique_ptr<NodeRecord>>::iterator it = records.begin(); it != records.end(); ++it)
    {
        if((*it)->node == node)
            return it;
    }

    // We should never ever reach this point
    assert(true);
    std::vector<std::unique_ptr<NodeRecord>>::iterator it;
    return it;
}
