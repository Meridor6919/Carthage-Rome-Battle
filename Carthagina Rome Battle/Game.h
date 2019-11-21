#pragma once
#include "DirectXApplication.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "SpriteBatch.h"
#include <vector>
#include "Piece.h"

class Game
{
	
	std::vector<std::shared_ptr<MeridorGraphics::Sprite>> sprites;
	std::vector<Piece> Pieces;

	void LoadSprites(DirectX::SpriteBatch * sprite_batch, ID3D11Device* device);
	void LoadPieces();

public:
	Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device *device);
	void DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time);
	void DrawSpriteBatch(DirectX::SpriteBatch *sprite_batch, float delta_time);
	void Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time);
};

