#include "CEffectAnim.h"

CEffectAnim::CEffectAnim()
{

}

void CEffectAnim::Update()
{
	// 2Dゲームでおすすめのアニメーション方法
	// テーブルアニメーション・・・決められた順番で再生させるためのデータ
	// ※テーブル・・・なにかの目的のために作られたデータの集まり
	// 二次元配列のときは後ろの添え字は指定しなくちゃいけない（これぐらいあればいいだろうぐらいの数を入れるしかない）
	int animTable[][32] = {
		// 下向き
		{0,1,2,3,4,5,6,7,8,9,10,11,-2},//　-1がきたら最初に戻る
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
	uv.x = (animID % 3) * 0.33f;

	uv.y = (animID / 3) * 0.25f;
}

CEffectAnim::~CEffectAnim()
{
}
