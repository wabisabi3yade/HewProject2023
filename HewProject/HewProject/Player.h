#pragma once
#include "CGridObject.h"
#include <iostream>
#include "CGrid.h"
#include "DoTween.h"
#include "PlayerMove.h"

#define MOVEROOT_MAX (20)	// 今まで取ってきた道を保存する最大数
#define EAT_TIME (1.0f)	// 食べ物食べる時間
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
		UP,
		DOWN,
		RIGHT,
		LEFT,
		NUM
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
	std::vector<D3DTEXTURE> normalTex;	
	std::vector<D3DTEXTURE> fatTex;
	std::vector<D3DTEXTURE>	thinTex;
	std::vector<D3DTEXTURE> muscleTex;
	
	
	// 画像を上に配列に入れる
	// 引数①：テクスチャパス ② 度の状態の配列に入れるか
	void TextureInput(const wchar_t* _texPath, STATE _set);
	
public:
	std::unique_ptr<DoTween> dotween;

	Player(D3DBUFFER vb, D3DTEXTURE tex);

	/// <summary>
	/// プレイヤーオブジェクトの初期化関数
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

	~Player();

	int GetCalorie() const { return calorie; }
	bool GetIsMoving()const;
	int GetDirection()const;
	void SetDirection(int _set);

	PlayerMove* GetPlayerMove()const;

	void SetGridTable(GridTable* _set) { gridTable = _set; }
	GridTable* GetGridTable() const { return gridTable; }

	STATE GetState() const { return playerState; }
};

