#pragma once
#include "direct3d.h"

// �A�j���[�V�����@�\�̃N���X�i�L�����N�^�[�A�G���j

class CAnimation
{
public:
	// �񋓌^
	// �A�j���[�V�����p�^�[����
	enum PATTERTN
	{
		DOWN,
		RIGHT,
		LEFT,
		UP,
		FX_0_11,	// �G�t�F�N�g��0�`11�Ԗڂ̉摜�𗬂�
		PATTERN_NUM
	};

protected:
	// �A�j���[�V�����ϐ�
	FLOAT_XY uv = {};	// �A�j���[�V������UV�ړ��ʂ�ۑ�
	float animCounter = 0.0f;	// �A�j���e�[�u���̃J�E���^�[
	int animPattern = 0;	// �Đ�����A�j���[�V�����̃p�^�[��ID�����ϐ�
	
	
public:
	float animSpeed = 0.1f;	// �Đ����x
	bool isPlaying = false;	// �Đ������ǂ�����\���ϐ�
	bool isStop = false;    // �A�j���[�V������~

public:

	CAnimation();

	// �����o�[�֐�
	virtual void Update();

	//// �Đ����x��ݒ肷��
	//void SetAnimSpeed(float setspeed);

	// �Đ�����A�j���[�V������ύX����

	// �Z�b�^�[�֐�(u)
	FLOAT_XY GetUV() { return uv; }

	// �Z�b�^�[�֐�(animPattern)
	void SetPattern(int setpattern);	

	// �Q�b�^�[�E�Z�b�^�[
	int GetisFX() { return animPattern; }
	void SetisFX(int setPattern) { animPattern = setPattern; }

	//effect�p�Z�b�^�[
	virtual void SetEffectLoop(bool) { 0; }

};

