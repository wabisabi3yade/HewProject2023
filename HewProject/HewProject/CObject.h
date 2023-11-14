#pragma once

#include "direct3d.h"
#include "CCamera.h"
#include "CAnimation.h"
#include"Vector3.h"
#include "Transform.h"

#define PathLength 64

enum ObjectLayer
{
	FADE,
	EFECT,
	UI,
	PLAY_GROUND,
	BACK_GROUND,
};


class CObject
{
	// �J�����I�u�W�F�N�g
	CCamera* mCamera;

protected:
	// ���݂̌�����\���x�N�g���ϐ�(3�������W)
	Vector3 mDir = { 0, 0, 0 };

	int mLayer;

	// �ړ����x
	float mMoveSpeed = 0.0f;

	// �`��Ɏg�p���钸�_�o�b�t�@
	D3DBUFFER mVertexBuffer;

	// �`��Ɏg�p����e�N�X�`��
	D3DTEXTURE mTexture;

	// �A�j���[�V�����N���X
	CAnimation* mAnim = nullptr;

	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// �}�e���A���F

	// �A�N�e�B�u/��A�N�e�B�u�؂�ւ��ϐ�
	bool isActive = true;

public:

	Transform mTransform;

	//�ǂݍ��ރt�@�C���̃p�X�ۑ��p
	const wchar_t* TexPath[PathLength];
	//Vector3 mPos = { 0, 0, 0 };	// �ʒu���W

	//Vector3 mScale = { 1.0f,1.0f,1.0f };	// �g��k���������ϐ�

	//float mRotZ = 0.0f;	// ��]����p�x�����ϐ�

public:
	// �����o�[�֐�
	// �����������i�R���X�g���N�^�j
	CObject(D3DBUFFER vb, D3DTEXTURE tex);

	// �Q�[�����[�v���ƂɎ��s���鏈���������֐�
	virtual void Update();

	// Update�̂��Ƃɍs���֐�
	virtual void LateUpdate();

	// �Q�[�����[�v���Ƃɕ`�悷�鏈���������֐�
	virtual void Draw();

	//�Q�b�^�[
	
	// �������擾
	Vector3 GetDir() { return mDir; }

	int GetLayer() { return mLayer; }


	//�Z�b�^�[	

	//������ݒ�
	void SetDir(Vector3 setdir);

	void SetTexture(D3DTEXTURE _tex) { mTexture = _tex; }

	void SetTransformScale(Vector3 _v) { mTransform.scale = _v; }

	void SetTransformScale(float _x, float _y, float _z) {
		mTransform.scale.x = _x, mTransform.scale.y = _y, mTransform.scale.z = _z;
	}

	void SetMoveSpeed(float _moveSpeed) { mMoveSpeed = _moveSpeed; }

	void SetLayer(ObjectLayer _layer) { mLayer = _layer; }
};

