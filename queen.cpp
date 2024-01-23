#include "queen.h"
#include "board.h"





std::vector<position> queen::AvailableMoves(board& grid)
{

    /*
    * / + /   /   / + /   /   / + /   /
    * /   / + /   / + /   / + /   /   /
    * /   /   / + / + / + /   /   /   /
    * / + / + / + / q / + / + / + / + /
    * /   /   / + / + / + /   /   /   /
    * /   / + /   / + /   / + /   /   /
    * / + /   /   / + /   /   / + /   /
    * /   /   /   / + /   /   /   / + /
    */


    std::vector<position> result;

    // +
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

    // x
    for (position index = pos + position(-1, -1); index.insideboard(); index = index + position(-1, -1)) // top left
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

    for (position index = pos + position(1, -1); index.insideboard(); index = index + position(1, -1)) // top right
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

    for (position index = pos + position(-1, 1); index.insideboard(); index = index + position(-1, 1)) // down left
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

    for (position index = pos + position(1, 1); index.insideboard(); index = index + position(1, 1)) // down right
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
