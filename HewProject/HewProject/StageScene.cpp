#include "StageScene.h"
#include<iostream>
#include<algorithm>


StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{


}

StageScene::~StageScene()
{
	SAFE_RELEASE(stageBuffer);
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

		CLASS_DELETE(stageMake);
	CLASS_DELETE(stage);
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}

}

void StageScene::Update()
{
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		(*it)->Update();
	}
}

void StageScene::Draw()
{
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		(*it)->Draw();
	}
}

void StageScene::Z_Sort(std::vector<CGridObject*>& _sortList)
{
	std::sort(_sortList.begin(), _sortList.end(), [](CObject* a, CObject* b) {return (a->mTransform.pos.z > b->mTransform.pos.z); });
}

void StageScene::Init()
{
	D3D_CreateSquare({ 1,1 }, &stageBuffer);
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

	stage = new CLoadStage;
	stageMake = new CStageMake;

	std::vector<LoadData> StageData = stage->LoadStage(L"asset/mizuno/Stage.csv");

	stagePos = stageMake->StagePos(StageData, 3);

	StageBlockNum = stageMake->GetStageNum();
	float kariX = 16.0f / 2.0f;
	int stageNum = 0;
	for (auto& Stage : stagePos)
	{
		CGridObject* stageObj = new CGridObject(stageBuffer, stageTextureFloor);
		if (stageNum % 2 == 0)
		{
			stageObj->SetTexture(stageTextureFloor2);
		}

		stageObj->SetGridPos((const int)Stage.pos.x, (const int)Stage.pos.y);
		int stageposX = (int)Stage.pos.x;
		//int stageType = (int)Stage.blockType;
		//床の画像セットの処理
		switch (Stage.blockType)
		{
		case CStageMake::BlockType::FLOOR:
			//stageObj->SetTexture(stageTextureFloor);
			break;
		case CStageMake::BlockType::WALL:
			stageObj->SetTexture(stageTextureWall);
			break;
		case CStageMake::BlockType::HOLL:
			stageObj->SetTexture(NULL);
			break;
		case CStageMake::BlockType::CAKE:
			stageObj->SetTexture(stageTextureCake);
			break;
		case CStageMake::BlockType::CASTELLA:
			stageObj->SetTexture(stageTextureCastella);
			break;
		case CStageMake::BlockType::BAUM:
			stageObj->SetTexture(stageTextureBaumkuchen);
			break;
		case CStageMake::BlockType::COIN:
			stageObj->SetTexture(stageTextureCoin);
			break;
		case CStageMake::BlockType::WATAAME:
			stageObj->SetTexture(stageTextureWataame);
			break;
		case CStageMake::BlockType::CHOCO:
			stageObj->SetTexture(stageTextureChocolate);
			break;
		case CStageMake::BlockType::GUMI:
			stageObj->SetTexture(stageTextureGumi);
			break;
		case CStageMake::BlockType::PROTEIN:
			stageObj->SetTexture(stageTextureProtein);
			break;
		case CStageMake::BlockType::START:
			//stageObj->SetTexture(stageTextureFloor);
			break;
		case CStageMake::BlockType::GALL:
			stageObj->SetTexture(stageTextureGallChest);
				break;
		default:
			break;
		}
		if ((stageposX % 3) == 0)
		{
			stageObj->mTransform.pos.x = -kariX + (stageObj->mTransform.scale.x / 2) + (stageObj->mTransform.scale.x / 2 * Stage.pos.y);
			stageObj->mTransform.pos.y = (stageObj->mTransform.scale.y * Stage.pos.y * -1.0f) + (0.03f * (Stage.pos.x + Stage.pos.y) * stageObj->mTransform.scale.y) - (stageObj->mTransform.scale.y / 2) + (stageObj->mTransform.scale.y / 2 * Stage.pos.y) - ((stageObj->mTransform.scale.y / 2) * (Stage.pos.y)) + ((stageObj->mTransform.scale.y / 2) * (Stage.pos.y)) + ((stageObj->mTransform.scale.y / 4) * (Stage.pos.y + 1)) - (0.1f * Stage.pos.y)/*+0.3f*/;
			if (stageObj->mTransform.pos.y < 0)
			{
				stageObj->mTransform.pos.z = stageObj->mTransform.pos.y * 0.01f;
			}
			else
			{
				stageObj->mTransform.pos.z = stageObj->mTransform.pos.y * 0.01f;
			}
			if (Stage.blockType == (int)CStageMake::BlockType::BAUM || Stage.blockType == (int)CStageMake::BlockType::CAKE || Stage.blockType == (int)CStageMake::BlockType::CASTELLA
				|| Stage.blockType == (int)CStageMake::BlockType::GALL || Stage.blockType == (int)CStageMake::BlockType::WALL || Stage.blockType == (int)CStageMake::BlockType::PROTEIN)
			{
				stageObj->mTransform.pos.y += stageObj->mTransform.scale.y / 2;
				if (Stage.blockType == (int)CStageMake::BlockType::CAKE || Stage.blockType == (int)CStageMake::BlockType::PROTEIN)
				{
					stageObj->mTransform.pos.y += stageObj->mTransform.scale.y / 4;
				}
				stageObj->mTransform.pos.z -= 0.01f;

			}
		}
		else
		{
			stageObj->mTransform.pos.x = -kariX + (stageObj->mTransform.scale.x / 2) + ((stageObj->mTransform.scale.x / 2) * (int)(stageposX + Stage.pos.y)) - 0.01f * Stage.pos.x;
			stageObj->mTransform.pos.y = (stageObj->mTransform.scale.y * Stage.pos.y * -1.0f) + (0.03f * (Stage.pos.x + Stage.pos.y) * stageObj->mTransform.scale.y) - (stageObj->mTransform.scale.y / 2) + (stageObj->mTransform.scale.y / 2 * Stage.pos.y) - ((stageObj->mTransform.scale.y / 2) * (Stage.pos.y)) + ((stageObj->mTransform.scale.y / 2) * (Stage.pos.y)) + ((stageObj->mTransform.scale.y / 4) * (Stage.pos.y + 1)) + ((stageObj->mTransform.scale.y / 4) * (Stage.pos.x)) - (0.1f * Stage.pos.y) /*+0.01f*Stagepos.pos.x*/;
			if (stageObj->mTransform.pos.y < 0)
			{
				stageObj->mTransform.pos.z = +stageObj->mTransform.pos.y * 0.01f;
			}
			else
			{
				stageObj->mTransform.pos.z = +stageObj->mTransform.pos.y * 0.01f;
			}
			if (Stage.blockType == (int)CStageMake::BlockType::BAUM || Stage.blockType == (int)CStageMake::BlockType::CAKE || Stage.blockType == (int)CStageMake::BlockType::CASTELLA
				|| Stage.blockType == (int)CStageMake::BlockType::GALL || Stage.blockType == (int)CStageMake::BlockType::PROTEIN || Stage.blockType == (int)CStageMake::BlockType::WALL)
			{
				//浮いてるもの
				stageObj->mTransform.pos.x += 0.05f;
				stageObj->mTransform.pos.y += stageObj->mTransform.scale.y / 2;
				if (Stage.blockType == (int)CStageMake::BlockType::CAKE || Stage.blockType == (int)CStageMake::BlockType::PROTEIN)
				{
					stageObj->mTransform.pos.y += stageObj->mTransform.scale.y / 4;
				}
				stageObj->mTransform.pos.z -= 0.01f;
			}
		}



		vStageObj.push_back(stageObj);
		//if (Stage.blockType == (int)CStageMake::BlockType::BAUM || Stage.blockType == (int)CStageMake::BlockType::CAKE || Stage.blockType == (int)CStageMake::BlockType::CASTELLA
		//	|| Stage.blockType == (int)CStageMake::BlockType::GALL || Stage.blockType == (int)CStageMake::BlockType::PROTEIN || Stage.blockType == (int)CStageMake::BlockType::WALL || Stage.blockType == (int)CStageMake::BlockType::START )
		//{

		//}
		//else
		//{
		//	stageNum++;

		//}
		if (Stage.blockType == CStageMake::BlockType::FLOOR)
		{
			stageNum++;
		}
	}
	Z_Sort(vStageObj);
}

Vector3 StageScene::GetGridToPos(CGrid::GRID_XY _gridXY)
{
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		if ((*it)->GetGridPos().x == _gridXY.x && (*it)->GetGridPos().y == _gridXY.y)
		{
			return (*it)->mTransform.pos;
		}
	}
	return Vector3();
}
