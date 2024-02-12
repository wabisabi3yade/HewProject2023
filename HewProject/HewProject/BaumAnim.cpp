#include "BaumAnim.h"

BaumAnim::BaumAnim()
{
	animRate = 1.0f;
	AnimEnd = false;
}

BaumAnim::~BaumAnim()
{
}

void BaumAnim::Update()
{
	int animTable[][32] = {

		{0,0,1,1,2,2,
		 3,3,4,4,5,5,
		 6,6,7,7,-2},
	};

	// �Đ����Ȃ�
	if (isPlaying)
	{
		// �A�j���[�V�����̃J�E���^�[��i�߂�
		animCounter += animSpeed * animRate;
		AnimEnd = false;
		// -1��������ŏ��ɖ߂�i���[�v�Đ��j
		if (animTable[animPattern][(int)animCounter] == -1)
		{
			animCounter = 0.0f;
		}
		// -2���������~�����鏈��
		else if (animTable[animPattern][(int)animCounter] == -2)
		{
			// �Đ����~�߂�
			isPlaying = false;
			animCounter = 0.0f;
			//animPattern -= 1;
			// �ŏ��̃R�}�ɖ߂��Ď~�߂�
			//animCounter -= 1.0f;
			AnimEnd = true;
		}
	}

	// �\��������R�}ID���擾
	int animID = animTable[animPattern][(int)animCounter];

	// �\��������UV���v�Z
	nowUV.x = (animID % 3) * (1.0f / 3);

	nowUV.y = (animID / 3) * 0.25f;

}

void BaumAnim::PlayAnim(int _dir, float _animRate)
{
	isPlaying = true;
	animCounter = 0;
	animRate = _animRate;
	switch (_dir)
	{
	case 0:
		SetPattern(static_cast<int>(BaumAnim::PATTERN::BAUM_DOWN));
		break;
	case 1:
		SetPattern(static_cast<int>(BaumAnim::PATTERN::BAUM_LEFT));
		break;
	case 2:
		SetPattern(static_cast<int>(BaumAnim::PATTERN::BAUM_RIGHT));
		break;
	case 3:
		SetPattern(static_cast<int>(BaumAnim::PATTERN::BAUM_UP));
		break;
	default:
		break;
	}
}
