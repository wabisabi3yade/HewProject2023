#pragma once
#include "CScene.h"
#include "Ccontroller.h"
#include "direct3d.h"
#include "Vector2.h"
#include "Vector3.h"

class CTatemizoScene :
	public CScene
{
	//現在の向きを表すベクトル変数
	Vector3 dir = { 0, 0, 0 };

	//移動速度
	float moveSpeed = 1.0f;

public:
	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CObject* charObj;

public:

	//仮想世界の中の位置座標
	Vector3 pos = { 0, 0, 0 };

	//拡大縮小率を持つ変数
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	//回転角度
	float angle = 0.0f;

	CTatemizoScene();

	~CTatemizoScene();

	void Update() override;

	void LateUpdate() override;

	void Draw() override;

	void SetMoveSpeed(float sp)
	{
		moveSpeed = sp;
	}

	void SetDir(Vector3 v)
	{
		dir = v;
	}

};

