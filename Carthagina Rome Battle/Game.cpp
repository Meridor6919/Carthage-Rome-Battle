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

Game::Game(DirectX::SpriteBatch * sprite_batch, ID3D11Device * device)
{
	LoadSprites(sprite_batch, device);
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
	sprite_batch->End();
}

void Game::Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time)
{
	
}
