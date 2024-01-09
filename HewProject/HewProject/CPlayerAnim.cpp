#include "CPlayerAnim.h"

CPlayerAnim::CPlayerAnim()
{

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
		animCounter += animSpeed;

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
	nowUV.x = (animID % 3) * 0.33f;

	nowUV.y = (animID / 3) * 0.25f;
}

void CPlayerAnim::PlayWalk(int num)
{
	isPlaying = true;
	SetPattern(num);
	animCounter = 0;
}

void CPlayerAnim::StopWalk()
{
	isPlaying = false;
	animCounter = 2;
}

