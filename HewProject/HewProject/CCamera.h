#pragma once

#include "direct3d.h"

// �Q�[���̃J�����̃N���X
// �J�����̓v���C���[��Ǐ]���Ă���
class CCamera
{
	Vector3 pos = {};	// ���W

	float rotZ = 0.0f;	// ��]�p�x

	CCamera();

	~CCamera();

	static CCamera* instance;

public:
	// �C���X�^���X�����擾
	// ���߂ČĂяo���ꂽ��C���X�^���X�𐶐�
	static CCamera* GetInstance();

	// �C���X�^���X���폜
	static void Delete();

	// ����������֐�
	void Init();

	// �J�����̏���
	void Update();

	// �Q�b�^�[�E�Z�b�^�[�֐�
	// ���W
	void SetPos(FLOAT_XY set)
	{
		pos.x = set.x;
		pos.y = set.y;
	}

	// �J�����̍��W���擾
	DirectX::XMFLOAT3 GetPos() { return pos; }

	// �J�����̉�]�p�x�iZ���j���擾
	float GetRotZ() { return rotZ; }
};