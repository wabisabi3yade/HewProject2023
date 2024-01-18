#pragma once

#include "CSceneManager.h"
#include "CScene.h"
#include "direct3d.h"
#include "Vector3.h"

class GameController;

class CTatemizoScene :
	public CScene
{

public:
	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CObject* charObj;

public:

	//���݂̌�����\���x�N�g���ϐ�
	Vector3 dir = { 0, 0, 0 };

	// �L�[����\�ȃL�����N�^�[���H
	bool isPlayer = true;

	//���z���E�̒��̈ʒu���W
	Vector3 pos = { 0, 0, 0 };

	//�g��k���������ϐ�
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	//��]�p�x
	float angle = 0.0f;

	CTatemizoScene();

	~CTatemizoScene();

	void Update() override;

	void LateUpdate() override;

	void Draw() override;

	GameController* x;


	void SetDir(Vector3 v)
	{
		dir = v;
	}
};

