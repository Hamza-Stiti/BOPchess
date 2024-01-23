#include "rook.h"
#include "board.h"


void rook::specialcases(RenderWindow& winren, std::array<texture*, 12>& images, board& grid)
{
    moved = true;
}

std::vector<position> rook::AvailableMoves(board& grid)
{

    /*
    * /   /   /   / + /   /   /   /   /
    * /   /   /   / + /   /   /   /   /
    * /   /   /   / + /   /   /   /   /
    * / + / + / + / r / + / + / + / + /
    * /   /   /   / + /   /   /   /   /
    * /   /   /   / + /   /   /   /   /
    * /   /   /   / + /   /   /   /   /
    * /   /   /   / + /   /   /   /   /
    */

    std::vector<position> result;

    for (position index = pos + position(0, -1); index.insideboard(); index = index + position(0, -1)) // up
    {
        if (grid[index.y][index.x].nonempty())
        {
            if (grid[index.y][index.x]->getcolour() != pcolour)
            {
                result.push_back(index);
            }
            break;
        }

        result.push_back(index);
    }

    for (position index = pos + position(0, 1); index.insideboard(); index = index + position(0, 1)) // down
    {
        if (grid[index.y][index.x].nonempty())
        {
            if (grid[index.y][index.x]->getcolour() != pcolour)
            {
                result.push_back(index);
            }
            break;
        }

        result.push_back(index);
    }

    for (position index = pos + position(1, 0); index.insideboard(); index = index + position(1, 0)) // right
    {
        if (grid[index.y][index.x].nonempty())
        {
            if (grid[index.y][index.x]->getcolour() != pcolour)
            {
                result.push_back(index);
            }
            break;
        }

        result.push_back(index);
    }

    for (position index = pos + position(-1, 0); index.insideboard(); index = index + position(-1, 0)) // left
    {
        if (grid[index.y][index.x].nonempty())
        {
            if (grid[index.y][index.x]->getcolour() != pcolour)
            {
                result.push_back(index);
            }
            break;
        }

        result.push_back(index);
    }


    return result;
}
