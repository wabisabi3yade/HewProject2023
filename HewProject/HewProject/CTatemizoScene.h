#pragma once

#include <Windows.h>
#include <Xinput.h>
#include "CSceneManager.h"
#include "CScene.h"
//#include "direct3d.h"
#include "Vector3.h"

//#include "COperation.h"

class CTatemizoScene :
	public CScene
{
	////���݂̌�����\���x�N�g���ϐ�
	//Vector3 dir = { 0, 0, 0 };

	////�ړ����x
	//float moveSpeed = 1.0f;

public:
	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CObject* charObj;

public:
	//// �L�[����\�ȃL�����N�^�[���H
	//bool isPlayer = false;

	////���z���E�̒��̈ʒu���W
	//Vector3 pos = { 0, 0, 0 };

	////�g��k���������ϐ�
	//Vector3 scale = { 1.0f, 1.0f, 1.0f };

	////��]�p�x
	//float angle = 0.0f;

	CTatemizoScene();

	~CTatemizoScene();

	void Update() override;

	void LateUpdate() override;

	void Draw() override;

	//void SetMoveSpeed(float sp)
	//{
	//	moveSpeed = sp;
	//}

	//void SetDir(Vector3 v)
	//{
	//	dir = v;
	//}

//private:
//	XINPUT_STATE m_controllerState;
};

