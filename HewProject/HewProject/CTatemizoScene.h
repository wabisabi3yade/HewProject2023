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

	// ���݂̌�����\���x�N�g���ϐ�
	Vector2 dir = { 0, 0 };

	// ���z���E�̒��̈ʒu���W
	Vector2 pos = { 0, 0 };

	// �g��k���������ϐ�
	Vector2 scale = { 1.0f, 1.0f };

	// ��]�p�x
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

