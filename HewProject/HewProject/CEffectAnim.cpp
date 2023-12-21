#include "CEffectAnim.h"

CEffectAnim::CEffectAnim()
{
	
}

void CEffectAnim::Update()
{
	// 2D�Q�[���ł������߂̃A�j���[�V�������@
	// �e�[�u���A�j���[�V�����E�E�E���߂�ꂽ���ԂōĐ������邽�߂̃f�[�^
	// ���e�[�u���E�E�E�Ȃɂ��̖ړI�̂��߂ɍ��ꂽ�f�[�^�̏W�܂�
	// �񎟌��z��̂Ƃ��͌��̓Y�����͎w�肵�Ȃ����Ⴂ���Ȃ��i���ꂮ�炢����΂������낤���炢�̐������邵���Ȃ��j
	int animTable[][32] = {
		// ������
		{0,1,2,3,4,5,6,7,8,9,10,11,-1},//�@-1��������ŏ��ɖ߂�
	};

	// �Đ����Ȃ�
	if (isPlaying)
	{
		// �A�j���[�V�����̃J�E���^�[��i�߂�
		animCounter += animSpeed;

		// -1��������ŏ��ɖ߂�i���[�v�Đ��j
		if (animTable[animPattern][(int)animCounter] == -1)
		{
			animCounter = 0.0f;
			if (isCheck == false)
			{
				// �Đ����~�߂�
				isPlaying = false;
			}
		}
	}

	// �\��������R�}ID���擾
	int animID = animTable[animPattern][(int)animCounter];

	// �\��������UV���v�Z
	uv.x = (animID % 3) * 0.33f;

	uv.y = (animID / 3) * 0.25f;
}

void CEffectAnim::SetEffectLoop(bool isLoop)
{
	isCheck = isLoop;
}

CEffectAnim::~CEffectAnim()
{
}
