#pragma once

#include "CSceneManager.h"
#include "CScene.h"
#include "direct3d.h"
#include "Vector2.h"

class GameController;

class CTatemizoScene :
	public CScene
{

public:
	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CObject* charObj;

public:

	// 現在の向きを表すベクトル変数
	Vector2 dir = { 0, 0 };

	// 仮想世界の中の位置座標
	Vector2 pos = { 0, 0 };

	// 拡大縮小率を持つ変数
	Vector2 scale = { 1.0f, 1.0f };

	// 回転角度
	float angle = 0.0f;

	CTatemizoScene();

	~CTatemizoScene();

	void Update() override;

	void LateUpdate() override;

	void Draw() override;

	void ButtonState();

	GameController* val;
	GameController* button;


	void SetDir(Vector2 v)
	{
		dir = v;
	}
};

