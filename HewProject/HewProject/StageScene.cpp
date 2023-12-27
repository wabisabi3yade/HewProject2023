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
#include "Player.h"

#define ISOME_FLOOR_SUBPOSY (3.6f)	// アイソメでの隣床のY座標の差（スケールを割る）
#define PLAYER dynamic_cast<Player*>(player)	// わざわざ書くのめんどくさい

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	oneFloor.FloorNum = 1;
	secondFloor.FloorNum = 2;
	thirdFloor.FloorNum = 3;

	PlayerState = 0;
}

StageScene::~StageScene()
{
	CLASS_DELETE(stageObj);

	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(playerBuffer);

	SAFE_RELEASE(stageTextureFloor);
	SAFE_RELEASE(stageTextureFloor2);
	SAFE_RELEASE(stageTextureBaumkuchen);
	SAFE_RELEASE(stageTextureCake);
	SAFE_RELEASE(stageTextureCastella);
	SAFE_RELEASE(stageTextureChili);
	SAFE_RELEASE(stageTextureChocolate);
	SAFE_RELEASE(stageTextureCoin);
	SAFE_RELEASE(stageTextureGallChest);
	SAFE_RELEASE(stageTextureGumi);
	SAFE_RELEASE(stageTextureProtein);
	SAFE_RELEASE(stageTextureWall);
	SAFE_RELEASE(stageTextureWataame);
	SAFE_RELEASE(playerTexture);

	CLASS_DELETE(stageMake);
	CLASS_DELETE(stage);
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
}

void StageScene::Update()
{
	player->mTransform.pos;

	PlayerMove();
	PLAYER->Update();
	if (gInput->GetKeyTrigger(VK_BACK))
	{
		PlayerState++;
		if (PlayerState == 4)
			PlayerState = 0;
	}

	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		(*it)->Update();
	}
}

void StageScene::PlayerMove()
{
	switch (PlayerState)
	{
	case 0:
		PlayerNomalMove();
		break;
	case 1:
		PlayerFatMove();
		break;
	case 2:
		PlayerSkinnyMove();
		break;
	case 3:
		PlayerMachoMove();
		break;
	default:
		break;
	}
}

void StageScene::PlayerNomalMove()
{
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 0 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 2 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 3 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 5 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 13) &&
				PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
			{
				playerGridPos.x += 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((playerGridPos.x != 0 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 2 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 3 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 5 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 13) && PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT)
			{
				playerGridPos.x -= 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 0 && oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 2 &&
				oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 3 && oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 5 &&
				oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 13) && PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
			{
				playerGridPos.y -= 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 0 && oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 2 &&
				oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 3 && oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 5 &&
				oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 13)
				&& PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
			{
				playerGridPos.y += 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
	}
}

void StageScene::PlayerFatMove()
{
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 0 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 2 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 3 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 13) &&
				PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
			{
				playerGridPos.x += 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] == 5)
				{
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
						{
							if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 2] == (int)CStageMake::BlockType::HOLL)
							{
								CGrid::GRID_XY xy = playerGridPos;
								xy.x += 1;
								Vector3 v = (GridToPos(xy, CStageMake::BlockType::CASTELLA));
								(*it)->mTransform.pos = v;
								oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							}
						}
					}
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((playerGridPos.x != 0 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 2 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 3 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 13) && PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT)
			{
				playerGridPos.x -= 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] == 5)
				{
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
						{
							if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 2] == (int)CStageMake::BlockType::HOLL)
							{
								CGrid::GRID_XY xy = playerGridPos;
								xy.x -= 1;
								Vector3 v = (GridToPos(xy, CStageMake::BlockType::CASTELLA));
								(*it)->mTransform.pos = v;
								oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							}
						}
					}
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 0 && oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 2 &&
				oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 3 &&
				oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 13) && PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
			{
				playerGridPos.y -= 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] == 5)
				{
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
						{
							if (oneFloor.gridTable[playerGridPos.y-2][playerGridPos.x] == (int)CStageMake::BlockType::HOLL)
							{
								CGrid::GRID_XY xy = playerGridPos;
								xy.y -= 1;
								Vector3 v = (GridToPos(xy, CStageMake::BlockType::CASTELLA));
								(*it)->mTransform.pos = v;
								oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							}
						}
					}
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 0 && oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 2 &&
				oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 3 &&
				oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 13)
				&& PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
			{
				playerGridPos.y += 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] == 5)
				{
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
						{
							if (oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] == (int)CStageMake::BlockType::HOLL)
							{
								CGrid::GRID_XY xy = playerGridPos;
								xy.y += 1;
								Vector3 v = (GridToPos(xy, CStageMake::BlockType::FLOOR));
								(*it)->mTransform.pos = v;
								oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							}
						}
					}
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
	}

}

void StageScene::PlayerSkinnyMove()
{
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 0 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 2 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 3 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 5 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 13) &&
				PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
			{
				playerGridPos.x += 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] != 6)
				{
					playerGridPos.x += 1;
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((playerGridPos.x != 0 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 2 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 3 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 5 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 13) && PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT)
			{
				playerGridPos.x -= 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] != 6)
				{
					playerGridPos.x -= 1;
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 0 && oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 2 &&
				oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 3 && oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 5 &&
				oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 13) && PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
			{
				playerGridPos.y -= 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] != 6)
				{
					playerGridPos.y -= 1;
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 0 && oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 2 &&
				oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 3 && oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 5 &&
				oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 13)
				&& PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
			{
				playerGridPos.y += 1;
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x] != 6)
				{
					playerGridPos.y += 1;
				}
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
	}

}

void StageScene::PlayerMachoMove()
{

	//マッチョ時壁のテクスチャなくすなり南下する
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 0 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 3 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 5) &&
				PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
			{
				playerGridPos.x += 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((playerGridPos.x != 0 && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 3 &&
				oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 5) &&
				PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT)
			{
				playerGridPos.x -= 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 0 &&
				oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 3 && oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 5) &&
				PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
			{
				playerGridPos.y -= 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}

		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			if ((oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 0 &&
				oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 3 && oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 5) &&
				PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
			{
				playerGridPos.y += 1;
				Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
				PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
				PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
			}
		}
	}

}

void StageScene::SettingPlayerDir()
{
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
	/*D3D_CreateSquare({ 3,4 }, &playerBuffer);*/

	D3D_LoadTexture(L"asset/mizuno/floor_y (1).png", &stageTextureFloor);
	D3D_LoadTexture(L"asset/mizuno/floor_g.png", &stageTextureFloor2);
	D3D_LoadTexture(L"asset/hashimoto/Baumkuchen.png", &stageTextureBaumkuchen);
	D3D_LoadTexture(L"asset/hashimoto/Cake.png", &stageTextureCake);
	D3D_LoadTexture(L"asset/hashimoto/Castella.png", &stageTextureCastella);
	D3D_LoadTexture(L"asset/hashimoto/Chili.png", &stageTextureChili);
	D3D_LoadTexture(L"asset/hashimoto/Chocolate.png", &stageTextureChocolate);
	D3D_LoadTexture(L"asset/hashimoto/Coin.png", &stageTextureCoin);
	D3D_LoadTexture(L"asset/hashimoto/GallChest.png", &stageTextureGallChest);
	D3D_LoadTexture(L"asset/hashimoto/Gumi.png", &stageTextureGumi);
	D3D_LoadTexture(L"asset/hashimoto/Protein.png", &stageTextureProtein);
	D3D_LoadTexture(L"asset/hashimoto/Wall.png", &stageTextureWall);
	D3D_LoadTexture(L"asset/hashimoto/Wataame.png", &stageTextureWataame);
	D3D_LoadTexture(L"asset/hashimoto/N_Walk01_Back.png", &playerTexture);

	stage = new CLoadStage;
	stageMake = new CStageMake;

	LoadData StageData = stage->LoadStage(filePath);

	//	ワールド座標
	stagePos = stageMake->StagePos(StageData);

	// ここでグリッドテーブルを作成する　/////////////
	oneFloor.isUse = true;

	// ステージの大きさ
	stageScale = { _stageScale,_stageScale,1.0f };

	// [0,0]の床の座標
	Offset_X = -stageScale.x * (StageData.numX - 1) / 2.0f;
	// ↓要調整
	Offset_Y = -stageScale.y / 2.0f;	// 床なので少し下に下げる

   // 行
	for (int i = 0; i < StageData.numY; i++)
	{
		// 列
		for (int j = 0; j < StageData.numX; j++)
		{
			// グリッドテーブルに一つずつデータを入れていく
			oneFloor.gridTable[i][j] = StageData.data[i * StageData.numX + j];

			// 最初に床の座標を求める
			Vector3 floorPos = Vector3::zero;
			floorPos.x = Offset_X + (i + j) * (stageScale.x / 2.0f);
			floorPos.y = Offset_Y + (j - i) * stageScale.y / ISOME_FLOOR_SUBPOSY;
			floorPos.z = floorPos.y * 0.01f;

			// 床からアイテムまでの距離（床のスケールに掛けることで調整する）
			float disTimes = 0;

			stageObj = nullptr;

			//床の画像セットの処理
			switch (oneFloor.gridTable[i][j])
			{
			case CStageMake::BlockType::FLOOR:
				//stageObj = new CFloor(stageBuffer, stageTextureFloor);
				//if ((i + j) % 2 == 0)
				//{
				//	stageObj->SetTexture(stageTextureFloor2);
				//}
				//stageObj->mTransform.pos = floorPos;
				//stageObj->CheckFloor();
				break;

			case CStageMake::BlockType::WALL:
				stageObj = new CWall(stageBuffer, stageTextureWall);
				stageObj->SetBlookType((int)CStageMake::BlockType::WALL);
				disTimes = 0.455f;
				break;

			case CStageMake::BlockType::HOLL:
				stageObj = new CHoll(stageBuffer, NULL);
				stageObj->SetBlookType((int)CStageMake::BlockType::HOLL);
				break;

			case CStageMake::BlockType::CAKE:
				stageObj = new CCake(stageBuffer, stageTextureCake);
				stageObj->SetBlookType((int)CStageMake::BlockType::CAKE);
				disTimes = 0.7f;
				break;

			case CStageMake::BlockType::CASTELLA:
				stageObj = new CCastella(stageBuffer, stageTextureCastella);
				stageObj->SetBlookType((int)CStageMake::BlockType::CASTELLA);
				disTimes = 0.455f;
				break;

			case CStageMake::BlockType::BAUM:
				stageObj = new CBaum(stageBuffer, stageTextureBaumkuchen);
				stageObj->SetBlookType((int)CStageMake::BlockType::BAUM);
				disTimes = 0.455f;
				break;

			case CStageMake::BlockType::COIN:
				stageObj = new CCoin(stageBuffer, stageTextureCoin);
				stageObj->SetBlookType((int)CStageMake::BlockType::COIN);
				disTimes = 0.455f;
				break;
			case CStageMake::BlockType::WATAAME:
				stageObj = new CWataame(stageBuffer, stageTextureWataame);
				stageObj->SetBlookType((int)CStageMake::BlockType::WATAAME);
				break;

			case CStageMake::BlockType::CHOCO:
				stageObj = new CChoco(stageBuffer, stageTextureChocolate);
				stageObj->SetBlookType((int)CStageMake::BlockType::CHOCO);
				break;

			case CStageMake::BlockType::GUMI:
				stageObj = new CGumi(stageBuffer, stageTextureGumi);
				stageObj->SetBlookType((int)CStageMake::BlockType::GUMI);
				disTimes = 0.455f;
				break;

			case CStageMake::BlockType::PROTEIN:
				stageObj = new CProtein(stageBuffer, stageTextureProtein);
				stageObj->SetBlookType((int)CStageMake::BlockType::PROTEIN);
				disTimes = 0.7f;
				break;

			case CStageMake::BlockType::START:
				player = new Player(stageBuffer, playerTexture);
				player->mTransform.pos = floorPos;
				player->mTransform.pos.y += stageScale.y * 0.5f;
				player->mTransform.pos.z -= 0.5f;
				player->mTransform.scale = stageScale;
				player->SetGridPos(j, i);
				vStageObj.push_back(player);
				break;

			case CStageMake::BlockType::GALL:
				stageObj = new CGall(stageBuffer, stageTextureGallChest);
				stageObj->SetBlookType((int)CStageMake::BlockType::GALL);
				disTimes = 0.55f;
				break;

			default:
				break;
			}

			// ここまでにオブジェクトが作成しているなら（床以外）
			if (stageObj != nullptr)
			{
				// ステージ全体の大きさを設定
				stageObj->mTransform.scale = stageScale;
				// 座標を設定
				stageObj->mTransform.pos = floorPos;
				stageObj->mTransform.pos.y += stageScale.y * disTimes;
				stageObj->mTransform.pos.z -= 0.5f;
				// オブジェクトをリストに入れる
				vStageObj.push_back(stageObj);
			}

			// 床がいらないオブジェクトは次のループに進める
			if (oneFloor.gridTable[i][j] == CStageMake::BlockType::CHOCO) continue;
			if (oneFloor.gridTable[i][j] == CStageMake::BlockType::WATAAME) continue;
			if (oneFloor.gridTable[i][j] == CStageMake::BlockType::HOLL) continue;

			// 床を作成
			CGridObject* floorObj = new CFloor(stageBuffer, stageTextureFloor);
			if ((i + j) % 2 == 0)
			{
				floorObj->SetTexture(stageTextureFloor2);
			}
			// パラメータ設定
			floorObj->SetBlookType((int)CStageMake::BlockType::FLOOR);
			floorObj->mTransform.pos = floorPos;
			floorObj->mTransform.scale = stageScale;

			vStageObj.push_back(floorObj);
		}
	}

	Z_Sort(vStageObj);
}

Vector3 StageScene::GetGridToPos(CGrid::GRID_XY _gridXY)
{
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		if ((*it)->GetGridPos().x == _gridXY.x && (*it)->GetGridPos().y == _gridXY.y && (*it)->GetBlookType() == 2)
		{
			return (*it)->mTransform.pos;
		}
	}
	return Vector3();
}

Vector3 StageScene::GridToPos(CGrid::GRID_XY _gridXY, CStageMake::BlockType _type)
{
	float disTimes = 0.0f;
	switch (_type)
	{
	case CStageMake::FLOOR:
	{

		Vector3 floorPos = Vector3::zero;
		floorPos.x = Offset_X + (_gridXY.y + _gridXY.x) * (stageScale.x / 2.0f);
		floorPos.y = Offset_Y + (_gridXY.x - _gridXY.y) * stageScale.y / ISOME_FLOOR_SUBPOSY;
		floorPos.z = floorPos.y * 0.01f;
		return floorPos;
	}
		break;
	case CStageMake::WALL:
	case CStageMake::CASTELLA:
	case CStageMake::BAUM:
	case CStageMake::COIN:
	case CStageMake::GUMI:
		disTimes = 0.455f;

		break;

	case CStageMake::CAKE:
	case CStageMake::PROTEIN:
		disTimes = 0.7f;
		break;

	case CStageMake::START:
		disTimes = 0.5f;
		break;
	}

	Vector3 v;
	v.x = Offset_X + (_gridXY.y + _gridXY.x) * (stageScale.x / 2.0f);
	v.y = Offset_Y + (_gridXY.x - _gridXY.y) * stageScale.y / ISOME_FLOOR_SUBPOSY
		+ stageScale.y * disTimes;
	v.z = (Offset_Y + (_gridXY.x - _gridXY.y) * stageScale.y / ISOME_FLOOR_SUBPOSY) * 0.01f - 0.5f;

	return v;
}