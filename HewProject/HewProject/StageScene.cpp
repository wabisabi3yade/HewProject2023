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
#include"CCannon.h"
//#include "Player.h"
#include "GridTable.h"
#include "TextureFactory.h"

#define PLAYER dynamic_cast<Player*>(player)	// わざわざ書くのめんどくさい

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	nNumProtein = 0;

	startFloor = 0;

	changeflag = false;

	FloorOnlyMap = false;

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
	stageTextureChocolateClack = texFactory->Fetch(L"asset/Stage/ChocoClack.png");
	stageTextureCake = texFactory->Fetch(L"asset/Item/Cake.png");
	stageTextureChili = texFactory->Fetch(L"asset/Item/Chili.png");
	stageTextureCoin = texFactory->Fetch(L"asset/Item/Coin.png");
	stageTextureGallChest = texFactory->Fetch(L"asset/Stage/GallChest.png");
	stageTextureGumi = texFactory->Fetch(L"asset/Stage/Gumi.png");
	stageTextureProtein = texFactory->Fetch(L"asset/Item/Protein.png");
	/*playerTexture = texFactory->Fetch(L"asset/Stage/floor_y.png");*/
	shadowTexture = texFactory->Fetch(L"asset/Item/shadow.png");
	stageTextureArrow = texFactory->Fetch(L"asset/UI/Arrow.png");
	stageTextureCannon[0] = texFactory->Fetch(L"asset/Stage/Canon_RightLeft.png");
	stageTextureCannon[1] = texFactory->Fetch(L"asset/Stage/Canon_UpDown.png");

}

// テクスチャは解放しない
StageScene::~StageScene()
{
	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(playerBuffer);

	CLASS_DELETE(stage);

	for (int i = 0; i < oneFStgObj.size(); i++)
	{
		CLASS_DELETE(oneFStgObj[i]);
	}
	oneFStgObj.clear();

	for (int i = 0; i < secondFStgObj.size(); i++)
	{
		CLASS_DELETE(secondFStgObj[i]);
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
	for (auto i : *vStageObj)
	{
		i->Update();
	}

	StageMove();

	if (gInput->GetKeyTrigger(VK_BACK))
	{
		Undo(stageScale);
	}

	/// 
	/// 階層変更している
	/// 

	if (player->GetPlayerMove()->GetisLoolMap() == true)
	{
		InputManager* input = InputManager::GetInstance();

		if (input->GetInputTrigger(InputType::L_BUTTON))
		{
			if (lockStageMap != nMaxFloor)
			{
				lockStageMap++;
			}
			if (lockStageMap == nowFloorNum)
			{
				//lockStageMap++;
			}
		}
		else if (input->GetInputTrigger(InputType::R_BUTTON))
		{

			if (lockStageMap != 1)
			{
				lockStageMap--;
			}
			if (lockStageMap == nowFloorNum)
			{
				//lockStageMap--;
			}
		}
		else if (input->GetInputTrigger(InputType::CANCEL))
		{
			player->GetPlayerMove()->CameraEnd();
		}
		else if (input->GetInputTrigger(InputType::OPTION))
		{
			FloorOnlyMap = !FloorOnlyMap;
		}


	}
	if (player->GetPlayerMove()->GetIncannon() && !cannonMove)
	{
		InCanonInput();
	}
	// 動いているときと動き終わった瞬間だけ
	if (player->GetPlayerMove()->GetIsMoving() || player->GetPlayerMove()->GetIsMoveTrigger())
	{
		// グリッドテーブルを更新する
		TableUpdate();
	}

	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{
		UndoTableUpdate();
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
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CAKE)
		{
			CCake* cakeObj = dynamic_cast<CCake*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			cakeObj->BlowOff(player->GetDirection());
		}

		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CHILI)
		{
			CChili* chiliObj = dynamic_cast<CChili*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			chiliObj->BlowOff(player->GetDirection());
		}

		if (player->GetPlayerMove()->CheckNowFloorType() == CGridObject::BlockType::WATAAME)
		{
			CWataame* wataameObj = dynamic_cast<CWataame*>(GetStageObject(player->GetGridPos(), CGridObject::BlockType::WATAAME));
			wataameObj->Melt();

			//for (auto it = vStageObj.begin(); it != vStageObj.end();) {
			//	// 条件一致した要素を削除する
			//	if (*it == wataameObj) {
			//		// 削除された要素の次を指すイテレータが返される。
			//		it = vStageObj.erase(it);
			//	}
			//	// 要素削除をしない場合に、イテレータを進める
			//	else {
			//		++it;
			//	}
			//}


			// ↓ここで穴のオブジェクトをnewしてvstageObjにpushbackする

			CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
			hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetGridPos()));
			hollObj->SetBlookType(CGridObject::BlockType::HOLL);
			hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
			vStageObj->push_back(hollObj);

		}


	}

	// プレイヤーが動き終えると
	if (player->GetPlayerMove()->GetIsWalkEnd())
	{
		if (player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCO ||
			player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCOCRACK)
		{
			CChoco* chocoObj = dynamic_cast<CChoco*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextFloorType())));
			if (player->GetState() != Player::STATE::THIN)
			{
				if (chocoObj->GetBlookType() == CGridObject::BlockType::CHOCOCRACK)
				{
					CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
					hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
					hollObj->SetBlookType(CGridObject::BlockType::HOLL);
					hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
					vStageObj->push_back(hollObj);
					player->GetPlayerMove()->FallStart();
				}
				chocoObj->CRACK();
				chocoObj->SetTexture(stageTextureChocolateClack);
			}
			if (player->GetState() == Player::STATE::FAT || player->GetState() == Player::STATE::MUSCLE)
			{
				chocoObj->CRACK();
				CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
				hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
				hollObj->SetBlookType(CGridObject::BlockType::HOLL);
				hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
				vStageObj->push_back(hollObj);
				player->GetPlayerMove()->FallStart();
			}
		}
		if (player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::GUMI)
		{
			player->GetPlayerMove()->RiseStart();
		}

		// アイテムがあるならそれを画面から消す
		ItemDelete();
	}


	if (player->GetPlayerMove()->GetCannonMoveStartTrigger())
	{
		//player->dotween->DelayedCall(CANNONMOVE_TIME, [&]()
		//	{
		//		ItemDelete();
		//	});
		CGridObject::BlockType type = player->GetPlayerMove()->CheckNextObjectType();
		switch (type)
		{
		case CGridObject::BlockType::WALL:
		{

			CWall* wallObj = dynamic_cast<CWall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), type));
			wallObj->Break(0.0f);
			break;
		}
		case CGridObject::BlockType::CAKE:
		{
			CCake* cakeObj = dynamic_cast<CCake*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), type));
			CGrid::GRID_XY deletePos = player->GetPlayerMove()->GetNextGridPos();
			cakeObj->dotween->DelayedCall(CANNONMOVE_TIME, [&, cakeObj, deletePos]()
				{
					cakeObj->BlowOff(player->GetDirection());
					cakeObj->dotween->OnComplete([&, cakeObj, deletePos]()
						{
							CannonItemDelete(deletePos, cakeObj->GetBlookType());
						});

				});
			break;
		}
		case CGridObject::BlockType::CASTELLA:
			break;
		case CGridObject::BlockType::COIN:
		{
			CCoin* coinObj = dynamic_cast<CCoin*>(GetStageObject(player->GetGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNowMassType())));
			coinObj->BlowOff(player->GetDirection());
			coinObj->dotween->OnComplete([&]()
				{
					CannonItemDelete();
				});
			break;
		}
		case CGridObject::BlockType::PROTEIN:
		{
			CProtein* proObj = dynamic_cast<CProtein*>(GetStageObject(player->GetGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNowMassType())));
			proObj->BlowOff(player->GetDirection());
			CGrid::GRID_XY deletePos = player->GetGridPos();
			//nowFloor->objectTable[proObj->GetGridPos().y][proObj->GetGridPos().x] =static_cast<short> (CGridObject::BlockType::NONE);
			proObj->dotween->OnComplete([&, deletePos]()
				{
					CannonItemDelete(deletePos);
				});
			break;
		}
		case CGridObject::BlockType::CHILI:
		{
			CChili* chiliObj = dynamic_cast<CChili*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextMassType())));
			//chiliObj->BlowOff(player->GetDirection());
			CGrid::GRID_XY deletePos = player->GetPlayerMove()->GetNextGridPos();
			chiliObj->dotween->DelayedCall(CANNONMOVE_TIME, [&, chiliObj, deletePos]()
				{
					chiliObj->BlowOff(player->GetDirection());
					chiliObj->dotween->OnComplete([&, chiliObj, deletePos]()
						{
							CannonItemDelete(deletePos, chiliObj->GetBlookType());
						});

				});
			break;
		}
		default:
			break;
		}
	}
	if (player->GetFallTrriger() == true)
	{
		//player->SetNowFloor(player->GetNowFloor()-1);
		if (player->GetNowFloor() != 0)
		{
			ChangeFloor(player->GetNowFloor() - 1);
		}
	}

	if (player->GetRiseTrriger() == true)
	{
		if (player->GetNowFloor() != 4)
		{
			ChangeFloor(player->GetNowFloor() + 1);
			CGrid::GRID_XY playerNextGridXY = player->GetPlayerMove()->GetNextGridPos();
			auto itr = std::find_if(vStageObj->begin(), vStageObj->end(),
				[&, playerNextGridXY](CGridObject* _obj)
				{
					return (_obj->GetGridPos().x == playerNextGridXY.x && _obj->GetGridPos().y == playerNextGridXY.y &&
						_obj->GetBlookType() == CGridObject::BlockType::FLOOR);
				});
			CFloor* floor = static_cast<CFloor*>((*itr));
			floor->FloorBound();
		}
	}

	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{

		if (player->GetState() != Player::STATE::MUSCLE && nNumProtein <= 0)
		{
			player->ChangeState(Player::STATE::MUSCLE);
			player->mTransform.scale.y *= 1.5f;
		}
		// マッチョじゃないなら
		if (player->GetState() == Player::STATE::MUSCLE) return;
		// 動き終えたあとにカロリーが状態変わるようなら状態を変化させる
		Player::STATE nextState = Player::STATE::FAT;
		if (player->GetCalorie() <= THIN_CALOMAX)
		{
			nextState = Player::STATE::THIN;
		}
		else if (player->GetCalorie() <= NORMAL_CALOMAX)
		{
			nextState = Player::STATE::NORMAL;
		}

		if (player->GetState() != nextState)
			player->ChangeState(nextState);

	}

}

void StageScene::TableUpdate()
{
	// 一旦全て白紙にする
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// その行の最初が使われていないなら終わる
		if ((nowFloor)->floorTable[i][0] == 0) break;

		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// 列が使われていないなら
			if ((nowFloor)->floorTable[i][j] == 0) break;

			(nowFloor)->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
			(nowFloor)->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
		}
	}

	// 配列全て見る
	for (auto itr = vStageObj->begin(); itr != vStageObj->end(); itr++)
	{
		// そのオブジェクトが画面にないなら次に行く
		if (!(*itr)->GetActive()) continue;

		// グリッド座標取って
		CGrid::GRID_XY g = (*itr)->GetGridPos();
		// 今の階層のテーブルに更新する
		if ((*itr)->GetCategory() == CGridObject::Category::FLOOR)
		{
			(nowFloor)->floorTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
		else
		{
			(nowFloor)->objectTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
	}
	player->SetGridTable((nowFloor));
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

	Vector3 target = (nowFloor)->GridToWorld(targetGrid, CGridObject::BlockType::CASTELLA);

	/////////////////////////////////////////////////////////////////////

	// リストの中からプレイヤーの移送先座標と同じもの　かつ　カステラを探す
	auto itr = std::find_if(vStageObj->begin(), vStageObj->end(),
		[&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == next.x && _obj->GetGridPos().y == next.y &&
				_obj->GetBlookType() == CGridObject::BlockType::CASTELLA);
		});

	CCastella* castella = static_cast<CCastella*>((*itr));

	// 動かした先が穴なら
	if ((nowFloor)->floorTable[targetGrid.y][targetGrid.x] == static_cast<int>(CGridObject::BlockType::HOLL))
	{
		Vector3 floorPos = (nowFloor)->GridToWorld(targetGrid, CGridObject::BlockType::FLOOR);
		castella->Move(target, true, floorPos);
		castella->SetGridPos(targetGrid.x, targetGrid.y);

		// オブジェクトテーブルからカステラを消して
		(nowFloor)->objectTable[targetGrid.y][targetGrid.x] = static_cast<int>(CGridObject::BlockType::NONE);

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

void StageScene::InCanonInput()
{
	int isSelectDir = -1;
	InputManager* input = InputManager::GetInstance();
	Vector2 PadStick = input->GetMovement();
	if (PadStick.x > 0.0f && PadStick.y > 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::RIGHT);
	}
	else if (PadStick.x < 0.0f && PadStick.y < 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::LEFT);
		//player->mTransform.pos.x -= 0.3f;
	}
	else if (PadStick.x < 0.0f && PadStick.y > 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::UP);
		//player->mTransform.pos.y -= 0.3f;
		//player->mTransform.pos.x -= 5.0f;
	}
	else if (PadStick.x > 0.0f && PadStick.y < 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::DOWN);
	}

	CCannon* cannonObj = dynamic_cast<CCannon*>(GetStageFloor(player->GetGridPos(), CGridObject::BlockType::CANNON));
	bool* canMoveDir = cannonObj->GetCanMove();

	// 入力した大砲の方向で発射できるか見る
	for (int i = 0; i < isSelectDir; i++)
	{
		canMoveDir++;
	}
	// 発射出来ない方向なら　入力されていないなら　終了する
	if (!canMoveDir || isSelectDir == -1) return;


	//player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
	player->SetDirection(isSelectDir);
	cannonMove = true;
	// 右 or 左なら　大砲動かす
	if (isSelectDir == 2 || isSelectDir == 1)
	{
		cannonObj->SetTexture(stageTextureCannon[0]);
		dynamic_cast<CannonAnim*>(cannonObj->GetmAnim())->PlayTurn(isSelectDir);
		player->dotween->DelayedCall(0.9f, [&, isSelectDir, cannonObj]()
			{
				cannonObj->DirSelect(static_cast<Player::DIRECTION>(isSelectDir));

				player->dotween->DelayedCall(0.9f, [&, cannonObj, isSelectDir]()
					{
						player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
						player->GetPlayerMove()->CannonMoveStart();
						cannonMove = false;
						cannonObj->PlayReturn();
					});
			});
	}
	else
	{
		cannonObj->DirSelect(static_cast<Player::DIRECTION>(isSelectDir));

		player->dotween->DelayedCall(0.9f, [&, cannonObj, isSelectDir]()
			{
				player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
				player->GetPlayerMove()->CannonMoveStart();
				cannonMove = false;
				cannonObj->PlayReturn();
			});
	}




}

void StageScene::ItemDelete()
{
	CGrid::GRID_XY next = player->GetPlayerMove()->GetNextGridPos();

	CGridObject* deleteObj;	// 画面から消す予定のポインタがはいる

	switch (static_cast<CGridObject::BlockType>
		((nowFloor)->objectTable[next.y][next.x]))
	{
		// プレイヤーの位置にこのアイテムがあれば
	case CGridObject::BlockType::PROTEIN:
		nNumProtein--;
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::COIN:
	case CGridObject::BlockType::CHILI:
	{
		// リストの中からプレイヤーの座標と同じもの　かつ　床じゃない物を探す
		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, static_cast<CGridObject::BlockType>((nowFloor)->objectTable[next.y][next.x]));

		// 画面から消す
		deleteObj->SetActive(false);
	}

	break;

	default:
		break;
	}
}

void StageScene::CannonItemDelete(CGrid::GRID_XY _deletePos, CGridObject::BlockType _type)
{
	CGrid::GRID_XY next;
	if (_deletePos.x == -1 && _deletePos.y == -1)
	{
		next = player->GetGridPos();
	}
	else
	{
		next = _deletePos;
	}


	CGridObject* deleteObj;	// 画面から消す予定のポインタがはいる
	CGridObject::BlockType type;
	if (_type == CGridObject::BlockType::NONE)
	{
		type = static_cast<CGridObject::BlockType>((nowFloor)->objectTable[next.y][next.x]);
	}
	else
	{
		type = _type;
	}
	switch (type)
	{
		// プレイヤーの位置にこのアイテムがあれば
	case CGridObject::BlockType::PROTEIN:
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::COIN:
	case CGridObject::BlockType::CHILI:
	{
		// リストの中からプレイヤーの座標と同じもの　かつ　床じゃない物を探す
		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, type);

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
	if (player->GetPlayerMove()->GetIsMoving()) return;

	// 0より下に行くと
	nNumUndo--;
	if (nNumUndo < 0)
	{
		// まだ使われていないのなら
		if (floorUndo[UNDO_ARRAY_NUM - 1].objectTable[0][0][0] == 0)
		{
			MessageBoxA(NULL, "これ以上戻れません", "Undo", MB_ICONERROR | MB_OK);
			nNumUndo = 0;
			return;	// 抜ける
		}

		nNumUndo = UNDO_ARRAY_NUM - 1;
	}

	// 更新するテーブル
	GridTable* updateTable = nowFloor;
	// 更新するオブジェクトのリスト
	std::vector<CGridObject*>* updateObjList = vStageObj;
	// 前にいた階数のグリッドテーブルを更新する
	const short& o_floorNum = floorUndo[nNumUndo].old_Floor;

	// 階層を移動していないなら
	if (nowFloorNum == o_floorNum)
	{
		// １つずつ入れていく
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				// 情報を入れる
				updateTable->objectTable[i][j] =
					floorUndo[nNumUndo].objectTable[o_floorNum - 1][i][j];

				// 情報を入れる
				updateTable->floorTable[i][j] =
					floorUndo[nNumUndo].floorTable[o_floorNum - 1][i][j];
			}
		}
		// 入れた階層のオブジェクトを作る
		CreateStage(*updateTable, *updateObjList);
	}
	// 移動しているなら
	else
	{
		for (int loop = 0; loop < MAX_LAYER; loop++)
		{
			// 全ての階層を更新する
			switch (loop)
			{
			case 0:
				updateTable = oneFloor;
				updateObjList = &oneFStgObj;
				break;
			case 1:
				updateTable = secondFloor;
				updateObjList = &secondFStgObj;
				break;
			case 2:
				updateTable = thirdFloor;
				updateObjList = &thirdFStgObj;
				break;

			default:	// エラー
				MessageBoxA(NULL, "Undo関数でold_Floorが1～3階の範囲でありません", "エラー", MB_ICONERROR | MB_OK);
				break;
			}

			// 階層がこれ以上ないなら終わる
			if (updateTable == nullptr) break;

			// １つずつ入れていく
			for (int i = 0; i < stageSquare.y; i++)
			{
				for (int j = 0; j < stageSquare.x; j++)
				{
					// 情報を入れる
					updateTable->objectTable[i][j] =
						floorUndo[nNumUndo].objectTable[loop][i][j];
					// 情報を入れる
					updateTable->floorTable[i][j] =
						floorUndo[nNumUndo].floorTable[loop][i][j];
				}
			}
			// 入れた階層のオブジェクトを作る
			CreateStage(*updateTable, *updateObjList);
		}


	}

	// リスがいる階層を更新
	nowFloorNum = o_floorNum;
	// 更新する
	switch (floorUndo[nNumUndo].old_Floor)
	{
	case 1:
		vStageObj = &oneFStgObj;
		nowFloor = oneFloor;

		break;

	case 2:
		vStageObj = &secondFStgObj;
		nowFloor = secondFloor;
		break;

	case 3:
		vStageObj = &thirdFStgObj;
		nowFloor = thirdFloor;
		break;
	}
	player->SetNowFloor(floorUndo[nNumUndo].old_Floor);


	FIELD_FLOOR beforeStage = floorUndo[nNumUndo];
	// プレイヤーに必要な情報を更新する
	UndoPlayerSet(beforeStage.dirUndo, beforeStage.calorieUndo, beforeStage.stateUndo);

}

void StageScene::UndoTableUpdate()
{
	nNumUndo++;
	if (nNumUndo >= UNDO_ARRAY_NUM)
	{
		nNumUndo = 0;
	}

	for (int loop = 0; loop < MAX_LAYER; loop++)
	{
		GridTable* setTable = nullptr;

		switch (loop)
		{
		case 0:
			setTable = oneFloor;
			break;

		case 1:
			setTable = secondFloor;
			break;

		case 2:
			setTable = thirdFloor;
			break;
		}
		// これ以上階層がないなら終わる
		if (setTable == nullptr) break;

		// 今いる階層だけ更新
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				floorUndo[nNumUndo].floorTable[loop][i][j] = setTable->floorTable[i][j];
				floorUndo[nNumUndo].objectTable[loop][i][j] = setTable->objectTable[i][j];
			}
		}
	}

	floorUndo[nNumUndo].playerUndo = player->GetGridPos();
	floorUndo[nNumUndo].stateUndo = player->GetState();
	floorUndo[nNumUndo].dirUndo = player->GetDirection();
	floorUndo[nNumUndo].calorieUndo = player->GetCalorie();
	floorUndo[nNumUndo].old_Floor = nowFloorNum;
}

void StageScene::UndoPlayerSet(const int& _dir, const int& _calorie,
	const Player::STATE& _state)
{
	player->SetGridTable(nowFloor);


	GridTable* setNextTable = nullptr;
	switch (nowFloorNum)
	{
	case 1:
		break;

	case 2:
		setNextTable = oneFloor;
		break;

	case 3:
		setNextTable = secondFloor;
		break;
	}
	player->SetNextGridTable(setNextTable);

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

	// カロリーを設定
	player->SetCalorie(_calorie);



	// アニメーションの画像も反映させる
	player->GetmAnim()->SetPattern(static_cast<int>(animPattern));

	// 状態を変化させる
	player->ChangeState(_state);

}

void StageScene::Draw()
{
	Z_Sort(*vStageObj);

	if (player->GetPlayerMove()->GetisLoolMap() == false)
	{
		for (auto it : *vStageObj)
		{
			it->Draw();
		}
	}
	else {
		MapDraw();
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
		nMaxFloor = 2;
		if (StageData.thirdFloor.floorTable[0][0] != 0)
		{
			thirdFloor = new GridTable({ StageData.numX,StageData.numY }, _stageScale);
			nMaxFloor = 3;
		}
	}
	else
	{
		secondFloor = nullptr;
		thirdFloor = nullptr;
		nMaxFloor = 1;
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
	startFloor = startfloor;

	lockStageMap = startfloor;
	//ここでグリッドテーブルを作成する /////////////////////////////////////////

	// ステージを作成する
	CreateStage(*oneFloor, oneFStgObj);



	// 2階と3階が使われているなら
	if (secondFloor != nullptr)
	{
		CreateStage(*secondFloor, secondFStgObj);
		if (thirdFloor != nullptr)
		{
			CreateStage(*thirdFloor, thirdFStgObj);
		}
	}

	GridTable* setTable = oneFloor;
	for (int k = 0; k < MAX_LAYER; k++)
	{
		if (k == 1)
		{
			setTable = secondFloor;
		}
		else if (k == 2)
		{
			setTable = thirdFloor;
		}

		// 階層これ以上ないなら
		if (setTable == nullptr) break;

		for (int i = 0; i < StageData.numY; i++)
		{
			for (int j = 0; j < StageData.numX; j++)
			{
				floorReset.floorTable[k][i][j] = setTable->floorTable[i][j];
				floorReset.objectTable[k][i][j] = setTable->objectTable[i][j];
			}
		}
	}

	switch (startfloor)
	{
	case 1:
		vStageObj = &oneFStgObj;
		nowFloor = oneFloor;
		break;

	case 2:
		vStageObj = &secondFStgObj;
		nowFloor = secondFloor;
		player->SetNextGridTable(oneFloor);
		break;
	case 3:
		vStageObj = &thirdFStgObj;
		nowFloor = thirdFloor;
		player->SetNextGridTable(secondFloor);
		break;
	default:
		break;
	}

	// プレイヤーの初期化を行う（ここで最初にどの方向に進むかを決めている）
	player->Init(nowFloor);

	player->SetNowFloor(startfloor);

	floorReset.playerUndo = player->GetGridPos();
	floorReset.stateUndo = player->GetState();
	floorReset.dirUndo = player->GetDirection();
	floorReset.calorieUndo = player->GetCalorie();
	floorReset.old_Floor = nowFloorNum;

	// 最初のUndoに入れておく
	floorUndo[0] = floorReset;

	Z_Sort(*vStageObj);
	//ChangeFloor(nowFloorNum);
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
			case CGridObject::BlockType::CANNON:
				objWork = new CCannon(playerBuffer, stageTextureCannon[1], nowFloor);
				dynamic_cast<CCannon*>(objWork)->SetArrow(stageBuffer, stageTextureArrow);
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
				else if (objWork->GetBlookType() == CGridObject::BlockType::CANNON)
				{
					dynamic_cast<CCannon*>(objWork)->CheckCanMove(_gridTable);
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
				floorWork = new CChoco(stageBuffer, stageTextureChocolateClack);
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
	//for (int i = 0; i < stageSquare.y; i++)
	//{
	//	for (int j = 0; j < stageSquare.x; j++)
	//	{
	//		if (nowFloor->objectTable[i][j] == static_cast<short>(CGridObject::BlockType::START))
	//		{
	//			nowFloor->objectTable[i][j] = static_cast<short>(CGridObject::BlockType::NONE);
	//		}
	//	}
	//}
	//vStageObj->clear();
	//vStageObj->shrink_to_fit();

	auto removeItr = std::remove(vStageObj->begin(), vStageObj->end(), player);

	vStageObj->erase(removeItr, vStageObj->end());


	// 移動前の階層のテーブルのプレイヤーをNONEにする
	for (int i = 0; i < stageSquare.y; i++)
	{
		for (int j = 0; j < stageSquare.x; j++)
		{
			if (nowFloor->objectTable[i][j] == static_cast<int>(CGridObject::BlockType::START))
			{
				nowFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
			}
		}
	}

	player->risingMoveTrriger = false;
	player->fallMoveTrriger = false;



	switch (_nextFloor)
	{
	case 1:
		vStageObj = &oneFStgObj;
		vStageObj->push_back(player);
		nowFloor = oneFloor;
		nowFloorNum = 1;
		player->SetGridTable(oneFloor);
		break;
	case 2:
		vStageObj = &secondFStgObj;
		vStageObj->push_back(player);
		nowFloor = secondFloor;
		nowFloorNum = 2;
		player->SetGridTable(secondFloor);
		player->SetNextGridTable(oneFloor);
		break;
	case 3:
		vStageObj = &thirdFStgObj;
		vStageObj->push_back(player);
		nowFloor = thirdFloor;
		nowFloorNum = 3;
		player->SetGridTable(thirdFloor);
		player->SetNextGridTable(secondFloor);
		break;
	default:
		break;
	}
	player->SetNowFloor(nowFloorNum);

	Z_Sort(*vStageObj);
}

void StageScene::MapDraw()
{

	switch (lockStageMap)
	{
	case 1:
		Z_Sort(oneFStgObj);
		for (std::vector<CGridObject*>::iterator i = oneFStgObj.begin(); i != oneFStgObj.end(); i++)
		{
			if (FloorOnlyMap)
			{
				if ((*i)->GetCategory() == CGridObject::Category::FLOOR)
				{
					(*i)->Draw();
				}
			}
			else
			{
				(*i)->Draw();
			}
		}
		break;
	case 2:
		Z_Sort(secondFStgObj);
		for (std::vector<CGridObject*>::iterator j = secondFStgObj.begin(); j != secondFStgObj.end(); j++)
		{
			if (FloorOnlyMap)
			{
				if ((*j)->GetCategory() == CGridObject::Category::FLOOR)
				{
					(*j)->Draw();
				}
			}
			else
			{
				(*j)->Draw();
			}
		}
		break;
	case 3:
		Z_Sort(thirdFStgObj);
		for (std::vector<CGridObject*>::iterator thir = thirdFStgObj.begin(); thir < thirdFStgObj.end(); thir++)
		{
			if (FloorOnlyMap)
			{
				if ((*thir)->GetCategory() == CGridObject::Category::FLOOR)
				{
					(*thir)->Draw();
				}
			}
			else
			{
				(*thir)->Draw();
			}
		}
		break;
	default:
		break;
	}

}

CGridObject* StageScene::GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType)
{
	// リストの中から指定した座標　オブジェクトテーブルにあるもの
	auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
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
	auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == _gridPos.x &&
				_obj->GetGridPos().y == _gridPos.y &&
				(_obj->GetBlookType() == _blockType)) &&
				_obj->GetActive() == true;
		});

	return (*itr);
}

GridTable* StageScene::GetNowFloor() const
{
	return nowFloor;
}
