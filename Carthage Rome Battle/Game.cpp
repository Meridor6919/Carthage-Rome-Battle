#include "Game.h"

Game::Game(DirectX::SpriteBatch * sprite_batch, ID3D11Device * device)
{
	grid = std::make_unique<Grid>(sprite_batch, device);
}
void Game::DrawGrid(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitive_batch, float delta_time)
{
	DirectX::XMFLOAT4 colors[2] = { { 0.5529, 0.7529, 0.5529, 1 }, { 0.7, 0.9215, 0.8039, 1 } };
	bool current_color = false;

	DirectX::XMFLOAT3 v1(240, 40, 1.0f);
	DirectX::XMFLOAT3 v2(240 + 90, 40, 1.0f);
	DirectX::XMFLOAT3 v3(240 + 90, 40 + 90, 1.0f);
	DirectX::XMFLOAT3 v4(240, 40 + 90, 1.0f);
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
	for (int i = 0; i < 12; ++i)
	{
		v1.x = 75 + 960 * (i / 6);
		v1.y = 75 + 110 * (i % 6);
		v2 = v1;
		v2.x += 90;
		v3 = v2;
		v3.y += 90;
		v4 = v1;
		v4.y += 90;

		primitive_batch->DrawQuad(DirectX::VertexPositionColor(XMLoadFloat3(&v1), XMLoadFloat4(&colors[current_color])),
			DirectX::VertexPositionColor(XMLoadFloat3(&v2), XMLoadFloat4(&colors[current_color])),
			DirectX::VertexPositionColor(XMLoadFloat3(&v3), XMLoadFloat4(&colors[current_color])),
			DirectX::VertexPositionColor(XMLoadFloat3(&v4), XMLoadFloat4(&colors[current_color])));
	}
}
void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitive_batch, float delta_time)
{
	primitive_batch->Begin();
	DrawGrid(primitive_batch, delta_time);
	primitive_batch->End();
}
void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	sprite_batch->Begin(DirectX::SpriteSortMode_FrontToBack);
	if (buffer_piece != nullptr)
	{
		buffer_piece->Draw();
	}
	grid->DrawPieces();
	sprite_batch->End();
}
void Game::Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time)
{

	if (button_tracker->leftButton == 3 && !draging)
	{
		COORD pos = grid->GetPosition(mouse->GetState().x, mouse->GetState().y);
		if (pos.X * pos.Y)
		{
			if (grid->Pieces[(pos.Y - 1) * 8 + pos.X - 1].id != 10)
			{
				draging = true;
				dragged_piece = &grid->Pieces[(pos.Y - 1) * 8 + pos.X - 1];
				dragged_piece->depth = 0.2f;
				dragged_piece_coords = pos;
			}
		}
		else
		{
			COORD coord = { mouse->GetState().x, mouse->GetState().y };
			int temp = 100;
			for (int i = 0; i < 12; ++i)
			{
				if (coord.Y > 75 + 110 * (i % 6) && coord.Y < 165 + 110 * (i % 6) && coord.X > 75 + 960 * (i / 6) && coord.X < 165 + 960 * (i / 6))
				{
					temp = i;
				}
			}
			if (temp != 100)
			{
				draging = true;
				buffer_piece = std::make_unique<Piece>(temp / 6, coord, temp / 6, grid->sprites[temp]);
				dragged_piece = buffer_piece.get();
				dragged_piece->depth = 0.2f;
				dragged_piece_coords = coord;
			}
		}
	}
	else if (draging && button_tracker->leftButton == 2)
	{
		COORD pos;

		COORD grid_pos = grid->GetPosition(mouse->GetState().x, mouse->GetState().y);
		if (grid_pos.X*grid_pos.Y)
		{
			if (grid->Pieces[(grid_pos.Y - 1) * 8 + grid_pos.X - 1].white != dragged_piece->white || grid->Pieces[(grid_pos.Y - 1) * 8 + grid_pos.X - 1].id == 10)
			{
				grid->Pieces[(grid_pos.Y - 1) * 8 + grid_pos.X - 1] = *dragged_piece;
				dragged_piece = &grid->Pieces[(grid_pos.Y - 1) * 8 + grid_pos.X - 1];
				if (buffer_piece == nullptr)
				{
					grid->Pieces[(dragged_piece_coords.Y - 1) * 8 + dragged_piece_coords.X - 1] = Piece(10, { 0,0 }, 0, nullptr);
				}
				else
				{
					buffer_piece = nullptr;
				}
				pos = grid->GetCoords(grid_pos.X, grid_pos.Y);
			}
			else
			{
				pos = grid->GetCoords(dragged_piece_coords.X, dragged_piece_coords.Y);
			}
		}
		else
		{
			pos = grid->GetCoords(dragged_piece_coords.X, dragged_piece_coords.Y);
		}

		dragged_piece->position.X = static_cast<short>(pos.X);
		dragged_piece->position.Y = static_cast<short>(pos.Y);
		dragged_piece->depth = 0.1f;

		draging = false;
		dragged_piece = nullptr;
	}
	else if (draging)
	{
		dragged_piece->position.X = static_cast<short>(mouse->GetState().x - 45);
		dragged_piece->position.Y = static_cast<short>(mouse->GetState().y - 45);
	}
}
