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
	// プレイヤー　→　ステージ　→　アイテム　→　背景　→　エフェクト　→　UI
	const wchar_t* texPath[] =
	{
		L"asset/Player/N_Walk.png",
		L"asset/Player/F_Walk.png",
		L"asset/Player/T_Walk.png",
		L"asset/Player/M_Walk01_Forword.png",

		L"asset/Stage/floor_y.png",
		L"asset/Stage/floor_g.png",
		L"asset/Stage/2floor_y.png",
		L"asset/Stage/2floor_g.png",
		L"asset/Stage/Wall.png",
		L"asset/Stage/test_Hool.png",
		L"asset/Stage/Wataame.png",
		L"asset/Stage/Chocolate.png",
		L"asset/Stage/Baumkuchen_R.png",
		L"asset/Stage/Baumkuchen_L.png",
		L"asset/Stage/Castella.png",
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
		L"asset/UI/Title.png"
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
