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
		//何もしない
		{ 0, -1 },
		// 下向き
		{ 0, 1, 2, 1, -1 },	//　-1がきたら最初に戻る
		// 左向き
		{ 3, 4, 5, 4, -1 },
		// 右向き
		{ 6, 7, 8, 7, -1 },
		// 上向き
		{ 9, 10, 11, 10, -1},

	};

	// 再生中なら
	if (isPlaying)
	{
		// アニメーションのカウンターを進める
		animCounter += animSpeed;

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
	uv.x = (animID % 3) * 0.33f;

	uv.y = (animID / 3) * 0.25f;
}

void CPlayerAnim::PlayWalk(int num)
{
	SetPattern(num);
}

void CPlayerAnim::StopWalk()
{
	if (isStop == false)
	{
		isPlaying = false;
		isStop = true;
	}
	else
	{
		isPlaying = true;
		isStop = false;
	}

}

