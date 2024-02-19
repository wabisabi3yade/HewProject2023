#include "CannonAnim.h"

CannonAnim::CannonAnim()
{
	animPattern = static_cast<int>(PATTERN::IDLE);
	AnimSpeedRate = 1.0f;
	dir = -1;
}

CannonAnim::~CannonAnim()
{
}

void CannonAnim::Update()
{
	int animTable[][32] = {

		{0,-1},//上向き待機状態


		{0,0,1,1,2,2,-2},//回転、上下から左右方向へ

		{2,2,1,1,0,0,-2},//回転、左右から上下方向へ

		{2,2,3,3,4,4,5,5,-2},//左方向へ

		{2,2,6,6,7,7,8,8,-2},//右方向へ

		{0,0,3,3,4,4,5,5,-2},//下方向へ

		{0,0,6,6,7,7,8,8,-2},//上方向へ


		//戻る
		{5,5,4,4,3,3,2,2,-2},//左方向から

		{8,8,7,7,6,6,2,2,-2},//右方向から

		{5,5,4,4,3,3,0,0,-2},//下方向から

		{8,8,7,7,6,6,0,0,-2},//上方向から
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
			isPlaying = false;
			//animPattern -= 1;
			// 最初のコマに戻して止める
			animCounter -= 1.0f;
		}
	}

	// 表示させるコマIDを取得
	int animID = animTable[animPattern][(int)animCounter];

	// 表示させるUVを計算
	nowUV.x = (animID % 3) * (1.0f / 3);

	nowUV.y = (animID / 3) * 0.25f;
}

void CannonAnim::PlayTurn(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	//dirで向きを確認する
	switch (_dir)
	{
	case 0:
	case 3:
	SetPattern(static_cast<int>(CannonAnim::PATTERN::UD_TURN));
		break;
	case 1:
	case 2:
	SetPattern(static_cast<int>(CannonAnim::PATTERN::LR_TURN));
		break;

	default:
		break;
	}
	//
}

void CannonAnim::PlayReturn(float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (dir)
	{
	case 0:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::D_RETURN));
		break;
	case 1:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::L_RETURN));
		break;
	case 2:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::R_RETURN));
		break;
	case 3:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::U_RETURN));
		break;
	default:
		break;
	}
}

void CannonAnim::PlayStart(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	dir = _dir;
	switch (_dir)
	{
	case 0:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::D_DIR));
		break;
	case 1:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::L_DIR));
		break;
	case 2:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::R_DIR));
		break;
	case 3:
		SetPattern(static_cast<int>(CannonAnim::PATTERN::U_DIR));
		break;
	default:
		break;
	}
}