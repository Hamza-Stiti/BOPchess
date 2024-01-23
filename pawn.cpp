#include "pawn.h"
#include "board.h"
#include "SDL_loops.h"





std::vector<position> pawn::AvailableMoves(board& grid)
{
    std::vector<position> result;

    position to_add[] = {
        pos + position(0, direction),       // 1-up
        pos + position(0, 2 * direction),   //2_up
        pos + position(1, direction),       //eat
        pos + position(-1, direction)       //eat
    };

    bool not_blocked = false;
    if (to_add[0].insideboard())
        if (!grid[to_add[0].y][to_add[0].x].nonempty())
        {
            result.push_back(to_add[0]); //1-up
            not_blocked = true;
        }

    if (!moved && not_blocked)
        if(to_add[1].insideboard())
            if (!grid[to_add[1].y][to_add[1].x].nonempty())
            {
                result.push_back(to_add[1]); //2-up
            }

    for (int i = 2; i < 4; ++i)
    {
        if (to_add[i].insideboard())
            if (grid[to_add[i].y][to_add[i].x].nonempty())
                if (grid[to_add[i].y][to_add[i].x]->getcolour() != pcolour)
                    result.push_back(to_add[i]);
    }

    position p = grid.get_enpassant();

    if (grid.get_enpassant() == (pos + position(1, 0)))
        result.push_back(pos + position(1, direction));

    if (grid.get_enpassant() == (pos + position(-1, 0)))
        result.push_back(pos + position(-1, direction));

    return result;
}

void pawn::specialcases(RenderWindow& winren, std::array<texture*, 12>& images, board& grid)
{
    moved = true;
    if (pos.y == 0 || pos.y == 7)
        winren.promotion(grid, images, pos);
}
