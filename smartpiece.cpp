#include "smartpiece.h"
#include "board.h"





smartpiece::smartpiece(smartpiece& other)
{
	if (other.nonempty())
	{
		switch (other.ptr->getcode())
		{
		case pieces_code::Bbishop:
			ptr = new bishop(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wbishop:
			ptr = new bishop(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bking:
			ptr = new king(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wking:
			ptr = new king(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bknight:
			ptr = new knight(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wknight:
			ptr = new knight(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bpawn:
			ptr = new pawn(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wpawn:
			ptr = new pawn(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bqueen:
			ptr = new queen(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wqueen:
			ptr = new queen(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Brook:
			ptr = new rook(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wrook:
			ptr = new rook(other->getpos(), other->getcolour(), other->getimage());
			break;
		}
	}
	else
		ptr = nullptr;
}

smartpiece::smartpiece(std::array<texture*, 12>& images, pieces_code code, position pos)
{
	switch (code)
	{
	case pieces_code::Bbishop:
		ptr = new bishop(pos, colour::black, *images.at((int)code));
		break;
	case pieces_code::Wbishop:
		ptr = new bishop(pos, colour::white, *images.at((int)code));
		break;
	case pieces_code::Bking:
		ptr = new king(pos, colour::black, *images.at((int)code));
		break;
	case pieces_code::Wking:
		ptr = new king(pos, colour::white, *images.at((int)code));
		break;
	case pieces_code::Bknight:
		ptr = new knight(pos, colour::black, *images.at((int)code));
		break;
	case pieces_code::Wknight:
		ptr = new knight(pos, colour::white, *images.at((int)code));
		break;
	case pieces_code::Bpawn:
		ptr = new pawn(pos, colour::black, *images.at((int)code));
		break;
	case pieces_code::Wpawn:
		ptr = new pawn(pos, colour::white, *images.at((int)code));
		break;
	case pieces_code::Bqueen:
		ptr = new queen(pos, colour::black, *images.at((int)code));
		break;
	case pieces_code::Wqueen:
		ptr = new queen(pos, colour::white, *images.at((int)code));
		break;
	case pieces_code::Brook:
		ptr = new rook(pos, colour::black, *images.at((int)code));
		break;
	case pieces_code::Wrook:
		ptr = new rook(pos, colour::white, *images.at((int)code));
		break;
	case pieces_code::empty:
		ptr = nullptr;
		break;
	}
	
}



smartpiece::~smartpiece()
{
	destroy();
}

void smartpiece::copying(smartpiece& other)
{
	if (other.nonempty())
	{
		switch (other.ptr->getcode())
		{
		case pieces_code::Bbishop:
			ptr = new bishop(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wbishop:
			ptr = new bishop(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bking:
			ptr = new king(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wking:
			ptr = new king(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bknight:
			ptr = new knight(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wknight:
			ptr = new knight(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bpawn:
			ptr = new pawn(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wpawn:
			ptr = new pawn(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Bqueen:
			ptr = new queen(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wqueen:
			ptr = new queen(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Brook:
			ptr = new rook(other->getpos(), other->getcolour(), other->getimage());
			break;
		case pieces_code::Wrook:
			ptr = new rook(other->getpos(), other->getcolour(), other->getimage());
			break;
		}
	}
	else
		ptr = nullptr;
}

void smartpiece::destroy()
{
	delete ptr;
}

smartpiece& smartpiece::operator=(smartpiece&& other) noexcept
{
	if (this == &other) return *this;

	delete ptr;
	ptr = other.ptr;
	other.ptr = nullptr;

	return *this;
}

piece& smartpiece::operator*()
{
	return *ptr;
}

piece* smartpiece::operator->()
{
	return ptr;
}
