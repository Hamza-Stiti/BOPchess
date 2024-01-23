#pragma once
#include "piece.h"

class smartpiece
{
private:
	piece* ptr;
public:
	smartpiece() : ptr(nullptr) {};
	smartpiece(piece* p_ptr) : ptr(p_ptr) {};
	smartpiece(smartpiece& other);
	smartpiece(std::array<texture*, 12>& images, pieces_code code, position pos);

	~smartpiece();


	void copying(smartpiece& other);

	inline bool nonempty() { return ptr != nullptr; }

	inline piece* getptr() { return ptr; }

	void destroy();

	smartpiece& operator=(smartpiece&& other) noexcept;



	piece& operator*();
	piece* operator->();
};