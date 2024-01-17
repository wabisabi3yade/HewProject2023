//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "StageScene.h"
#include<iostream>
#include<algorithm>
#include"CCake.h"
#include"CChoco.h"
#include"CCastella.h"
#include"CWall.h"
#include"CHoll.h"
#include "CFloor.h"
#include"CBaum.h"
#include"CCoin.h"
#include"CWataame.h"
#include"CGumi.h"
#include"CProtein.h"
#include"CGall.h"
#include"CChili.h"
//#include "Player.h"
#include "GridTable.h"
#include "TextureFactory.h"

#define PLAYER dynamic_cast<Player*>(player)	// わざわざ書くのめんどくさい

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	nNumProtein = 0;

	// テクスチャを管理するクラスのインスタンスを取得
	TextureFactory* texFactory = TextureFactory::GetInstance();

	// 各オブジェクトのテクスチャを取得する
	stageTextureFloor = texFactory->Fetch(L"asset/Stage/floor_y.png");
	stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/floor_g.png");
	/*stageTextureFloor = texFactory->Fetch(L"asset/Stage/2floor_y.png");
	stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/2floor_g.png"); */


	stageTextureWall = texFactory->Fetch(L"asset/Stage/Wall.png");
	stageTextureHoll = texFactory->Fetch(L"asset/Stage/test_Hool.png");
	stageTextureWataame = texFactory->Fetch(L"asset/Stage/Wataame.png");

	/*stageTextureCastella = texFactory->Fetch(L"asset/Stage/Castella.png");*/
	stageTextureCastella = texFactory->Fetch(L"asset/Stage/2castella.png");

	stageTextureBaumkuchen_R = texFactory->Fetch(L"asset/Stage/Baumkuchen_R.png");
	stageTextureBaumkuchen_L = texFactory->Fetch(L"asset/Stage/Baumkuchen_L.png");
	stageTextureChocolate = texFactory->Fetch(L"asset/Stage/Chocolate.png");
	stageTextureCake = texFactory->Fetch(L"asset/Item/Cake.png");
	stageTextureChili = texFactory->Fetch(L"asset/Item/Chili.png");
	stageTextureCoin = texFactory->Fetch(L"asset/Item/Coin.png");
	stageTextureGallChest = texFactory->Fetch(L"asset/Stage/GallChest.png");
	stageTextureGumi = texFactory->Fetch(L"asset/Stage/Gumi.png");
	stageTextureProtein = texFactory->Fetch(L"asset/Item/Protein.png");
	/*playerTexture = texFactory->Fetch(L"asset/Stage/floor_y.png");*/
	shadowTexture = texFactory->Fetch(L"asset/Item/shadow.png");

}

// テクスチャは解放しない
StageScene::~StageScene()
{
	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(playerBuffer);

	CLASS_DELETE(stage);

	for (std::vector<CGridObject*>::iterator it = oneFStgObj.begin(); it != oneFStgObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
	oneFStgObj.clear();

	for (std::vector<CGridObject*>::iterator it = secondFStgObj.begin(); it != secondFStgObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
	secondFStgObj.clear();

	for (std::vector<CGridObject*>::iterator it = thirdFStgObj.begin(); it != thirdFStgObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
	thirdFStgObj.clear();

	CLASS_DELETE(oneFloor);
	CLASS_DELETE(secondFloor);
	CLASS_DELETE(thirdFloor);
}

void StageScene::Update()
{
	for (int i = 0; i < vStageObj.size(); i++)
	{
		vStageObj[i]->Update();
	}

	StageMove();

	if (gInput->GetKeyTrigger(VK_BACK))
	{
		Undo(stageScale);
	}

	if (gInput->GetKeyTrigger(VK_ESCAPE))
	{
		ChangeFloor(2);
	}

	// 動いているときと動き終わった瞬間だけ
	if (player->GetPlayerMove()->GetIsMoving() || player->GetPlayerMove()->GetIsMoveTrigger())
	{
		// グリッドテーブルを更新する
		TableUpdate();
	}

	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{
		for (int k = 0; k < MAX_LAYER; k++)
		{
			if (k == 1 && secondFloor == nullptr)
			{
				break;
			}
			else if (k == 2 && thirdFloor == nullptr)
			{
				break;
			}

			for (int i = 0; i < stageSquare.y; i++)
			{
				for (int j = 0; j < stageSquare.x; j++)
				{
					floorUndo[nNextUndo].floorTable[k][i][j] = nowFloor->floorTable[i][j];
					floorUndo[nNextUndo].objectTable[k][i][j] = nowFloor->objectTable[i][j];
				}
			}
		}

		floorUndo[nNextUndo].playerUndo = player->GetGridPos();
		floorUndo[nNextUndo].stateUndo = player->GetState();
		floorUndo[nNextUndo].dirUndo = player->GetDirection();
		floorUndo[nNextUndo].calorieUndo = player->GetCalorie();
		floorUndo[nNextUndo].old_Floor = nowFloorNum;

		nNextUndo++;
		nNumUndo = nNextUndo;
		if (nNextUndo > 20)
		{
			nNextUndo = 0;
		}
	}
}

void StageScene::StageMove()
{
	// ↓プレイヤーの動きにあわせてステージ内の物を動かす
	if (player->GetPlayerMove()->GetIsMoveStart())
	{
		// プレイヤーが太ってる　かつ　移動した先がカステラなら
		if (player->GetState() == Player::STATE::FAT &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CASTELLA)
		{
			// カステラに移動しろと命令する
			CastellaMoveOrder();
		}
		// プレイヤーがマッチョ　かつ　移動先が壁なら
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::WALL)
		{
			CWall* wallObj = dynamic_cast<CWall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::WALL));
			wallObj->Break();
		}
		if (player->GetPlayerMove()->CheckNowFloorType() == CGridObject::BlockType::WATAAME)
		{
			CWataame* wataameObj = dynamic_cast<CWataame*>(GetStageObject(player->GetGridPos(), CGridObject::BlockType::WATAAME));
			wataameObj->Melt();

			// ↓ここで穴のオブジェクトをnewしてvstageObjにpushbackする

			CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
			hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetGridPos()));
			hollObj->SetBlookType(CGridObject::BlockType::HOLL);
			hollObj->mTransform.pos = nowFloor->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
			vStageObj.push_back(hollObj);
		}
	}

	// プレイヤーが動き終えると
	if (player->GetPlayerMove()->GetIsWalkEnd())
	{
		if (player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCO ||
			player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCOCRACK)
		{
			CChoco* chocoObj = dynamic_cast<CChoco*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType> (player->GetPlayerMove()->CheckNextFloorType())));
			chocoObj->CRACK();
			if (player->GetState() == Player::STATE::FAT)
			{
				chocoObj->CRACK();
			}
			if (chocoObj->GetActive() == false)
			{
				CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
				hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetGridPos()));
				hollObj->SetBlookType(CGridObject::BlockType::HOLL);
				hollObj->mTransform.pos = nowFloor->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
				vStageObj.push_back(hollObj);
			}
		}
		// アイテムがあるならそれを画面から消す
		ItemDelete();
	}
	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{
		if (player->GetState() != Player::STATE::MUSCLE && nNumProtein <= 0)
		{
			player->ChangeState(Player::STATE::MUSCLE);
		}

	}

}

void StageScene::TableUpdate()
{
	// 一旦全て白紙にする
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// その行の最初が使われていないなら終わる
		if (nowFloor->floorTable[i][0] == 0) break;

		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// 列が使われていないなら
			if (nowFloor->floorTable[i][j] == 0) break;

			nowFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
			nowFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
		}
	}

	// 配列全て見る
	for (auto itr = vStageObj.begin(); itr != vStageObj.end(); itr++)
	{
		// そのオブジェクトが画面にないなら次に行く
		if (!(*itr)->GetActive()) continue;

		// グリッド座標取って
		CGrid::GRID_XY g = (*itr)->GetGridPos();
		// 今の階層のテーブルに更新する
		if ((*itr)->GetCategory() == CGridObject::Category::FLOOR)
		{
			nowFloor->floorTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
		else
		{
			nowFloor->objectTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
	}
}

void StageScene::CastellaMoveOrder()
{
	// 座標を求める ////////////////////////////////////////////////////
	CGrid::GRID_XY d = {};
	switch (static_cast<Player::DIRECTION>(player->GetDirection()))
	{
	case Player::DIRECTION::UP:
		d.y = -1;
		break;

	case Player::DIRECTION::DOWN:
		d.y = 1;
		break;

	case Player::DIRECTION::RIGHT:
		d.x = 1;
		break;

	case Player::DIRECTION::LEFT:
		d.x = -1;
		break;
	}

	CGrid::GRID_XY next = player->GetPlayerMove()->GetNextGridPos();

	// 動かす先のワールド座標を求める
	CGrid::GRID_XY targetGrid = { next.x + d.x, next.y + d.y };

	Vector3 target = nowFloor->GridToWorld(targetGrid, CGridObject::BlockType::CASTELLA);

	/////////////////////////////////////////////////////////////////////

	// リストの中からプレイヤーの移送先座標と同じもの　かつ　カステラを探す
	auto itr = std::find_if(vStageObj.begin(), vStageObj.end(),
		[&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == next.x && _obj->GetGridPos().y == next.y &&
				_obj->GetBlookType() == CGridObject::BlockType::CASTELLA);
		});

	CCastella* castella = static_cast<CCastella*>((*itr));

	// 動かした先が穴なら
	if (nowFloor->floorTable[targetGrid.y][targetGrid.x] == static_cast<int>(CGridObject::BlockType::HOLL))
	{
		Vector3 floorPos = nowFloor->GridToWorld(targetGrid, CGridObject::BlockType::FLOOR);
		castella->Move(target, true, floorPos);
		castella->SetGridPos(targetGrid.x, targetGrid.y);

		// オブジェクトテーブルからカステラを消して
		nowFloor->objectTable[targetGrid.y][targetGrid.x] = static_cast<int>(CGridObject::BlockType::NONE);

		//	カステラを床にする
		castella->SetCategory(CGridObject::Category::FLOOR);
		castella->SetBlookType(CGridObject::BlockType::CASTELLA_FLOOR);

		// 穴を画面から消す
		GetStageFloor(targetGrid, CGridObject::BlockType::HOLL)->SetActive(false);
	}
	else
	{
		castella->Move(target, player->GetDirection());
		castella->SetGridPos(targetGrid.x, targetGrid.y);
	}
}

void StageScene::ItemDelete()
{
	CGrid::GRID_XY next = player->GetPlayerMove()->GetNextGridPos();

	CGridObject* deleteObj;	// 画面から消す予定のポインタがはいる

	switch (static_cast<CGridObject::BlockType>
		(nowFloor->objectTable[next.y][next.x]))
	{
		// プレイヤーの位置にこのアイテムがあれば
	case CGridObject::BlockType::PROTEIN:
		nNumProtein--;
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::COIN:
	case CGridObject::BlockType::CHILI:
	{
		// リストの中からプレイヤーの座標と同じもの　かつ　床じゃない物を探す
		auto itr = std::find_if(vStageObj.begin(), vStageObj.end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, static_cast<CGridObject::BlockType>(nowFloor->objectTable[next.y][next.x]));

		// 画面から消す
		deleteObj->SetActive(false);
	}

	break;

	default:
		break;
	}
}

void StageScene::Undo(float _stageScale)
{
	// 一個前のUndoを参照する
	nNumUndo--;
	if (nNumUndo < 0)
	{
		nNumUndo = 0;
	}

	// 更新するテーブル
	GridTable* updateTable = nowFloor;
	// 更新するオブジェクトのリスト
	std::vector<CGridObject*>& updateObjList = vStageObj;
	// 前にいた階数のグリッドテーブルを更新する
	const short& o_floorNum = floorUndo[nNumUndo].old_Floor;
	switch (o_floorNum)
	{
	case 1:

		break;
	case 2:
		updateTable = secondFloor;
		updateObjList = secondFStgObj;
		break;
	case 3:
		updateTable = thirdFloor;
		updateObjList = thirdFStgObj;
		break;

	default:	// エラー
		MessageBoxA(NULL, "Undo関数でold_Floorが1～3階の範囲でありません", "エラー", MB_ICONERROR | MB_OK);
		break;
	}

	// １つずつ入れていく
	for (int i = 0; i < stageSquare.y; i++)
	{
		for (int j = 0; j < stageSquare.x; j++)
		{
			// 情報を入れる
			updateTable->objectTable[i][j] =
				floorUndo[nNumUndo].objectTable[o_floorNum - 1][i][j];
		}
	}
	// 入れた階層のオブジェクトを作る
	CreateStage(*updateTable, updateObjList);

	// 現在の階層のテーブル、オブジェクトに設定する
	nowFloor = updateTable;
	vStageObj = updateObjList;

	// 今の階層と前の階層が違うなら今いる階層も入れなおす
	if (nowFloorNum != o_floorNum)
	{
		switch (nowFloorNum)
		{
		case 1:
			updateTable = oneFloor;
			updateObjList = oneFStgObj;
			break;
		case 2:
			updateTable = secondFloor;
			updateObjList = secondFStgObj;
			break;
		case 3:
			updateTable = thirdFloor;
			updateObjList = thirdFStgObj;
			break;

		default:
			MessageBoxA(NULL, "Undo関数でnowFloorNumが1～3階の範囲でありません", "エラー", MB_ICONERROR | MB_OK);
			break;
		}

		// １つずつ入れていく
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				// 情報を入れる
				updateTable->objectTable[i][j] =
					floorUndo[nNumUndo].objectTable[nowFloorNum - 1][i][j];
			}
		}
		// 入れた階層のオブジェクトを作る
		CreateStage(*updateTable, updateObjList);
	}
	// リスがいる階層を更新
	nowFloorNum = o_floorNum;

	FIELD_FLOOR beforeStage = floorUndo[nNumUndo];
	// プレイヤーに必要な情報を更新する
	UndoPlayerSet(beforeStage.dirUndo, beforeStage.calorieUndo, beforeStage.stateUndo);
}

void StageScene::UndoPlayerSet(const int& _dir, const int& _calorie,
	const Player::STATE& _state)
{
	player->SetGridTable(nowFloor);

	// 方向を設定
	player->SetDirection(_dir);


	CPlayerAnim::PATTERN animPattern;
	switch (static_cast<Player::DIRECTION>(_dir))
	{
	case Player::DIRECTION::DOWN:
	case Player::DIRECTION::EVERY:
		animPattern = CPlayerAnim::PATTERN::STAY_DOWN;
		break;

	case Player::DIRECTION::LEFT:
		animPattern = CPlayerAnim::PATTERN::STAY_LEFT;
		break;

	case Player::DIRECTION::RIGHT:
		animPattern = CPlayerAnim::PATTERN::STAY_RIGHT;
		break;

	case Player::DIRECTION::UP:
		animPattern = CPlayerAnim::PATTERN::STAY_UP;
		break;
	}

	// アニメーションの画像も反映させる
	player->GetmAnim()->SetPattern(static_cast<int>(animPattern));

	// カロリーを設定
	player->SetCalorie(_calorie);

	// 状態を変化させる
	player->ChangeState(_state);

}

void StageScene::Draw()
{
	Z_Sort(vStageObj);
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		(*it)->Draw();
	}
}

void StageScene::Z_Sort(std::vector<CGridObject*>& _sortList)
{
	std::sort(_sortList.begin(), _sortList.end(), [](CObject* a, CObject* b) {return (a->mTransform.pos.z > b->mTransform.pos.z); });
}

void StageScene::Init(const wchar_t* filePath, float _stageScale)
{
	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	D3D_CreateSquare({ 3,4 }, &playerBuffer);

	stageTextureHoll = NULL;

	// ステージの大きさを設定する
	stageScale = _stageScale;
	nNumProtein = 0;

	stage = new CLoadStage;
	//stageMake = new CStageMake();

	LoadData StageData = stage->LoadStage(filePath);

	stageSquare = { StageData.numX,StageData.numY };

	//	ワールド座標
	/*stagePos = stageMake->StagePos(StageData);*/

	// ここでグリッドテーブルを作成する　/////////////
	// 階層ごとのテーブルに入れていく ///////////////
	oneFloor = new GridTable({ StageData.numX, StageData.numY }, _stageScale);
	if (StageData.secondFloor.floorTable[0][0] != 0) //0が入っていれば作られてない　階層なし
	{
		secondFloor = new GridTable({ StageData.numX, StageData.numY }, _stageScale);
		if (StageData.thirdFloor.floorTable[0][0] != 0)
		{
			thirdFloor = new GridTable({ StageData.numX,StageData.numY }, _stageScale);
		}
	}
	else
	{
		secondFloor = nullptr;
		thirdFloor = nullptr;
	}

	//開始する階層
	int startfloor = 0;

	// ロードしたデータからグリッドテーブルに入れる
	for (int i = 0; i < StageData.numY; i++)
	{
		for (int j = 0; j < StageData.numX; j++)
		{
			// オブジェクトのカテゴリを取得する
			CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.oneFloor.floorTable[i][j]);
			CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

			// 床だったら
			if (bCate == CGridObject::Category::FLOOR)
			{
				// 床テーブルに入れて
				oneFloor->floorTable[i][j] = StageData.oneFloor.floorTable[i][j];
				// オブジェクトテーブルには何も置かない(99を入れてる)
				oneFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
			}
			// オブジェクト・アイテムなら
			else
			{
				//	オブジェクトテーブルに入れて
				oneFloor->objectTable[i][j] = StageData.oneFloor.floorTable[i][j];
				// 床テーブルには通常床を入れる
				oneFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
				//読み込んだ数字ごとに処理するモノ
				switch (static_cast<CGridObject::BlockType>(StageData.oneFloor.floorTable[i][j]))
				{
				case CGridObject::BlockType::START:
					startfloor = 1;
					nowFloor = oneFloor;
					break;
				case CGridObject::BlockType::PROTEIN:
					nNumProtein++;
					break;
				default:
					break;
				}
			}

			//２階があればテーブル作成
			if (secondFloor != nullptr)
			{
				CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.secondFloor.floorTable[i][j]);
				CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

				// 床だったら
				if (bCate == CGridObject::Category::FLOOR)
				{
					// 床テーブルに入れて
					secondFloor->floorTable[i][j] = StageData.secondFloor.floorTable[i][j];
					// オブジェクトテーブルには何も置かない(99を入れてる)
					secondFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
				}
				// オブジェクト・アイテムなら
				else
				{
					//	オブジェクトテーブルに入れて
					secondFloor->objectTable[i][j] = StageData.secondFloor.floorTable[i][j];
					// 床テーブルには通常床を入れる
					secondFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
					switch (static_cast<CGridObject::BlockType>(StageData.secondFloor.floorTable[i][j]))
					{
					case CGridObject::BlockType::START:
						startfloor = 2;
						nowFloor = secondFloor;
						break;
					case CGridObject::BlockType::PROTEIN:
						nNumProtein++;
						break;
					default:
						break;
					}
				}

				//３階があればテーブルを作成する
				if (thirdFloor != nullptr)
				{
					CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.thirdFloor.floorTable[i][j]);
					CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

					// 床だったら
					if (bCate == CGridObject::Category::FLOOR)
					{
						// 床テーブルに入れて
						thirdFloor->floorTable[i][j] = StageData.thirdFloor.floorTable[i][j];
						// オブジェクトテーブルには何も置かない(99を入れてる)
						thirdFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
					}
					// オブジェクト・アイテムなら
					else
					{
						//	オブジェクトテーブルに入れて
						thirdFloor->objectTable[i][j] = StageData.thirdFloor.floorTable[i][j];
						// 床テーブルには通常床を入れる
						thirdFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
						switch (static_cast<CGridObject::BlockType>(StageData.thirdFloor.floorTable[i][j]))
						{
						case CGridObject::BlockType::START:
							startfloor = 3;
							nowFloor = thirdFloor;
							break;
						case CGridObject::BlockType::PROTEIN:
							nNumProtein++;
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}

	nowFloorNum = startfloor;	// 1階から


	//ここでグリッドテーブルを作成する /////////////////////////////////////////

	// ステージを作成する
	CreateStage(*oneFloor, oneFStgObj);

	vStageObj = oneFStgObj;

	// 2階と3階が使われているなら
	if (secondFloor != nullptr)
	{
		CreateStage(*secondFloor, secondFStgObj);
		if (thirdFloor != nullptr)
		{
			CreateStage(*thirdFloor, thirdFStgObj);
		}
	}

	for (int k = 0; k < MAX_LAYER; k++)
	{
		if (k == 1 && secondFloor == nullptr)
		{
			break;
		}
		else if (k == 2 && thirdFloor == nullptr)
		{
			break;
		}

		for (int i = 0; i < StageData.numY; i++)
		{
			for (int j = 0; j < StageData.numX; j++)
			{
				floorUndo[0].floorTable[k][i][j] = oneFloor->floorTable[i][j];
				floorUndo[0].objectTable[k][i][j] = oneFloor->objectTable[i][j];
			}
		}
	}

	// プレイヤーの初期化を行う（ここで最初にどの方向に進むかを決めている）
	player->Init(nowFloor);

	floorUndo[0].playerUndo = player->GetGridPos();
	floorUndo[0].stateUndo = player->GetState();
	floorUndo[0].dirUndo = player->GetDirection();
	floorUndo[0].calorieUndo = player->GetCalorie();
	floorUndo[0].old_Floor = 1;
	Z_Sort(vStageObj);
}

void StageScene::CreateStage(const GridTable& _gridTable, std::vector<CGridObject*>& _settingList)
{

	// 解放する
	for (int i = 0; i < _settingList.size(); i++)
	{
		CLASS_DELETE(_settingList[i]);
	}
	_settingList.clear();

	// オブジェクトテーブル
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// 左端が0なら終わる　→　
		if (_gridTable.objectTable[i][0] == 0) break;

		// 一つづつ見ていく
		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// その行で初めて0が出たなら　→　ステージで使っていないところなら
			if (_gridTable.objectTable[i][0] == 0) break;

			// オブジェクト ////////////////////////////////////
			// オブジェクトを生成する
			CGridObject* objWork = nullptr;
			switch (static_cast<CGridObject::BlockType>(_gridTable.objectTable[i][j]))
			{
			case CGridObject::BlockType::WALL:
				objWork = new CWall(stageBuffer, stageTextureWall);
				break;

			case CGridObject::BlockType::CAKE:
				objWork = new CCake(stageBuffer, stageTextureCake);
				break;

			case CGridObject::BlockType::CASTELLA:
				objWork = new CCastella(stageBuffer, stageTextureCastella);
				break;

			case CGridObject::BlockType::BAUMHORIZONTAL:
				objWork = new CBaum(stageBuffer, stageTextureBaumkuchen_L);
				break;

			case CGridObject::BlockType::BAUMVERTICAL:
				objWork = new CBaum(stageBuffer, stageTextureBaumkuchen_R);
				break;

			case CGridObject::BlockType::COIN:
				objWork = new CCoin(stageBuffer, stageTextureCoin);
				break;

			case CGridObject::BlockType::GUMI:
				objWork = new CGumi(stageBuffer, stageTextureGumi);
				break;

			case CGridObject::BlockType::PROTEIN:
				objWork = new CProtein(stageBuffer, stageTextureProtein);
				break;

			case CGridObject::BlockType::CHILI:
				objWork = new CChili(stageBuffer, stageTextureChili);
				break;

			case CGridObject::BlockType::START:
				objWork = new Player(playerBuffer, NULL);
				// プレイヤーは触ることが多いのでメンバ変数として持っておく
				player = dynamic_cast<Player*>(objWork);
				break;

			case CGridObject::BlockType::GALL:
				objWork = new CGall(stageBuffer, stageTextureGallChest);
				break;

			default:
				break;

			}

			if (objWork != nullptr)	// オブジェクトを生成しているなら
			{
				// グリッド座標を持たせる
				objWork->SetGridPos(j, i);

				// 座標を設定
				CGridObject::BlockType b =
					static_cast<CGridObject::BlockType>(_gridTable.objectTable[i][j]);

				// ステージ全体の大きさを設定
				objWork->mTransform.scale = { stageScale, stageScale, 1 };
				// オブジェクトにその種類をもたせる
				objWork->SetBlookType(b);
				// オブジェクトにカテゴリーをもたせる
				objWork->SetCategory(CGridObject::TypeToCategory(b));

				objWork->mTransform.pos = oneFloor->GridToWorld({ j, i },
					b);
				// アイテムならここで影の設定する
				if (objWork->GetCategory() == CGridObject::Category::ITEM)
				{
					dynamic_cast<CItem*>(objWork)->InitItem(shadowTexture);
				}


				_settingList.push_back(objWork);
			}
			// オブジェクト /////////////////////////////////////

			// 床 ///////////////////////////////////////////////
			CGridObject* floorWork = nullptr;
			// 床を生成する
			switch (static_cast<CGridObject::BlockType>(_gridTable.floorTable[i][j]))
			{
			case CGridObject::BlockType::FLOOR:
				floorWork = new CFloor(stageBuffer, stageTextureFloor);
				if ((i + j) % 2 == 0)
				{
					floorWork->SetTexture(stageTextureFloor2);
				}
				break;

			case CGridObject::BlockType::HOLL:
				floorWork = new CHoll(stageBuffer, stageTextureHoll);
				break;


			case CGridObject::BlockType::WATAAME:
				floorWork = new CWataame(stageBuffer, stageTextureWataame);
				break;

			case CGridObject::BlockType::CHOCO:
				floorWork = new CChoco(stageBuffer, stageTextureChocolate);
				break;

			case CGridObject::BlockType::CHOCOCRACK:
				floorWork = new CChoco(stageBuffer, stageTextureChocolate);
				break;

			default:
				break;
			}
			// 床 //////////////////////////////////////////////////////////////////////

			if (floorWork != nullptr)
			{
				// グリッド座標を持たせる
				floorWork->SetGridPos(j, i);

				// 座標を設定
				CGridObject::BlockType b =
					static_cast<CGridObject::BlockType>(_gridTable.floorTable[i][j]);

				// ステージ全体の大きさを設定
				floorWork->mTransform.scale = { stageScale, stageScale, 1 };
				// オブジェクトにその種類をもたせる
				floorWork->SetBlookType(b);
				// 床カテゴリに設定する
				floorWork->SetCategory(CGridObject::Category::FLOOR);

				floorWork->mTransform.pos = oneFloor->GridToWorld({ j, i },
					b);
				// 配列に入れていく
				_settingList.push_back(floorWork);
			}

		}

	}
}

void StageScene::ChangeFloor(int _nextFloor)
{
	vStageObj.clear();
	switch (_nextFloor)
	{
	case 1:
		vStageObj = oneFStgObj;
		player->SetGridTable(oneFloor);
		break;
	case 2:
		vStageObj = secondFStgObj;
		player->SetGridTable(secondFloor);
		break;
	case 3:
		vStageObj = thirdFStgObj;
		player->SetGridTable(thirdFloor);
		break;
	default:
		break;
	}
}

CGridObject* StageScene::GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType)
{
	// リストの中から指定した座標　オブジェクトテーブルにあるもの
	auto itr = std::find_if(vStageObj.begin(), vStageObj.end(), [&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == _gridPos.x &&
				_obj->GetGridPos().y == _gridPos.y &&
				(_obj->GetBlookType() == _blockType));
		});

	return (*itr);
}

CGridObject* StageScene::GetStageFloor(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType)
{
	// リストの中から指定した座標　オブジェクトテーブルにあるもの
	auto itr = std::find_if(vStageObj.begin(), vStageObj.end(), [&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == _gridPos.x &&
				_obj->GetGridPos().y == _gridPos.y &&
				(_obj->GetBlookType() == _blockType));
		});

	return (*itr);
}
