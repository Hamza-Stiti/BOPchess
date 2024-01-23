#include "knight.h"
#include "board.h"


std::vector<position> knight::AvailableMoves(board& grid)
{
    /*
    * /   /   /   /   /   /   /   /   /
    * /   /   / + /   / + /   /   /   /
    * /   / + /   /   /   / + /   /   /
    * /   /   /   / n /   /   /   /   /
    * /   / + /   /   /   / + /   /   /
    * /   /   / + /   / + /   /   /   /
    * /   /   /   /   /   /   /   /   /
    * /   /   /   /   /   /   /   /   /
    */

    std::vector<position> result;



    position to_add[] = {
        pos + position(2, 1),
        pos + position(2, -1),
        pos + position(-2, 1),
        pos + position(-2, -1),
        pos + position(1, 2),
        pos + position(1, -2),
        pos + position(-1, 2),
        pos + position(-1, -2)
    };

    for (int i = 0; i < 9; ++i)
        if (to_add[i].insideboard())
            if ((!grid[to_add[i].y][to_add[i].x].nonempty()) || (grid[to_add[i].y][to_add[i].x]->getcolour() != pcolour))
                result.push_back(to_add[i]);


    return result;
}
