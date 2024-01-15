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
		// 下向き
		{ 0, 0 ,1, 2, 2, 1, -1 },	//　-1がきたら最初に戻る
		// 左向き
		{ 3, 3, 4, 5, 5, 4, -1 },
		// 右向き
		{ 6, 6, 7, 8, 8, 7, -1 },
		// 上向き
		{ 9, 9, 10, 11, 11, 10, -1},

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
		//else if (animTable[animPattern][(int)animCounter] == -2)
		//{
		//	// 再生を止める
		//	isPlaying = false;
		//	// 最初のコマに戻して止める
		//	animCounter = 0.0f;
		//}
	}

	// 表示させるコマIDを取得
	int animID = animTable[animPattern][(int)animCounter];

	// 表示させるUVを計算
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


