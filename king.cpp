#include "king.h"
#include "board.h"


void king::specialcases(RenderWindow& winren, std::array<texture*, 12>& images, board& grid)
{
    moved = true;

    specialcases(grid);
}

void king::specialcases(board& grid)
{
    switch (pcolour)
    {
    case colour::black:
        grid.set_black_king(pos);
        break;
    case colour::white:
        grid.set_white_king(pos);
        break;
    }
}

std::vector<position> king::legalmoves(board& grid)
{
    std::vector<position> temp = AvailableMoves(grid);
    std::vector<position> result;
    position la = pos;
    for (const position& i : temp)
    {
        bool testing = test(grid, i);
        if (test(grid, i))
            result.push_back(i);
    }

    position castle_right = pos + position(2, 0);
    position go_right = pos + position(1, 0);

    position castle_left = pos + position(-2, 0);
    position go_left = pos + position(-1, 0);

    auto it_castle_right = std::find(result.begin(), result.end(), castle_right);
    if (it_castle_right != result.end())
    {
        auto it_go_right = std::find(result.begin(), result.end(), go_right);
        if (it_go_right == result.end())
            result.erase(it_castle_right);
    }

    auto it_castle_left = std::find(result.begin(), result.end(), castle_left);
    if (it_castle_left != result.end())
    {
        auto it_go_left = std::find(result.begin(), result.end(), go_left);
        if (it_go_left == result.end())
            result.erase(it_castle_left);
    }

    return result;
}




bool king::check_castle(board& grid, position end, int direction)
{
    if (!pos.insideboard() || !end.insideboard())
        return false;

    if (!grid[end.y][end.x].nonempty())
        return false;

    if (grid[end.y][end.x]->getmoved() || grid[pos.y][pos.x]->getmoved())
        return false;

    for (position index = pos + position(direction, 0); !(index == end); index = index + position(direction, 0))
    {
        if (grid[index.y][index.x].nonempty())
            return false;
    }

    return true;

}

std::vector<position> king::AvailableMoves(board& grid)
{
    /*
    * /   /   /   /   /   /   /   /   /
    * /   /   /   /   /   /   /   /   /
    * /   /   / + / + / + /   /   /   /
    * /   /   / + / k / + /   /   /   /
    * /   /   / + / + / + /   /   /   /
    * /   /   /   /   /   /   /   /   /
    * /   /   /   /   /   /   /   /   /
    * /   /   /   /   /   /   /   /   /
    */

    std::vector<position> result;

    position to_add[] = {
        pos + position(0, -1),  // up
        pos + position(-1, -1), // top left
        pos + position(1, -1),  // top right
        pos + position(1, 0),   // right
        pos + position(-1, 0),  // left
        pos + position(0, 1),   // down
        pos + position(-1, 1),  // down left
        pos + position(1, 1)    // down right
    };

    for (int i = 0; i < 9; ++i)
        if (to_add[i].insideboard())
            if ((!grid[to_add[i].y][to_add[i].x].nonempty()) || (grid[to_add[i].y][to_add[i].x]->getcolour() != pcolour) )
                result.push_back(to_add[i]);

    position right_rook = pos + position(3, 0);

    if (check_castle(grid, right_rook, 1))
        result.push_back(pos + position(2, 0));

    position left_rook = pos + position(-4, 0);

    if (check_castle(grid, left_rook, -1))
        result.push_back(pos + position(-2, 0));
    
    return result;
}
