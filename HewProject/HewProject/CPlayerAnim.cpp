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

		// �ҋ@
		// ������
		{ 0, 0 ,1, 2, 2, 1, -1 },	//�@-1��������ŏ��ɖ߂�
		// ������
		{ 3, 3, 4, 5, 5, 4, -1 },
		// �E����
		{ 6, 6, 7, 8, 8, 7, -1 },
		// �����
		{ 9, 9, 10, 11, 11, 10, -1},

		// ����
		// ������
		{ 0, 0 ,1, 2, 2, 1, -1 },	//�@-1��������ŏ��ɖ߂�
		// ������
		{ 3, 3, 4, 5, 5, 4, -1 },
		// �E����
		{ 6, 6, 7, 8, 8, 7, -1 },
		// �����
		{ 9, 9, 10, 11, 11, 10, -1},

		// �ł��Ă������
		// ������
		{  0 ,1, 2, 1, -1 },	//�@-1��������ŏ��ɖ߂�
		// ������
		{  3, 4, 5, 4, -1 },
		// �E����
		{  6, 7, 8, 7, -1 },
		// �����
		{ 9, 10, 11, 10, -1},

		//��C�̓���
		// ������
		{0,1,2,-1},
		// ������
		{3,4,5,-1},
		// �E����
		{6,7,8,-1},
		// �����
		{9,10,11,-1},

		//�H�ׂ�
		//�E����
		{0,0,1,1,2,2,
		3,3,},
		//������
		{6,6,7,7,8,8,
		9,9,-1},

		//�p���`
		{ 0,0,1,1,2,2,
		 3,3,3,3,3,4,4,5,5,
		 6,6,6,7,7,7,7,-1},
		
		 //�o�E��
		{ 0,0,1,1,2,2,
		3,3,4,4,5,5,
		6,6,7,7,-1},
		//
		{0,0,1,2,
		3,4,5,
		6,7,-2},
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
		else if (animTable[animPattern][(int)animCounter] == -2)
		{
			// �Đ����~�߂�
			animCounter -= 1.0f;
			// �ŏ��̃R�}�ɖ߂��Ď~�߂�
			isPlaying = false;
		}
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
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;

	switch (num)
	{
		//�@��
		// �S���ʍs����
	case 0:
		SetPattern(static_cast<int>(PATTERN::WALK_DOWN));
		break;

		// ��
	case 1:
		SetPattern(static_cast<int>(PATTERN::WALK_LEFT));
		break;

		// �E
	case 2:
		SetPattern(static_cast<int>(PATTERN::WALK_RIGHT));
		break;

		// ��
	case 3:
		SetPattern(static_cast<int>(PATTERN::WALK_UP));
		break;
	}
}

void CPlayerAnim::StopWalk(int _num)
{
	isPlaying = true;
	AnimSpeedRate = 1.0f;
	switch (_num)
	{
	case 0:
		SetPattern(static_cast<int>(PATTERN::STAY_DOWN));
		break;
	case 1:
		SetPattern(static_cast<int>(PATTERN::STAY_LEFT));
		break;
	case 2:
		SetPattern(static_cast<int>(PATTERN::STAY_RIGHT));
		break;
	case 3:
		SetPattern(static_cast<int>(PATTERN::STAY_UP));
		break;
	default:
		break;
	}
	animCounter = 0.0f;
	//animPattern -= static_cast<int>(PATTERN::WALK_DOWN);
	if (animPattern < 0) animPattern = 0;
}

void CPlayerAnim::PlayFall(int _num, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_num)
	{
		//�@��
		// �S���ʍs����
	case 0:
		SetPattern(static_cast<int>(PATTERN::PANIC_DOWN));
		break;

		// ��
	case 1:
		SetPattern(static_cast<int>(PATTERN::PANIC_LEFT));
		break;

		// �E
	case 2:
		SetPattern(static_cast<int>(PATTERN::PANIC_RIGHT));
		break;

		// ��
	case 3:
		SetPattern(static_cast<int>(PATTERN::PANIC_UP));
		break;
	}
}

void CPlayerAnim::PlayCannon(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_dir)
	{
		//�@��
		// �S���ʍs����
	case 0:
		SetPattern(static_cast<int>(PATTERN::CANNON_DOWN));
		break;

		// ��
	case 1:
		SetPattern(static_cast<int>(PATTERN::CANNON_LEFT));
		break;

		// �E
	case 2:
		SetPattern(static_cast<int>(PATTERN::CANNON_RIGHT));
		break;

		// ��
	case 3:
		SetPattern(static_cast<int>(PATTERN::CANNON_UP));
		break;
	}
}

void CPlayerAnim::PlayEat(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_dir)
	{
		//�@��
		// �S���ʍs����
	case 0:
		// �E
	case 2:
		SetPattern(static_cast<int>(PATTERN::EAT_RIGHT));
		break;
		// ��
	case 1:
		// ��
	case 3:
		SetPattern(static_cast<int>(PATTERN::EAT_LEFT));
		break;
	}
}

void CPlayerAnim::PlayPunch(float _animSpeedRate, bool _isGall)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	if(!_isGall)
	SetPattern(static_cast<int>(PATTERN::PUNCH));
	else
	SetPattern(static_cast<int>(PATTERN::GALL_PUNCH));
}

void CPlayerAnim::PlayBaum(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_dir)
	{
		//�@��
		// �S���ʍs����
	case 0:
		// �E
	case 2:
		// ��
	case 1:
		// ��
	case 3:
		SetPattern(static_cast<int>(PATTERN::BAUM));
		break;
	}
}


