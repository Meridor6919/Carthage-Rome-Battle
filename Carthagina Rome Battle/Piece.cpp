#include "Piece.h"



Piece::Piece(int id, COORD position, bool white, std::shared_ptr<MeridorGraphics::Sprite> sprite)
{
	this->id = id;
	this->position = position;
	this->white = white;
	this->sprite = sprite;
}

void Piece::Draw()
{
	sprite->SetX(240 + 90 * position.X);
	sprite->SetY(40 + 90 * position.Y);
	sprite->Draw();
}

void Piece::Update(int x, int y)
{
	position = { static_cast<short>(x),static_cast<short>(y) };
}
