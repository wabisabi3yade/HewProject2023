#pragma once
#include "CScene.h"
#include "Ccontroller.h"
#include "direct3d.h"
#include "Vector2.h"
#include "Vector3.h"

class CTatemizoScene :
	public CScene
{
	//���݂̌�����\���x�N�g���ϐ�
	Vector3 dir = { 0, 0, 0 };

	//�ړ����x
	float moveSpeed = 1.0f;

public:
	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CObject* charObj;

public:

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

	void SetMoveSpeed(float sp)
	{
		moveSpeed = sp;
	}

	void SetDir(Vector3 v)
	{
		dir = v;
	}

};

