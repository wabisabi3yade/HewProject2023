#include "CEffectAnim.h"

CEffectAnim::CEffectAnim()
{
	AnimEnd = false;
}

void CEffectAnim::Update()
{
	// 2D�Q�[���ł������߂̃A�j���[�V�������@
	// �e�[�u���A�j���[�V�����E�E�E���߂�ꂽ���ԂōĐ������邽�߂̃f�[�^
	// ���e�[�u���E�E�E�Ȃɂ��̖ړI�̂��߂ɍ��ꂽ�f�[�^�̏W�܂�
	// �񎟌��z��̂Ƃ��͌��̓Y�����͎w�肵�Ȃ����Ⴂ���Ȃ��i���ꂮ�炢����΂������낤���炢�̐������邵���Ȃ��j
	int animTable[][64] = {
		// ������
		{0,1,2,3,4,5,6,7,8,9,10,11,-1},//�@-1��������ŏ��ɖ߂�

		{ 0, 1, 2, 3, 4, 5,
		  6, 7, 8, 9, 10, 11,
		  12, 13, 14, 15, 16, 17,
		  18, 19, 20, 21, 22, 23,
		  24, 25, 26, 27, 28, 29,
		  30, 31,-2,
		},
		{  19, 20, 21, 22, 23,
		  24, 25, 26, 27, 28, 29,
		  30, 31,-1}
	};

	// �Đ����Ȃ�
	if (isPlaying)
	{
		AnimEnd = false;
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
				AnimEnd = true;
			}
		}
		else if (animTable[animPattern][(int)animCounter] == -2)
		{
			animCounter = 0.0f;
			animPattern = 2;
		}

	}

	// �\��������R�}ID���擾
	int animID = animTable[animPattern][(int)animCounter];

	if (animPattern == 0)
	{
		// �\��������UV���v�Z
		nowUV.x = (animID % 3) * (1.0f / 3.0f);

		nowUV.y = (animID / 3) * (1.0f / 4.0f);
	}
	else if (animPattern == 1 || animPattern == 2)
	{
		nowUV.x = (animID % 6) * (1.0f / 6.0f);

		nowUV.y = (animID / 6) * (1.0f / 7.0f);
	}
}

void CEffectAnim::SetEffectLoop(bool isLoop)
{
	isCheck = isLoop;
}

CEffectAnim::~CEffectAnim()
{
}
