#pragma once
#include "piece.h"
class rook :
    public piece
{
private:
public:
    rook(position p_pos, colour p_pcolour, texture& image) : piece(p_pos, p_pcolour, image) 
    {
        pice_code = p_pcolour == colour::black ? pieces_code::Brook : pieces_code::Wrook;
    }



    void specialcases(RenderWindow& winren, std::array<texture*, 12>& images, class board& grid) override;

    std::vector<position> AvailableMoves(class board& grid) override;

};

