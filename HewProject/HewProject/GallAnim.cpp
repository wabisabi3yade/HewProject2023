#include "GallAnim.h"

GallAnim::GallAnim()
{
	AnimSpeedRate = 1.5f;
	
}

GallAnim::~GallAnim()
{
}

void GallAnim::Update()
{
	int animTable[][32] = {

		{0,1,2,
		3, -1},//�ʏ�ҋ@���

		{0,1,2,
		3,4,5,
		6,-2},

		{3,4,5,6,-1}
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
			animPattern += 1;
			// �ŏ��̃R�}�ɖ߂��Ď~�߂�
			animCounter = 0.0f;
		}
	}

	// �\��������R�}ID���擾
	int animID = animTable[animPattern][(int)animCounter];

	// �\��������UV���v�Z
	nowUV.x = (animID % 3) * (1.0f / 3);

	nowUV.y = (animID / 3) * 0.25f;

}

void GallAnim::PlayOpen(float _animSpeedRate)
{
	AnimSpeedRate = _animSpeedRate;
	SetPattern(static_cast<int>(GallAnim::PATTERN::OPEN));
}
