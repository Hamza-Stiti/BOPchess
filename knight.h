#pragma once
#include "piece.h"
class knight :
    public piece
{
public:
    knight(position p_pos, colour p_pcolour, texture& image) : piece(p_pos, p_pcolour, image) 
    {
        pice_code = p_pcolour == colour::black ? pieces_code::Bknight : pieces_code::Wknight;
    }


    std::vector<position> AvailableMoves(class board& grid) override;
};

