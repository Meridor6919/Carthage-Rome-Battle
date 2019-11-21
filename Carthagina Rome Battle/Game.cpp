#include "Game.h"

void Game::LoadSprites(DirectX::SpriteBatch * sprite_batch, ID3D11Device* device)
{
	float width = 56;
	float height = 60;
	for (int x = 0; x < 12; ++x)
	{
		RECT rect = { static_cast<short>(width) * (x%6),x/6*height,static_cast<short>(width) + (static_cast<short>(width) * (x % 6)), x / 6 * height+height };
		sprites.push_back(std::make_shared<MeridorGraphics::Sprite>(sprite_batch,  rect, 0, 0, 90, 90));
		sprites[x]->AddTexture(L"Graphics\\figures.png", device);
	}
}

void Game::LoadPieces()
{
	//pawns
	for (int x = 0; x < 16; ++x)
	{
		COORD pos = { 240 + x % 8 * 90, 130+450*(x/8) };
		Pieces.push_back(Piece(5, pos, x / 8, sprites[5 + 6 * (x / 8)]));
	}
	//pieces
	for (int i = 0; i < 3; ++i)
	{
		for (int x = 0; x < 4; ++x)
		{
			COORD pos = { 240+(i*90) + (630-2*i*90) * (x / 2), 40 + 630 * (x % 2) };
			Pieces.push_back(Piece(0, pos, x % 2, sprites[i + 6 * (x % 2)]));
		}
	}
	//queen and king
	for (int i = 0; i < 2; ++i)
	{
		for (int x = 0; x < 2; ++x)
		{
			COORD pos = { 510 + i * 90, 40 + 630 * (x % 2) };
			Pieces.push_back(Piece(0, pos, x % 2, sprites[3+i%2 + 6*(x%2)]));
		}
	}
}

Game::Game(DirectX::SpriteBatch * sprite_batch, ID3D11Device * device)
{
	LoadSprites(sprite_batch, device);
	LoadPieces();
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitive_batch, float delta_time)
{
	DirectX::XMFLOAT4 colors[2] = { { 0.5529, 0.7529, 0.5529, 1 }, { 0.7, 0.9215, 0.8039, 1 } };
	bool current_color = false;

	DirectX::XMFLOAT3 v1(240, 40, 1.0f);
	DirectX::XMFLOAT3 v2(240 + 90, 40, 1.0f);
	DirectX::XMFLOAT3 v3(240 + 90, 40 + 90, 1.0f);
	DirectX::XMFLOAT3 v4(240, 40 + 90, 1.0f);

	primitive_batch->Begin();
	for (int i = 0; i < 8; i++)
	{
		v1.x = 240;
		v2.x = 240 + 90;
		v3.x = 240 + 90;
		v4.x = 240;
		for (int j = 0; j < 8; j++)
		{
			current_color = !current_color;
			primitive_batch->DrawQuad(DirectX::VertexPositionColor(XMLoadFloat3(&v1), XMLoadFloat4(&colors[current_color])),
				DirectX::VertexPositionColor(XMLoadFloat3(&v2), XMLoadFloat4(&colors[current_color])),
				DirectX::VertexPositionColor(XMLoadFloat3(&v3), XMLoadFloat4(&colors[current_color])),
				DirectX::VertexPositionColor(XMLoadFloat3(&v4), XMLoadFloat4(&colors[current_color])));
			v1.x += 90;
			v2.x += 90;
			v3.x += 90;
			v4.x += 90;
		}
		v1.y += 90;
		v2.y += 90;
		v3.y += 90;
		v4.y += 90;
		current_color = !current_color;
	}
	primitive_batch->End();
}

void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	sprite_batch->Begin();
	for (int i = 0; i < static_cast<int>(Pieces.size()); ++i)
	{
		Pieces[i].Draw();
	}

	sprite_batch->End();
}

void Game::Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time)
{
	
}
