#pragma once
#include "piece.h"
class bishop :
    public piece
{
public:
    bishop(position p_pos, colour p_pcolour, texture& image) : piece(p_pos, p_pcolour, image) 
    {  
        pice_code = p_pcolour == colour::black? pieces_code::Bbishop : pieces_code::Wbishop; 
    }

    //std::vector<position> AllMoves() override;

    std::vector<position> AvailableMoves(class board& grid) override;

};

