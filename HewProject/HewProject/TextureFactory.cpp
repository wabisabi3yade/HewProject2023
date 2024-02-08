#include "TextureFactory.h"

TextureFactory* TextureFactory::instance = nullptr;
TexHash* TextureFactory::texList = {};

TextureFactory::~TextureFactory()
{
	// texListのtexture情報解放
	for (auto e : *texList)
	{
		SAFE_RELEASE(e.second);
	}

	CLASS_DELETE(texList);
}

void TextureFactory::Init()
{
	Load();
}

TextureFactory* TextureFactory::GetInstance()
{
	// 初めて作られたなら
	if (instance == nullptr)
	{
		instance = new TextureFactory();
		// 初期化処理をする
		Init();
	}

	return instance;
}

void TextureFactory::Delete()
{
	CLASS_DELETE(instance);
}

void TextureFactory::Load()
{
	texList = new TexHash();	// テクスチャのマップクラス

	// テクスチャのパス名格納
	// 順番
	// プレイヤー　→　ステージ　→　アイテム　→　背景　→　エフェクト　→　UI →　文字
	const wchar_t* texPath[] =
	{
		L"asset/Background/Stage2.png",
		
		L"asset/Player/N_Walk.png",
		L"asset/Player/F_Walk.png",
		L"asset/Player/T_Walk.png",
		L"asset/Player/M_Walk.png",
		L"asset/Player/N_Wait.png",
		L"asset/Player/F_Wait.png",
		L"asset/Player/T_Wait.png",
		L"asset/Player/M_Wait.png",
		L"asset/Player/M_Punch_Down.png",
		L"asset/Player/M_Punch_Left.png",
		L"asset/Player/M_Punch_Right.png",
		L"asset/Player/M_Punch_Up.png",
		L"asset/Player/N_EatCake.png",
		L"asset/Player/F_EatCake.png",
		L"asset/Player/T_EatCake.png",
		L"asset/Player/N_EatChili.png",
		L"asset/Player/F_EatChili.png",
		L"asset/Player/T_EatChili.png",
		L"asset/Player/Player_CanonMove.png",

		L"asset/Stage/floor_y.png",
		L"asset/Stage/floor_g.png",
		L"asset/Stage/2floor_y.png",
		L"asset/Stage/2floor_g.png",
		L"asset/Stage/Wall.png",
		L"asset/Stage/test_Hool.png",
		L"asset/Stage/Wataame.png",
		L"asset/Stage/Chocolate.png",
		L"asset/Stage/ChocoClack.png",
		L"asset/Stage/Baumkuchen_R.png",
		L"asset/Stage/Baumkuchen_L.png",
		L"asset/Stage/Castella.png",
		L"asset/Stage/Canon_RightLeft.png",
		L"asset/Stage/Canon_UpDown.png",
		L"asset/Stage/2castella.png",
		L"asset/Stage/GallChest.png",
		L"asset/Stage/Gumi.png",

		L"asset/Item/Cake.png",
		L"asset/Item/Chili.png",
		L"asset/Item/Coin.png",
		L"asset/Item/Protein.png",
		L"asset/Item/shadow.png",

		L"asset/UI/fade_BackBlue.png",
		L"asset/UI/NowLoading….png",
		L"asset/UI/LoadCharacter.png",
		L"asset/UI/textBox_Blue.png",
		L"asset/UI/textBox_White.png",
		L"asset/UI/textBox_Pink.png",
		L"asset/UI/textBox_Purple.png",
		L"asset/UI/Title.png",
		L"asset/UI/Carorie_Mark.png",
		L"asset/UI/Gage_Rogo.png",
		L"asset/UI/Gage_Back.png",
		L"asset/UI/Calorie_Number.png",
		L"asset/UI/Floor_Num.png",
		L"asset/UI/Button.png",
		L"asset/UI/Protein_Mark.png",
		L"asset/UI/Protein_Bar.png",
		L"asset/UI/GAMEOVER.png",
		L"asset/UI/Arrow.png",

		L"asset/Text/T_GameStart.png",
		L"asset/Text/T_GameEnd.png",
		L"asset/Text/T_Back.png",
		L"asset/Text/T_Help.png",
		L"asset/Text/T_Restart.png",
		L"asset/Text/T_Undo.png",
	};

	D3DTEXTURE texWork;

	// 上で書いたパス名をロードしていく
	for (int i = 0; i < ARRAYSIZE(texPath); i++)
	{
		D3D_LoadTexture(texPath[i], &texWork);
		// マップクラスに入れていく（パス名, テクスチャ情報）
		texList->emplace(texPath[i], texWork);
	}
}

D3DTEXTURE TextureFactory::Fetch(std::wstring _texPath)
{
	// 指定したパス名のテクスチャを返す
	return texList->at(_texPath);
}
