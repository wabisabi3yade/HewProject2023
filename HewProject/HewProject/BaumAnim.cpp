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

	// 再生中なら
	if (isPlaying)
	{
		// アニメーションのカウンターを進める
		animCounter += animSpeed * animRate;
		AnimEnd = false;
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
			animCounter = 0.0f;
			//animPattern -= 1;
			// 最初のコマに戻して止める
			//animCounter -= 1.0f;
			AnimEnd = true;
		}
	}

	// 表示させるコマIDを取得
	int animID = animTable[animPattern][(int)animCounter];

	// 表示させるUVを計算
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
