#ifndef PATHFINDINGLIST_HPP
#define PATHFINDINGLIST_HPP

#include <vector>
#include <memory>
#include "Data.hpp"
#include "Connection.hpp"

class PathfindingList
{
    public:
        PathfindingList();
        bool contains(std::string node);
        std::vector<std::unique_ptr<NodeRecord>>::iterator smallestElement();
        std::vector<std::unique_ptr<NodeRecord>>::iterator find(std::string node);
        std::vector<std::unique_ptr<NodeRecord>> records;
};

#endif
