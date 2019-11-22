#include "Grid.h"



Grid::Grid(DirectX::SpriteBatch* sprite_batch, ID3D11Device *device)
{
	for (int i = 0; i < 64; ++i)
	{
		Pieces.push_back(Piece(10, { 0,0 }, 0, nullptr));
	}
	LoadSprites(sprite_batch, device);
	LoadPieces();
}

COORD Grid::GetPosition(double x, double y)
{
	short pos_x = static_cast<short>((x - 240.0) / 90.0);
	short pos_y = (y - 40) / 90;
	if (x < 240 || x>1160 || y < 40 || y > 760)
	{
		return { 0,0 };
	}
	return { pos_x+1, pos_y+1 };
}
COORD Grid::GetCoords(short x, short y)
{
	short coord_x = 150 + 90 * x;
	short coord_y = -50 + 90 * y;
	return { coord_x, coord_y };
}
void Grid::DrawPieces()
{
	for (int i = 0; i < static_cast<int>(Pieces.size()); ++i)
	{
		if (Pieces[i].id != 10)
			Pieces[i].Draw();
	}
}
void Grid::LoadPieces()
{
	//pawns
	for (int x = 0; x < 16; ++x)
	{
		COORD pos = { 1 + x%8, 2 + 5 * (x > 7) };
		Pieces[(pos.Y-1)*8 + pos.X - 1] = (Piece(5, GetCoords(pos.X, pos.Y), x > 7, sprites[5 + 6 * (x / 8)]));
	}
	//pieces
	for (int i = 0; i < 3; ++i)
	{
		for (int x = 0; x < 4; ++x)
		{
			COORD pos = { 1 + i + x/2*(7-i*2),1 + 7 * (x % 2) };
			Pieces[(pos.Y - 1) * 8 + pos.X - 1] = (Piece(0, GetCoords( pos.X, pos.Y ), x % 2, sprites[i + 6 * (x % 2)]));
		}
	}
	//queen and king
	for (int i = 0; i < 2; ++i)
	{
		for (int x = 0; x < 2; ++x)
		{
			COORD pos = { i + 4 ,1 + 7 * (x % 2) };
			Pieces[(pos.Y - 1) * 8 + pos.X - 1] = (Piece(0, GetCoords(pos.X, pos.Y), x % 2, sprites[3 + i % 2 + 6 * (x % 2)]));
		}
	}
}
void Grid::LoadSprites(DirectX::SpriteBatch * sprite_batch, ID3D11Device* device)
{
	float width = 56;
	float height = 60;
	for (int x = 0; x < 12; ++x)
	{
		RECT rect = { static_cast<short>(width) * (x % 6),x / 6 * height,static_cast<short>(width) + (static_cast<short>(width) * (x % 6)), x / 6 * height + height };
		sprites.push_back(std::make_shared<MeridorGraphics::Sprite>(sprite_batch, rect, 0, 0, 90, 90));
		sprites[x]->AddTexture(L"Graphics\\figures.png", device);
	}
}
