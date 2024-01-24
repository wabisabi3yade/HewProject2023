#include "Stage.h"
#include "CSceneManager.h"
#include "Ckcal_gauge.h"
#include"Player.h"
#include"CDirectWrite.h"

Stage::Stage(const wchar_t* _csvPath)
{
	stage = new StageScene(NULL, NULL);
	stage->Init(_csvPath, 3);

	if (isDirectWriteUse)
	{
		dbgFloorTable = new DebugTable(stage->GetNowFloor(), true);
		dbgObjTable = new DebugTable(stage->GetNowFloor(), false);
		gauge = new Ckcal_gauge();
	}	
}

void Stage::Update()
{
	stage->Update();
	if (isDirectWriteUse)
	{
		gauge->SetKcal(stage->GetPlayer()->GetCalorie());

	}
}

void Stage::LateUpdate()
{
}

void Stage::Draw()
{
	stage->Draw();
	if (isDirectWriteUse)
	{
		dbgFloorTable->Draw();
		dbgObjTable->Draw();
		gauge->Draw();

		std::string canMoveDirCheck;
		bool* canmove = stage->GetPlayer()->GetCanMoveDir();
		if (canmove[0] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}
		if (canmove[1] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}
		if (canmove[2] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}
		if (canmove[3] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}


		Write->SetFont(Font::HG_Gyosyo, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ja-jp", DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Green));
		Write->DrawString(canMoveDirCheck, DirectX::XMFLOAT2(30, 10), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
}

Stage::~Stage()
{
	CLASS_DELETE(stage);
	CLASS_DELETE(gauge);
	CLASS_DELETE(dbgFloorTable);
	CLASS_DELETE(dbgObjTable);
}
