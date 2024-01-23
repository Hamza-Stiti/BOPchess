#pragma once
#include "piece.h"


class pawn :
    public piece
{
private:
    int direction;
public:
    pawn(position p_pos, colour p_pcolour, texture& image) : piece(p_pos, p_pcolour, image), direction((int)pcolour) 
    {
        pice_code = p_pcolour == colour::black ? pieces_code::Bpawn : pieces_code::Wpawn;
    }

    void specialcases(RenderWindow& winren, std::array<texture*, 12>& images, class board& grid) override;

    std::vector<position> AvailableMoves(class board& grid) override;

};

//(int)colour::black == 1, (int)colour::white == -1