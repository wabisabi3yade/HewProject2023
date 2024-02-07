#include "CannonAnim.h"

CannonAnim::CannonAnim()
{
	animPattern = static_cast<int>(PATTERN::IDLE);
	AnimSpeedRate = 1.0f;
}

CannonAnim::~CannonAnim()
{
}

void CannonAnim::Update()
{
	int animTable[][32] = {

		{0,-1},//������ҋ@���


		{0,0,1,1,2,2,-2},//��]�A�㉺���獶�E������

		{2,2,3,3,4,4,5,5,-2},//��������

		{2,2,6,6,7,7,8,8,-2},//�E������

		{0,0,3,3,4,4,5,5,-2},//��������

		{0,0,6,6,7,7,8,8,-2},//�������

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
			//isPlaying = false;
			//animPattern -= 1;
			// �ŏ��̃R�}�ɖ߂��Ď~�߂�
			animCounter -= 1.0f;
		}
	}

	// �\��������R�}ID���擾
	int animID = animTable[animPattern][(int)animCounter];

	// �\��������UV���v�Z
	nowUV.x = (animID % 3) * (1.0f / 3);

	nowUV.y = (animID / 3) * 0.25f;
}

void CannonAnim::PlayTurn(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;

	SetPattern(static_cast<int>(CannonAnim::PATTERN::TURN));
}

void CannonAnim::PlayStart(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_dir)
	{
	case 0:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::D_DIR));
		break;
	case 1:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::L_DIR));
		break;
	case 2:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::R_DIR));
		break;
	case 3:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::U_DIR));
		break;
	default:
		break;
	}
}