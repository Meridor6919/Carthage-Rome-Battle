#pragma once
#include "Sprite.h"


class Piece
{
	std::shared_ptr<MeridorGraphics::Sprite> sprite;
	int id;
	COORD position;
	bool white;
	bool moved = false;

public:
	Piece(int id, COORD position, bool white, std::shared_ptr< MeridorGraphics::Sprite> sprite);
	void Draw();
	void Update(int x, int y);
};

