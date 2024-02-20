#pragma once
#include"CScene.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
#include"CGridObject.h"
#include "Player.h"
#include"ProteinUI.h"
#include"FloorUI.h"
#include "CalorieGage_hori.h"
#include "CMenu.h"
#include"CoinUI.h"
class DoTween;
class CArrow;
class CGameClear;
class CGameOver;
class CGameStart;
#define MAX_LAYER (3)         // 階層の最大数
#define UNDO_ARRAY_NUM (40)	// Undoの配列の要素数

class GridTable;

class Tutorial;

class StageScene :
	public CObject
{
public:

	struct FIELD_FLOOR
	{
		// ステージ床の上にあるテーブル
		short int objectTable[MAX_LAYER][MAX_GRIDNUM][MAX_GRIDNUM] = {};

		// ステージ床のテーブル
		short int floorTable[MAX_LAYER][MAX_GRIDNUM][MAX_GRIDNUM] = {};
		
		//　プレイヤーが1つ前にいた何階層にいたか 
		short int old_Floor;	

		//プレイヤーの座標
		CGrid::GRID_XY playerUndo;

		//プレイヤーの状態
		Player::STATE stateUndo;

		//プレイヤーの方向
		int dirUndo;

		//プレイヤーのカロリー
		int calorieUndo;

	};

private:
	CLoadStage* stage;
	/*CStageMake* stageMake;*/
	/*std::vector<STAGEPOS> stagePos;*/
	const wchar_t* CsvPath[PathLength] = { L"asset/mizuno/Stage.csv" };
	Player* player;
	short nowFloorNum;	// 現在にいる階層の数字

	CScene::SCENE_NAME selectName = CScene::SCENE_NAME::STAGE1;
	CScene::SCENE_NAME nextStageName = CScene::SCENE_NAME::STAGE1;

	bool isTrue = true;
	bool isFalse = false;

	// ステージのグリッドテーブル
	GridTable* oneFloor;	// 1階
	GridTable* secondFloor;	// 2階
	GridTable* thirdFloor;	// 3階
	GridTable* nowFloor;	// 現在の階層

	std::unique_ptr<DoTween> dotween;

	CGameClear* gameClear;
	CGameOver* gameOver;
	CGameStart* gameStart;

	//ステージの縦幅と横幅
	CGrid::GRID_XY stageSquare;
	// ステージの大きさ
	float stageScale = 0.0f;

	//メニュー画面
	CMenu* Menu;

	//開始フロア
	int startFloor;

	int lockStageMap;

	bool changeflag;

	bool FloorOnlyMap;

	bool cannonMove = false;

	bool* isLookMap;

	bool* isMenu;

	bool gallVibration = false;

	bool gallReduction = false;

	bool isGameClear;

	bool isStartStop;

	//最大フロア
	int nMaxFloor;

	// リセットのときに使用する最初の状態
	FIELD_FLOOR floorReset;

	// やり直し機能
	FIELD_FLOOR floorUndo[UNDO_ARRAY_NUM];
	int nNumUndo = 0;
	int nNextUndo = 1;

	std::vector<CGridObject*> oneFStgObj;	// 1階のオブジェクト格納
	std::vector<CGridObject*>secondFStgObj;	// 2階
	std::vector<CGridObject*>thirdFStgObj;	// 3階
	std::vector<CGridObject*> *vStageObj;	// 現在の階層の配列のポインタ変数
											//（ここに今の階層のvector配列のアドレスを入れる）
	// バッファ	
	D3DBUFFER stageBuffer;	// ステージのオブジェクト
	D3DBUFFER playerBuffer;	// プレイヤー
	D3DBUFFER clearBuffer;	// クリア
	D3DBUFFER LR_ButtonBuffer;	// LB_RLボタン用バッファ

	// テクスチャ
	D3DTEXTURE stageTextureFloor;
	D3DTEXTURE stageTextureFloor2;
	D3DTEXTURE stageTextureWall;
	D3DTEXTURE stageTextureHoll;
	D3DTEXTURE stageTextureWataame;
	D3DTEXTURE stageTextureCastella;
	D3DTEXTURE stageTextureBaumkuchen_R;
	D3DTEXTURE stageTextureBaumkuchen_L;
	D3DTEXTURE stageTextureChocolate;
	D3DTEXTURE stageTextureChocolateClack;
	D3DTEXTURE stageTextureCake;
	D3DTEXTURE stageTextureChili;
	D3DTEXTURE stageTextureCoin;
	D3DTEXTURE stageTextureGallChest[3];//0　通常　1　光開く　2　光オーラ
	D3DTEXTURE stageTextureGumi;
	D3DTEXTURE stageTextureProtein;
	D3DTEXTURE playerTexture;
	D3DTEXTURE shadowTexture;
	D3DTEXTURE stageTextureCannon[2]; //0に左右 1に上下
	D3DTEXTURE stageTextureArrow;
	D3DTEXTURE stageTextureBaumAnim[4];

	D3DTEXTURE ButtonTextureCamera;
	D3DTEXTURE ButtonTextureFloorLook;
	D3DTEXTURE ButtonTextureUndo;
	D3DTEXTURE TextTextureLooking;
	D3DTEXTURE Button_LB_RB_Texture;
	D3DTEXTURE ButtonTextureCameraBack;
	D3DTEXTURE GetProteinTexture;
	D3DTEXTURE GoChestTexture;

	//UI関係
	UI* LookingTxet;
	UI* CameraButton;
	UI* FloorLookButton;
	UI* UndoButton;
	UI* RB_Button;
	UI* LB_Button;
	UI* BackCameraButton;
	
	UI* GetProtein;
	//プロテイン
	ProteinUI* proteinUi;
	//コイン
	CoinUI* coinUI;

	//階層
	FloorUI* floorUi;

	//カロリーゲージ
	CalorieGage_hori* calorieGage;

	CArrow* Arrow[static_cast<int>(Player::DIRECTION::NUM)];

	// チュートリアルするかどうかフラグ
	bool isDoTutorial = false;
	bool isTutorialNow = false;
	Tutorial* tutorial = nullptr;

	bool isW11 = false;


public:
	int nNumProtein;	// 現在ステージにあるプロテインの数

	int nNumCoin;
	StageScene(D3DBUFFER vb, D3DTEXTURE tex, short int worldNum, bool _isW11 = false);
	~StageScene();

	void Update();
	// プレイヤーの動きによってステージのオブジェクトを変化する処理
	void StageMove();
	// グリッドテーブルの更新をする
	void TableUpdate();

	// カステラに動かせる命令を出す
	void CastellaMoveOrder();

	// 大砲の中での入力を受け付ける
	void InCanonInput();

	// アイテム（ケーキとか）と同じマスに移動するとアイテムを消したりする関数 次のマス用
	void ItemDelete();
	//現在地のアイテムを消す関数
	void CannonItemDelete(CGrid::GRID_XY _deletePos = {-1,-1}, CGridObject::BlockType _type = CGridObject::BlockType::NONE);

	// ステージの状態を一つ前に戻す関数
	void Undo(float _stageScale, bool isPush = false);
	// 移動するごとに前のテーブル状態に更新する
	void UndoTableUpdate();

	void Reset();

	// ひとつ前に戻すときにプレイヤーの情報を設定する
	void UndoPlayerSet(const int& _dir, const int& _calorie, const Player::STATE& _state);

	void Draw();
	void Z_Sort(std::vector<CGridObject*>& _sortList);
	// ステージの初期化関数
	void Init(const wchar_t* filePath);

	// ステージをグリッドテーブルから作る関数
	void CreateStage(const GridTable& _gridTable, std::vector<CGridObject*>& _settingList);

	void ChangeFloor(int _nextFloor);

	void MapDraw();

	/// <summary>
	/// ゲーム開始時のプレイヤーの状態を変える関数
	/// </summary>
	/// <param name="_calorie">初期カロリー MAX15</param>
	/// <param name="_state">プレイヤーの初期状態  0 通常  1 ガリ  2 デブ 3 マッチョ</param>
	void SetPlayerStartstatus(int _calorie , int _state) { player->SetCalorie(_calorie) ,player->ChangeState(static_cast<Player::STATE>(_state)); }

	// 今の階層にある指定したグリッド座標のオブジェクトを取得する
	CGridObject* GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	CGridObject* GetStageFloor(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	// ステージ内のプレイヤーを取得
	Player* GetPlayer() const { return player; };

	GridTable* GetNowFloor() const;

	void SetTutorial(Tutorial* _setTutorial);

	void SetNextStageName(CScene::SCENE_NAME _set) { nextStageName = _set; }
};
