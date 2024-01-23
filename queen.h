#pragma once
#include "piece.h"
class queen :
    public piece
{

public:
    queen(position p_pos, colour p_pcolour, texture& image) : piece(p_pos, p_pcolour, image) 
    {
        pice_code = p_pcolour == colour::black ? pieces_code::Bqueen : pieces_code::Wqueen;
    }

    std::vector<position> AvailableMoves(class board& grid) override;


};

