#pragma once
#include "Sprite.h"


struct Piece
{
	std::shared_ptr<MeridorGraphics::Sprite> sprite;
	int id;
	COORD position;
	bool white;
	bool moved = false;
	bool en_passant = false;
	float depth = 0.1f;

	Piece(int id, COORD position, bool white, std::shared_ptr< MeridorGraphics::Sprite> sprite);
	void Draw();
	void Update(int x, int y);
};

