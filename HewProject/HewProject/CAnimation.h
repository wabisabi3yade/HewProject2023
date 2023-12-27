#pragma once
#include "direct3d.h"

// アニメーション機能のクラス（キャラクター、敵やら）

class CAnimation
{
public:
	// 列挙型
	// アニメーションパターン名
	enum PATTERTN
	{
		DOWN,
		RIGHT,
		LEFT,
		UP,
		FX_0_11,	// エフェクトの0～11番目の画像を流す
		PATTERN_NUM
	};

protected:
	// アニメーション変数
	FLOAT_XY uv = {};	// アニメーションのUV移動量を保存
	float animCounter = 0.0f;	// アニメテーブルのカウンター
	int animPattern = 0;	// 再生するアニメーションのパターンIDを持つ変数
	
	
public:
	float animSpeed = 0.1f;	// 再生速度
	bool isPlaying = false;	// 再生中かどうかを表す変数
	bool isStop = false;    // アニメーション停止

public:

	CAnimation();

	// メンバー関数
	virtual void Update();

	//// 再生速度を設定する
	//void SetAnimSpeed(float setspeed);

	// 再生するアニメーションを変更する

	// セッター関数(u)
	FLOAT_XY GetUV() { return uv; }

	// セッター関数(animPattern)
	void SetPattern(int setpattern);	

	// ゲッター・セッター
	int GetisFX() { return animPattern; }
	void SetisFX(int setPattern) { animPattern = setPattern; }

	//effect用セッター
	virtual void SetEffectLoop(bool) { 0; }

};

