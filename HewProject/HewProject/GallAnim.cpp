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
		3, -1},//通常待機状態

		{0,1,2,
		3,4,5,
		6,-2},

		{3,4,5,6,-1}
	};


	// 再生中なら
	if (isPlaying)
	{
		// アニメーションのカウンターを進める
		animCounter += animSpeed * AnimSpeedRate;

		// -1が来たら最初に戻る（ループ再生）
		if (animTable[animPattern][(int)animCounter] == -1)
		{
			animCounter = 0.0f;
		}
		// -2が来たら停止させる処理
		else if (animTable[animPattern][(int)animCounter] == -2)
		{
			// 再生を止める
			//isPlaying = false;
			animPattern += 1;
			// 最初のコマに戻して止める
			animCounter = 0.0f;
		}
	}

	// 表示させるコマIDを取得
	int animID = animTable[animPattern][(int)animCounter];

	// 表示させるUVを計算
	nowUV.x = (animID % 3) * (1.0f / 3);

	nowUV.y = (animID / 3) * 0.25f;

}

void GallAnim::PlayOpen(float _animSpeedRate)
{
	AnimSpeedRate = _animSpeedRate;
	SetPattern(static_cast<int>(GallAnim::PATTERN::OPEN));
}
