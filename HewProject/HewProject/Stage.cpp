#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Stage.h"
#include "CSceneManager.h"
#include "Ckcal_gauge.h"
#include"Player.h"

Stage::Stage(const wchar_t* _csvPath)
{
	stage = new StageScene(NULL, NULL);
	stage->Init(_csvPath, 3);

	dbgFloorTable = new DebugTable(stage->GetNowFloor(),true);
	dbgObjTable = new DebugTable(stage->GetNowFloor(), false);

	gauge = new Ckcal_gauge();
}

void Stage::Update()
{
	stage->Update();
	gauge->SetKcal(stage->GetPlayer()->GetCalorie());
}

void Stage::LateUpdate()
{
}

void Stage::Draw()
{
	stage->Draw();
	dbgFloorTable->Draw();
	dbgObjTable->Draw();
	gauge->Draw();

}

Stage::~Stage()
{
	CLASS_DELETE(stage);
	CLASS_DELETE(gauge);
	CLASS_DELETE(dbgFloorTable);
	CLASS_DELETE(dbgObjTable);
}
