#include "FloorUI.h"
#include "TextureFactory.h"

#define F_OFFSETX (0.5f)	// F�̂��炷X���W
#define F_OFFSETZ (0.0001f)	// F�̂��炷Z���W

#define HIGHLIGHT_OFFSET_X	(0.4f)	// �n�C���C�g�̂Ƃ��ɒ��S���W���炸���X���W

#define FLOOR_UI_OFFSETY (1.0f)	// �K�w���Ƃ̂��炷Y���W

FloorUI::FloorUI(const int& _startFloorNum, const int& _maxNum)
{
	mTransform.pos = {7.0f, -2.0f, 0.0f};

	// ���̊K�w�ɕK�v�ȊK�wUI�̐�
	stageFloorNum = _maxNum;

	// �n�C���C�g�����K�w
	nowHilghtFloor = _startFloorNum;

	D3D_CreateSquare({ 4,2 }, &buffer);
	D3DTEXTURE texWork;
	texWork = TextureFactory::GetInstance()->Fetch(L"asset/UI/Floor_Num.png");

	// UI�쐬
	for (int i = 0; i < stageFloorNum; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			floor[i][j] = new UI(buffer, texWork);
		}

		// �D�F�̐������o���Ă���
		floor[i][0]->SetUV(i * (1.0f / 4), 0.0f);	// ����
		floor[i][1]->SetUV(3 * (1.0f / 4), 0.0f);	// F
	}

	SetPosition();
	SetHighlight(_startFloorNum);
}

FloorUI::~FloorUI()
{
	SAFE_RELEASE(buffer);

	// UI�쐬
	for (int i = 0; i < stageFloorNum; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			CLASS_DELETE(floor[i][j]);
		}
	}
}

void FloorUI::Draw()
{
	for (int i = 0; i < stageFloorNum; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			floor[i][j]->Draw();
		}
	}
}

void FloorUI::SetHighlight(int _set)
{
	// 1�����@�ő�K�w�ȏ�Ȃ�
	if (_set > stageFloorNum)
	{
		_set = stageFloorNum;
	}
	else if (_set < 1)
	{
		_set = 1;
	}
	// �X�V
	nowHilghtFloor = _set;

	for (int i = 0; i < stageFloorNum; i++)
	{
		// V���W�𒲐�����悤�ϐ�
		short t = 0;
		// �ݒ肵�����K�w��������
		if (i == _set - 1)
		{
			// ���点��悤�ɂ���
			t = 1;
		}

		// UV���W�𒲐�
		floor[i][0]->SetUV(i * (1.0f / 4), t * (1.0f / 2));	// ��
		floor[i][1]->SetUV(3 * (1.0f / 4), t * (1.0f / 2));	// F
	}

	SetPosition();
}

void FloorUI::SetPosition()
{
	// �K�w���Ƃ�UI���W�ݒ�
	for (int i = 0; i < stageFloorNum; i++)
	{
		float ypos = mTransform.pos.y + i * FLOOR_UI_OFFSETY;

		floor[i][0]->mTransform.pos = mTransform.pos;
		floor[i][0]->mTransform.pos.y = ypos;
		floor[i][0]->mTransform.scale = grayScale;


		floor[i][1]->mTransform.pos = mTransform.pos;
		floor[i][1]->mTransform.pos.x += F_OFFSETX;
		floor[i][1]->mTransform.pos.y = ypos;
		floor[i][1]->mTransform.pos.z -= F_OFFSETZ;
		floor[i][1]->mTransform.scale = grayScale;
	}

	floor[nowHilghtFloor - 1][0]->mTransform.pos.x = mTransform.pos.x - HIGHLIGHT_OFFSET_X;
	floor[nowHilghtFloor - 1][0]->mTransform.scale = highlightScale;
	floor[nowHilghtFloor - 1][1]->mTransform.pos.x = mTransform.pos.x + HIGHLIGHT_OFFSET_X;
	floor[nowHilghtFloor - 1][1]->mTransform.scale = highlightScale;
}
