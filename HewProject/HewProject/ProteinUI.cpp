#include "ProteinUI.h"
#include "TextureFactory.h"

#define UI_OFFSETZ (0.0001f)	// UIのZ値差分

#define CIRCLE_OFFSETX (1.0f)	// 〇同士のX座標差分
#define CIRCLE_OFFSETY (0.7f)	// 棒から〇のY座標差分
#define PRO_SCALETIME (1.3f)	// 大きくなるまでの時間
ProteinUI::ProteinUI(const int& _proteinNum)
{
	// 全体の座標をここで設定
	mTransform.pos = {};

	TextureFactory* texFactory = TextureFactory::GetInstance();
	// このステージにあるプロテイン取得
	stageProMax = _proteinNum;

	D3D_CreateSquare({ 1,1 }, &buffer);
	D3DTEXTURE texWork;
	// 〇のUI
	texWork = texFactory->Fetch(L"asset/UI/Protein_Mark.png");
	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i] = new UI(buffer, texWork);
		proMark[i]->mTransform.scale = proScale;
	}

	// プロテイン
	texWork = texFactory->Fetch(L"asset/Item/Protein.png");
	for (int i = 0; i < stageProMax; i++)
	{
		protein[i] = new UI(buffer, texWork);
		protein[i]->mTransform.scale = proScale;
		protein[i]->MakeDotween();
	}

	// 下の棒
	texWork = texFactory->Fetch(L"asset/UI/Protein_Bar.png");
	bar = new UI(buffer, texWork);
	bar->mTransform.scale = { 3.0f, 0.2f, 1.0f };

	SetPosition(mTransform.pos);
}

ProteinUI::~ProteinUI()
{
	SAFE_RELEASE(buffer);

	for (int i = 0; i < stageProMax; i++)
	{
		CLASS_DELETE(proMark[i]);
	}
	for (int i = 0; i < stageProMax; i++)
	{
		CLASS_DELETE(protein[i]);
	}
	CLASS_DELETE(bar);
}

void ProteinUI::Update()
{
	for (int i = 0; i < stageProMax; i++)
	{
		protein[i]->Update();
	}
}

void ProteinUI::SetProtein(const int& _getProtein)
{
	if (_getProtein > stageProMax || _getProtein < 0)
	{
		MessageBoxA(NULL, "SetPritein関数の引数が範囲外です", "エラー", MB_ICONERROR | MB_OK);
		return;
	}

	// 取得数更新
	getProtein = _getProtein;

	short roop = 0;
	// 取得したプロテインのUI反映
	for (; roop < _getProtein; roop++)
	{
		// 〇は非表示
		proMark[roop]->SetActive(false);
		// プロテインは表示
		protein[roop]->SetActive(true);
		protein[roop]->mTransform.scale = proScale;
	}
	// 取得していないUI反映
	for (; roop < stageProMax; roop++)
	{
		proMark[roop]->SetActive(true);

		protein[roop]->SetActive(false);
	}
}

void ProteinUI::AddProtein()
{
	// プロテインを1つ取得
	getProtein++;

	// ステージにあるプロテインの数を超えたら
	if (getProtein > stageProMax)
	{
		MessageBoxA(NULL, "プロテインの取得数がステージにある\nプロテイン取得数を超えました", "AddProtein関数", MB_ICONERROR | MB_OK);
		// 数を合わせる
		getProtein = stageProMax;
	}

	// 配列の要素数
	short n = getProtein - 1;
	// プロテインを表示させて
	protein[n]->SetActive(true);
	proMark[n]->SetActive(false);
	//大きくする
	protein[n]->mTransform.scale = { 0.0f, 0.0f, 1.0f };
	protein[n]->dotween->DoEaseElasticScale(proScale, PRO_SCALETIME);
}

void ProteinUI::Draw()
{
	bar->Draw();

	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i]->Draw();
	}

	for (int i = 0; i < stageProMax; i++)
	{
		protein[i]->Draw();
	}
}

void ProteinUI::SetPosition(const Vector3& _pos)
{
	mTransform.pos = _pos;

	bar->mTransform.pos = _pos;

	switch (stageProMax)
	{
	case 1:
		proMark[0]->mTransform.pos.x = _pos.x;
		break;

	case 2:
		proMark[0]->mTransform.pos.x = _pos.x - CIRCLE_OFFSETX / 2;
		proMark[1]->mTransform.pos.x = _pos.x + CIRCLE_OFFSETX / 2;
		break;

	case 3:
		proMark[0]->mTransform.pos.x = _pos.x - CIRCLE_OFFSETX;
		proMark[1]->mTransform.pos.x = _pos.x;
		proMark[2]->mTransform.pos.x = _pos.x + CIRCLE_OFFSETX;
		break;
	}

	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i]->mTransform.pos.y = _pos.y + CIRCLE_OFFSETY;
		proMark[i]->mTransform.pos.z = _pos.z - i * UI_OFFSETZ;

		protein[i]->mTransform.pos = proMark[i]->mTransform.pos;
		protein[i]->mTransform.pos.z -=  2 * UI_OFFSETZ;
	}
}