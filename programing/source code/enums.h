#pragma once

enum class colour {
	white = -1, black = 1
};

enum class pieces_code {
	Wpawn = 0, Bpawn = 1, Wking = 2, Bking = 3, Wqueen = 4, Bqueen = 5, Wbishop = 6, Bbishop = 7, Wknight = 8, Bknight = 9, Wrook = 10, Brook = 11, piece, empty = -1
};

enum class game {
	contin, checkmate, stalemate
};