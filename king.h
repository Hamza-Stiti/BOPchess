#pragma once
#include "piece.h"
class king :
    public piece
{
public:
    king(position p_pos, colour p_pcolour, texture& image) : piece(p_pos, p_pcolour, image) 
    {
        pice_code = p_pcolour == colour::black ? pieces_code::Bking : pieces_code::Wking;
    }

    void specialcases(class RenderWindow& winren, std::array<texture*, 12>& images, class board& grid) override;
    void specialcases(class board& grid) override;

    std::vector<position> legalmoves(class board& grid) override;

    bool check_castle(board& grid, position end, int direction);

    std::vector<position> AvailableMoves(class board& grid) override;

};

