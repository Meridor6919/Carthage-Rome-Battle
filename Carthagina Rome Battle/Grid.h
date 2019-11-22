#pragma once
#include "Piece.h"


struct Grid
{
	std::vector<Piece> Pieces;
	std::vector<std::shared_ptr<MeridorGraphics::Sprite>> sprites;



	Grid(DirectX::SpriteBatch* sprite_batch, ID3D11Device *device);
	COORD GetPosition(double x, double y);
	COORD GetCoords(short x, short y);
	void DrawPieces();
	void LoadPieces();
	void LoadSprites(DirectX::SpriteBatch * sprite_batch, ID3D11Device* device);
};

