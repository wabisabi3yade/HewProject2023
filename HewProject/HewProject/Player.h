#pragma once
#include "CGridObject.h"
#include <iostream>
#include "CGrid.h"
#include "DoTween.h"
#include "PlayerMove.h"
#include"CPlayerAnim.h"

#define MOVEROOT_MAX (20)	// 今まで取ってきた道を保存する最大数
#define EAT_TIME (1.0f)	// 食べ物食べる時間
#define BREAK_TIME (3.0f) //壁を壊してから移動できるまでの時間
#define FALL_TIME (3.0f) //チョコが壊れてから落ち始めるまでの時間
#define FALLMOVE_TIME (1.0f) //落ちる移動時間
#define FALL_POS_Y (-4.5f) //落ちる最終座標
#define THIN_CALOMAX (5)	// ガリ状態時での最大カロリー数 
#define NORMAL_CALOMAX (10)	// 普通状態時での最大カロリー数 

// プレイヤー（リス）のオブジェクトクラス
class Player :
	public CGridObject
{
public:
	enum class STATE
	{
		NORMAL,	// 通常
		THIN,	// ガリ
		FAT,	// デブ
		MUSCLE,	// マッチョ
		NUM
	};

	// 方向
	enum class DIRECTION
	{
		DOWN,	// 下
		LEFT,	// 左
		RIGHT,	// 右
		UP,	// 上
		NUM,
		EVERY,	// 全方位移動可能（キャラの画像の向きは下向き）
	};

	enum ANIM_TEX
	{
		WALK,
		EAT,
		ACTION,
		NUM,
	};

private:
	STATE playerState;	// プレイヤーの今の状態

	DIRECTION direction;	// 今向いている方向

	std::shared_ptr<PlayerMove> move;	// PlaterMoveクラス(状態別のアドレスを入れる)

	// 今まで通ってきた経路を保存する座標
	CGrid::GRID_XY moveRoot[MOVEROOT_MAX];

	int calorie;	// カロリー

	int nowFloor;	// 今何層目にいるか

	GridTable* gridTable;// ステージのグリッドテーブルのポインタを設定

	// テクスチャ（状態別）
	D3DTEXTURE normalTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE fatTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE thinTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE muscleTex[static_cast<int>(ANIM_TEX::NUM)];
	
	// 画像を上に配列に入れる
	// 引数①：テクスチャパス ② 度の状態の配列に入れるか
	void TextureInput(const wchar_t* _texPath, STATE _set , ANIM_TEX _anim_tex);
	
public:
	std::unique_ptr<DoTween> dotween;

	Player(D3DBUFFER vb, D3DTEXTURE tex);

	/// <summary>
	/// ステージに入った時に使われる初期化関数
	/// </summary>
	/// <param name="_grid">スタート時のグリッド座標</param>
	/// <param name="_pTable">グリッドテーブル</param>
	void Init(GridTable* _pTable);

	void Update() override;

	// カロリーに関する処理
	void WalkCalorie();
	void EatCake();
	void EatChilli();

	/// <summary>
	/// 状態を変化するときに処理をする関数
	/// </summary>
	/// <param name="_set">変化先の状態</param>
	void ChangeState(STATE _set);

	void Draw() override;

	void Fall();

	~Player();

	int GetCalorie() const { return calorie; }
	void SetCalorie(int _cal) { calorie = _cal; }
	bool GetIsMoving()const;
	int GetDirection()const;
	void SetDirection(int _set);

	PlayerMove* GetPlayerMove()const;

	CPlayerAnim* GetPlayerAnim() { return dynamic_cast<CPlayerAnim*> (mAnim); }

	void SetGridTable(GridTable* _set) { gridTable = _set; }
	GridTable* GetGridTable() const { return gridTable; }

	STATE GetState() const { return playerState; }
};

