#include "bishop.h"
#include"board.h"

//std::vector<position> bishop::AllMoves()
//{
//    /*
//    * / + /   /   /   /   /   / + /   /
//    * /   / + /   /   /   / + /   /   /
//    * /   /   / + /   / + /   /   /   /
//    * /   /   /   / b /   /   /   /   /
//    * /   /   / + /   / + /   /   /   /
//    * /   / + /   /   /   / + /   /   /
//    * / + /   /   /   /   /   / + /   /
//    * /   /   /   /   /   /   /   / + /
//    */
//
//    std::vector<position> result;
//
//    for (position index = pos; index.insideboard(); index = index + position(-1, -1)) // top left
//    {
//        if (grid[index.y][index.x].nonempty())
//            if (grid[index.y][index.x]->getcolour() != pcolour)
//            {
//                result.push_back(index);
//                break;
//            }
//        result.push_back(index);
//    }
//
//    for (position index = pos; index.insideboard(); index = index + position(1, -1)) // top right
//    {
//        if (grid[index.y][index.x].nonempty())
//            if (grid[index.y][index.x]->getcolour() != pcolour)
//            {
//                result.push_back(index);
//                break;
//            }
//        result.push_back(index);
//    }
//    
//    for (position index = pos; index.insideboard(); index = index + position(-1, 1)) // down left
//    {
//        if (grid[index.y][index.x].nonempty())
//            if (grid[index.y][index.x]->getcolour() != pcolour)
//            {
//                result.push_back(index);
//                break;
//            }
//        result.push_back(index);
//    }
//    
//    for (position index = pos; index.insideboard(); index = index + position(1, 1)) // down right
//    {
//        if (grid[index.y][index.x].nonempty())
//            if (grid[index.y][index.x]->getcolour() != pcolour)
//            {
//                result.push_back(index);
//                break;
//            }
//        result.push_back(index);
//    }
//
//
//    return result;
//}

std::vector<position> bishop::AvailableMoves(board& grid)
{
    /*
    * / + /   /   /   /   /   / + /   /
    * /   / + /   /   /   / + /   /   /
    * /   /   / + /   / + /   /   /   /
    * /   /   /   / b /   /   /   /   /
    * /   /   / + /   / + /   /   /   /
    * /   / + /   /   /   / + /   /   /
    * / + /   /   /   /   /   / + /   /
    * /   /   /   /   /   /   /   / + /
    */

    std::vector<position> result;

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
