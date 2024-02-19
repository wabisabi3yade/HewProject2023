#include "CAnimation.h"

CAnimation::CAnimation()
{
	isPlaying = true;
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	// 2Dゲームでおすすめのアニメーション方法
	// テーブルアニメーション・・・決められた順番で再生させるためのデータ
	// ※テーブル・・・なにかの目的のために作られたデータの集まり
	// 二次元配列のときは後ろの添え字は指定しなくちゃいけない（これぐらいあればいいだろうぐらいの数を入れるしかない）
	int animTable[][32] = {
		// 下向き
		{ 0, 1, 2, 1, -1 },	//　-1がきたら最初に戻る
		// 左向き
		{ 3, 4, 5, 4, -1 },
		// 上向き
		{ 6, 7, 8, 7, -1 },
		// 下向き
		{ 9, 10, 11, 10, -1},
		// エフェクト
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, -2 },	//　-1がきたら最初に戻る
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
		else if (animTable[animPattern][(int)animCounter] == -2)
		{
			// 再生を止める
			isPlaying = false;
			// 最初のコマに戻して止める
			animCounter = 0.0f;
		}
	}

	// 表示させるコマIDを取得
	int animID = animTable[animPattern][(int)animCounter];

	// 表示させるUVを計算
	nowUV.x = (animID % 3) * (1.0f / 3.0f);

	nowUV.y = (animID / 3) * (1.0f / 4.0f);
}

// セッター関数(animPattern)
void CAnimation::SetPattern(int setpattern)
{
	animPattern = setpattern;
}
