#pragma once

#include "direct3d.h"
#include"Vector3.h"
#include"Transform.h"

// �Q�[���̃J�����̃N���X
// �J�����̓v���C���[��Ǐ]���Ă���
class CCamera
{

	Transform mTransform;

	CCamera();

	~CCamera();

	static CCamera* instance;

public:
	static float scaleScreen;	// �摜�̑傫���i�l���������Ȃ�قǉ摜�͑傫���Ȃ�j
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
		mTransform.pos.x = set.x;
		mTransform.pos.y = set.y;
	}

	// �J�����̍��W���擾
	//DirectX::XMFLOAT3 GetPos() { return pos; }
	Vector3 GetPos() { return mTransform.pos; }

	// �J�����̉�]�p�x�iZ���j���擾
	float GetRotZ() { return mTransform.rotation.z; }
};