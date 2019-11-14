#include "Game.h"

Game::Game(DirectX::SpriteBatch * sprite_batch, ID3D11Device * device)
{
	moving = std::make_shared<PlaceholderMove>(sprite_batch, device);
	staying = std::make_shared<PlaceholderStay>(sprite_batch, device);
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitive_batch, float delta_time)
{
}

void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	sprite_batch->Begin();
	staying->Draw(200,100, 50,50,1,DirectX::SpriteEffects::SpriteEffects_None);
	sprite_batch->End();
}

void Game::Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time)
{
}
