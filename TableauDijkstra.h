//
// Created by devws on 22/03/2019.
//

#ifndef GRAPHES_PJ_TABLEAUDIJKSTRA_H
#define GRAPHES_PJ_TABLEAUDIJKSTRA_H

#include <tuple>
#include <vector>


class TableauDijkstra {

public:

    TableauDijkstra();
    ~TableauDijkstra();




private:

    std::vector<std::vector<std::pair<int, int>>> tableau;
    std::vector<int> sommetsFixes;

};


#endif //GRAPHES_PJ_TABLEAUDIJKSTRA_H
