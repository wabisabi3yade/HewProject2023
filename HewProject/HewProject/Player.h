#pragma once
#include "CGridObject.h"
#include <iostream>
#include "CGrid.h"
#include "DoTween.h"
#include "PlayerMove.h"
#include"CPlayerAnim.h"
#include<list>
#include"CEffectManeger.h"

#define CAKE_CALORIE (15)	// ケーキ食べたあとのリスのカロリー

#define MOVEROOT_MAX (20)	// 今まで取ってきた道を保存する最大数
#define EAT_TIME (1.3f)	// 食べ物食べる時間
#define BREAK_TIME (1.4f) //壁を壊してから移動できるまでの時間
#define FALL_TIME (1.75f) //チョコが壊れてから落ち始めるまでの時間
#define FALLMOVE_TIME (0.65f) //落ちる移動時間
#define FALL_POS_Y (-4.5f) //落ちる最終座標
#define JUMP_TIME (1.25f) //ジャンプの移動時間
#define BOUND_TIME (0.9f) //ジャンプ後のバウンドする時間
constexpr float BOUND_CURVE_POS_Y = 1.3f;	//バウンドするときの高さ
constexpr float RISING_TIME = 0.5f; //グミでの上昇時間
#define THIN_CALOMAX (5)	// ガリ状態時での最大カロリー数 
#define NORMAL_CALOMAX (10)	// 普通状態時での最大カロリー数 
constexpr float CANNONMOVE_TIME = 0.4f;		//大砲でのいどうじかん
constexpr float CANNONBOUND_TIME = 1.0f;	//大砲で目的地でのバウンドする時間
constexpr float CANNONBOUND_POS_Y = 3.0f;	//大砲で目的地でのバウンドする高さ
constexpr float CANNON_IN_CURVE_POS_Y = 2.0f;//大砲に入るときの最大地点
constexpr float MAKEOVER_TIME = 1.0f; //マッチョになるときのアニメーションの時間（白目）

class CalorieGage_hori;

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
		EAT_CAKE,
		EAT_CHILI,
		ACTION,
		WAIT,
		PANIC,
		DRINK,
		NUM,
		CANNON,
		BAUM,
		PUNCH,
		PUSH_CASTELLA,
		GALL_EAT,
		GAMEOVER,
	};

private:
	STATE playerState;	// プレイヤーの今の状態

	DIRECTION direction;	// 今向いている方向

	std::shared_ptr<PlayerMove> move;	// PlaterMoveクラス(状態別のアドレスを入れる)

	// 今まで通ってきた経路を保存する座標
	CGrid::GRID_XY moveRoot[MOVEROOT_MAX];

	int calorie;	// カロリー

	int nowFloor;	// 今何層目にいるか

	bool IsgameOver;

	bool gameOverOnes;

	bool GameClear;

	bool ChangeCannonTexture;

	bool fallFloorChangeTrriger; //落ちて階層が変わったか
	bool risingChangeTrriger;

	bool isEat;

	bool PlayMakeover;

	bool IsPlaymakeover;

	bool IsPlayMakeoverTrigger;

	bool IsStop;

	bool isCasetellaPush;


	GridTable* gridTable;// ステージのグリッドテーブルのポインタを設定
	GridTable* nextGridTable; //次の階層グリッドテーブルのポインタを設定

	// テクスチャ（状態別）
	D3DTEXTURE normalTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE fatTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE thinTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE muscleTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE castellaPushTex;
	D3DTEXTURE cannonTex;
	D3DTEXTURE GallEatTex;
	D3DTEXTURE GameOverTex;
	//DIRECTIONと同じ向きのパンチの画像を格納
	D3DTEXTURE punchTex[static_cast<int>(DIRECTION::NUM)];
	// 画像を上に配列に入れる
	// 引数�@：テクスチャパス �A 度の状態の配列に入れるか
	void TextureInput(const wchar_t* _texPath, STATE _set , ANIM_TEX _anim_tex);
	
	std::list<CEffect*> effect;

	//UI

	//カロリーゲージ
	CalorieGage_hori* calorieGage;

public:
	bool fallMoveTrriger;
	bool risingMoveTrriger;
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

	void ChangeTexture(ANIM_TEX _animTex);

	void Draw() override;

	void Fall();

	void Rise();

	void EatEnd();

	~Player();

	int GetCalorie() const { return calorie; }
	void SetCalorie(int _cal) { calorie = _cal; }
	bool GetIsMoving()const;
	int GetDirection()const;
	void SetDirection(int _set);
	void SetChangeCannonTexture(const bool _set) { ChangeCannonTexture = _set; }

	PlayerMove* GetPlayerMove()const;

	CPlayerAnim* GetPlayerAnim() { return dynamic_cast<CPlayerAnim*> (mAnim); }
	void SetGameOver(bool _set) { IsgameOver = _set; }
	void Reset();
	bool GetIsGameOver() { return  IsgameOver; }
	bool GetGameOverOnes() { return  gameOverOnes; }
	int GetNowFloor() { return nowFloor; }
	void SetNowFloor(int _set);
	void GameOver();
	void PlayEffect(Vector3 _pos, Vector3 _scale, EffectManeger::FX_TYPE _type, bool _isLoop);
	bool GetFallTrriger() { return fallMoveTrriger; }
	bool GetFallFloorChageTrriger() { return fallFloorChangeTrriger; }
	bool GetRiseFloorChangeTrriger() { return risingChangeTrriger; }
	bool GetRiseTrriger() { return risingMoveTrriger; }
	bool GetCangeCannonTexture() { return ChangeCannonTexture; }
	bool GetCannonFX()const { return move->GetCannonFX(); }
	bool GetIsStop()const { return IsStop; }
	void SetGridTable(GridTable* _set) { gridTable = _set; }
	void SetNextGridTable(GridTable* _set) { nextGridTable = _set; }
	GridTable* GetGridTable() const { return gridTable; }
	GridTable* GetNextGridTable()const { return nextGridTable; }
	bool* GetCanMoveDir() { return move->GetCanMoveDir(); }
	STATE GetState() const { return playerState; }
	void SetCalorieGage(CalorieGage_hori* _calorie) { calorieGage = _calorie; }
	
	void SetIsCastellaPush(bool _set) { isCasetellaPush = _set; }
	bool GetIsMissMove()const { return move->GetIsMissMove(); }

	bool GetIsPlayMakeover()const { return IsPlaymakeover; }
	bool GetIsPlayMakeoverTrigger()const { return IsPlayMakeoverTrigger; }
	bool GetPlayMakeover()const { return PlayMakeover; }
	void SetIsPlayMakeover(bool _set) { IsPlaymakeover = _set; }
	void SetPlayMakeover(bool _set) { PlayMakeover = _set; }
};

