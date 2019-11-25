#pragma once
#include "DirectXApplication.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "SpriteBatch.h"
#include <vector>
#include "Grid.h"

class Game
{
	
	bool draging = false;
	Piece* dragged_piece = nullptr;
	COORD dragged_piece_coords = { 0,0 };
	std::unique_ptr<Grid> grid;

	void DrawGrid(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time);


public:
	Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device *device);
	void DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time);
	void DrawSpriteBatch(DirectX::SpriteBatch *sprite_batch, float delta_time);
	void Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time);
};

