#include "CPlayerAnim.h"

CPlayerAnim::CPlayerAnim()
{
	AnimSpeedRate = 1.0f;
	Now_IsFall = false;
	Old_IsFall = false;
}

CPlayerAnim::~CPlayerAnim()
{

}

void CPlayerAnim::Update()
{
	int animTable[][32] = {
		// ������
		{ 0, 0 ,1, 2, 2, 1, -1 },	//�@-1��������ŏ��ɖ߂�
		// ������
		{ 3, 3, 4, 5, 5, 4, -1 },
		// �E����
		{ 6, 6, 7, 8, 8, 7, -1 },
		// �����
		{ 9, 9, 10, 11, 11, 10, -1},

	};


	// �Đ����Ȃ�
	if (isPlaying)
	{
		// �A�j���[�V�����̃J�E���^�[��i�߂�
		animCounter += animSpeed * AnimSpeedRate;

		// -1��������ŏ��ɖ߂�i���[�v�Đ��j
		if (animTable[animPattern][(int)animCounter] == -1)
		{
			animCounter = 0.0f;
		}
		// -2���������~�����鏈��
		//else if (animTable[animPattern][(int)animCounter] == -2)
		//{
		//	// �Đ����~�߂�
		//	isPlaying = false;
		//	// �ŏ��̃R�}�ɖ߂��Ď~�߂�
		//	animCounter = 0.0f;
		//}
	}

	// �\��������R�}ID���擾
	int animID = animTable[animPattern][(int)animCounter];

	// �\��������UV���v�Z
	nowUV.x = (animID % 3) * (1.0f / 3);

	nowUV.y = (animID / 3) * 0.25f;

	Old_IsFall = Now_IsFall;

}

void CPlayerAnim::PlayWalk(int num, float _animSpeedRate)
{
	isPlaying = true;
	SetPattern(num);
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
}

void CPlayerAnim::StopWalk()
{
	isPlaying = false;
	animCounter = 2;
}

void CPlayerAnim::PlayFall(int _num, float _animSpeedRate)
{
	isPlaying = true;
	SetPattern(_num);
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
}


