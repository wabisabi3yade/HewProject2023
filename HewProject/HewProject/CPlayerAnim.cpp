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

		// 待機
		// 下向き
		{ 0, 0 ,1, 2, 2, 1, -1 },	//　-1がきたら最初に戻る
		// 左向き
		{ 3, 3, 4, 5, 5, 4, -1 },
		// 右向き
		{ 6, 6, 7, 8, 8, 7, -1 },
		// 上向き
		{ 9, 9, 10, 11, 11, 10, -1},

		// 歩き
		// 下向き
		{ 0, 0 ,1, 2, 2, 1, -1 },	//　-1がきたら最初に戻る
		// 左向き
		{ 3, 3, 4, 5, 5, 4, -1 },
		// 右向き
		{ 6, 6, 7, 8, 8, 7, -1 },
		// 上向き
		{ 9, 9, 10, 11, 11, 10, -1},

		// 焦っている歩き
		// 下向き
		{  0 ,1, 2, 1, -1 },	//　-1がきたら最初に戻る
		// 左向き
		{  3, 4, 5, 4, -1 },
		// 右向き
		{  6, 7, 8, 7, -1 },
		// 上向き
		{ 9, 10, 11, 10, -1},

		//大砲の動き
		// 下向き
		{0,1,2,-1},
		// 左向き
		{3,4,5,-1},
		// 右向き
		{6,7,8,-1},
		// 上向き
		{9,10,11,-1},

		//食べる
		//右向き
		{0,0,1,1,2,2,
		3,3,},
		//左向き
		{6,6,7,7,8,8,
		9,9,-1},

		//パンチ
		{ 0,0,1,1,2,2,
		 3,3,3,3,3,4,4,5,5,
		 6,6,6,7,7,7,7,-1},
		
		 //バウム
		{ 0,0,1,1,2,2,
		3,3,4,4,5,5,
		6,6,7,7,-1},
		//
		{0,0,1,2,
		3,4,5,
		6,7,-2},
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
			animCounter -= 1.0f;
			// 最初のコマに戻して止める
			isPlaying = false;
		}
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
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;

	switch (num)
	{
		//　下
		// 全方位行動可
	case 0:
		SetPattern(static_cast<int>(PATTERN::WALK_DOWN));
		break;

		// 左
	case 1:
		SetPattern(static_cast<int>(PATTERN::WALK_LEFT));
		break;

		// 右
	case 2:
		SetPattern(static_cast<int>(PATTERN::WALK_RIGHT));
		break;

		// 上
	case 3:
		SetPattern(static_cast<int>(PATTERN::WALK_UP));
		break;
	}
}

void CPlayerAnim::StopWalk(int _num)
{
	isPlaying = true;
	AnimSpeedRate = 1.0f;
	switch (_num)
	{
	case 0:
		SetPattern(static_cast<int>(PATTERN::STAY_DOWN));
		break;
	case 1:
		SetPattern(static_cast<int>(PATTERN::STAY_LEFT));
		break;
	case 2:
		SetPattern(static_cast<int>(PATTERN::STAY_RIGHT));
		break;
	case 3:
		SetPattern(static_cast<int>(PATTERN::STAY_UP));
		break;
	default:
		break;
	}
	animCounter = 0.0f;
	//animPattern -= static_cast<int>(PATTERN::WALK_DOWN);
	if (animPattern < 0) animPattern = 0;
}

void CPlayerAnim::PlayFall(int _num, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_num)
	{
		//　下
		// 全方位行動可
	case 0:
		SetPattern(static_cast<int>(PATTERN::PANIC_DOWN));
		break;

		// 左
	case 1:
		SetPattern(static_cast<int>(PATTERN::PANIC_LEFT));
		break;

		// 右
	case 2:
		SetPattern(static_cast<int>(PATTERN::PANIC_RIGHT));
		break;

		// 上
	case 3:
		SetPattern(static_cast<int>(PATTERN::PANIC_UP));
		break;
	}
}

void CPlayerAnim::PlayCannon(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_dir)
	{
		//　下
		// 全方位行動可
	case 0:
		SetPattern(static_cast<int>(PATTERN::CANNON_DOWN));
		break;

		// 左
	case 1:
		SetPattern(static_cast<int>(PATTERN::CANNON_LEFT));
		break;

		// 右
	case 2:
		SetPattern(static_cast<int>(PATTERN::CANNON_RIGHT));
		break;

		// 上
	case 3:
		SetPattern(static_cast<int>(PATTERN::CANNON_UP));
		break;
	}
}

void CPlayerAnim::PlayEat(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_dir)
	{
		//　下
		// 全方位行動可
	case 0:
		// 右
	case 2:
		SetPattern(static_cast<int>(PATTERN::EAT_RIGHT));
		break;
		// 左
	case 1:
		// 上
	case 3:
		SetPattern(static_cast<int>(PATTERN::EAT_LEFT));
		break;
	}
}

void CPlayerAnim::PlayPunch(float _animSpeedRate, bool _isGall)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	if(!_isGall)
	SetPattern(static_cast<int>(PATTERN::PUNCH));
	else
	SetPattern(static_cast<int>(PATTERN::GALL_PUNCH));
}

void CPlayerAnim::PlayBaum(int _dir, float _animSpeedRate)
{
	isPlaying = true;
	animCounter = 0;
	AnimSpeedRate = _animSpeedRate;
	switch (_dir)
	{
		//　下
		// 全方位行動可
	case 0:
		// 右
	case 2:
		// 左
	case 1:
		// 上
	case 3:
		SetPattern(static_cast<int>(PATTERN::BAUM));
		break;
	}
}


