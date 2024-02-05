#include "FloorUI.h"
#include "TextureFactory.h"

#define F_OFFSETX (0.5f)	// FのずらすX座標
#define F_OFFSETZ (0.0001f)	// FのずらすZ座標

#define HIGHLIGHT_OFFSET_X	(0.4f)	// ハイライトのときに中心座標からずれるX座標

#define FLOOR_UI_OFFSETY (1.0f)	// 階層ごとのずらすY座標

FloorUI::FloorUI(const int& _startFloorNum, const int& _maxNum)
{
	mTransform.pos = {7.0f, -2.0f, 0.0f};

	// この階層に必要な階層UIの数
	stageFloorNum = _maxNum;

	// ハイライトされる階層
	nowHilghtFloor = _startFloorNum;

	D3D_CreateSquare({ 4,2 }, &buffer);
	D3DTEXTURE texWork;
	texWork = TextureFactory::GetInstance()->Fetch(L"asset/UI/Floor_Num.png");

	// UI作成
	for (int i = 0; i < stageFloorNum; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			floor[i][j] = new UI(buffer, texWork);
		}

		// 灰色の数字を出しておく
		floor[i][0]->SetUV(i * (1.0f / 4), 0.0f);	// 数字
		floor[i][1]->SetUV(3 * (1.0f / 4), 0.0f);	// F
	}

	SetPosition();
	SetHighlight(_startFloorNum);
}

FloorUI::~FloorUI()
{
	SAFE_RELEASE(buffer);

	// UI作成
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
	// 1未満　最大階層以上なら
	if (_set > stageFloorNum)
	{
		_set = stageFloorNum;
	}
	else if (_set < 1)
	{
		_set = 1;
	}
	// 更新
	nowHilghtFloor = _set;

	for (int i = 0; i < stageFloorNum; i++)
	{
		// V座標を調整するよう変数
		short t = 0;
		// 設定したい階層が来たら
		if (i == _set - 1)
		{
			// 光らせるようにする
			t = 1;
		}

		// UV座標を調整
		floor[i][0]->SetUV(i * (1.0f / 4), t * (1.0f / 2));	// 数
		floor[i][1]->SetUV(3 * (1.0f / 4), t * (1.0f / 2));	// F
	}

	SetPosition();
}

void FloorUI::SetPosition()
{
	// 階層ごとのUI座標設定
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
