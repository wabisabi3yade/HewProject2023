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
	SAFE_RELEASE(stageTexture)
		SAFE_RELEASE(stageTexture2)

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
	D3D_LoadTexture(L"asset/mizuno/floor_y (1).png", &stageTexture);

	D3D_LoadTexture(L"asset/mizuno/floor_b.png", &stageTexture2);

	stage = new CLoadStage;
	stageMake = new CStageMake;

	std::vector<LoadData> StageData = stage->LoadStage(L"asset/mizuno/Stage.csv");

	stagePos = stageMake->StagePos(StageData, 13);

	StageBlockNum = stageMake->GetStageNum();
	float kariX = 16.0f / 2.0f;
	int stageNum = 0;
	for (auto& Stage : stagePos)
	{

		CGridObject* stageObj = new CGridObject(stageBuffer, stageTexture);

		stageObj->SetGridPos((const int)Stage.pos.x, (const int)Stage.pos.y);
		int stageposX = (int)Stage.pos.x;
		//°‚Ì‰æ‘œƒZƒbƒg‚Ìˆ—
		switch (Stage.blockType)
		{
			default:
			break;
		}
		if ((stageposX % 13) == 0)
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
		}



		vStageObj.push_back(stageObj);
		stageNum++;
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
