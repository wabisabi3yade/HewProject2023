#include "NowLoadingText.h"
#include "LoadCharacter.h"
#include "TextureFactory.h"

#define TEXT_BASEPOSX (2.0f)	// テキスト1文字目のX座標
#define TEXT_SIN_BASEPOSY (0.0f)	// サイン関数で動かす軸となるY座標
#define TEXT_POSZ (-0.49f)	// テキストのZ座標

#define ALL_SCALE (0.93f)	// テキストの全体の倍率
#define TEXT_SPACE_X (ALL_SCALE * 0.55f)	//	文字間のスペース
#define TEXT_PERIOD_SPACE (ALL_SCALE * 0.35f)	// ピリオド間のスペース
#define OFFSET_CHARA_TEXT (ALL_SCALE * 0.9f)	// キャラクターと文字の大きさ


#define TEXT_U_NUM (3)	// テキスト画像のU
#define TEXT_V_NUM (4)

#define TEXT_AMPLITUDE (0.4f)	// テキストの振幅
#define TEXT_MOVESPEED (3.0f)	// テキストの動く速度

NowLoadingText::NowLoadingText()
{
	// バッファ作成
	D3D_CreateSquare({ 3,4 }, &buffer);

	// テクスチャ読みこみ
	TextureFactory* texFactory = TextureFactory::GetInstance();
	D3DTEXTURE texWork = texFactory->Fetch(L"asset/UI/NowLoading….png");

	Vector3 textBeginPos = { TEXT_BASEPOSX, TEXT_SIN_BASEPOSY, TEXT_POSZ };
	Vector2 textScale = Vector2::zero;
	// テキスト作成
	for (int num = 0; num < static_cast<int>(TEXT::NUM); num++)
	{
		text[num] = new UI(buffer, texWork);


		// 左端から文字の距離をとる
		text[num]->mTransform.pos = textBeginPos;
		// ピリオドまでの文字
		if (num < static_cast<int>(TEXT::period_1))
		{
			
			text[num]->mTransform.pos.x += num * TEXT_SPACE_X;
		}
		// ピリオドから
		else
		{
			text[num]->mTransform.pos.x += static_cast<int>(TEXT::g) * TEXT_SPACE_X +
				TEXT_PERIOD_SPACE * ( num - static_cast<int>(TEXT::g));
		}

		// 角度を変えて
		degree[num] = rand() % 360;
		text[num]->mTransform.pos.y += TEXT_AMPLITUDE * sin(DirectX::XMConvertToRadians(degree[num]));

		// Z座標を被らないようにする
		text[num]->mTransform.pos.z = TEXT_POSZ - (num + 1) * 0.0001f;

		// 画像のUVを設定
		text[num]->SetUV((1.0f / TEXT_U_NUM) * (num % TEXT_U_NUM), (1.0f / TEXT_V_NUM) * (num / TEXT_U_NUM));

		// 大きさ調整
		switch (static_cast<TEXT>(num))
		{
		case TEXT::N:
			textScale = { 0.6f, 0.6f };
			break;

		case TEXT::o_1:
		case TEXT::o_2:
			textScale = { 0.43f, 0.43f };
			break;

		case TEXT::w:
			textScale = { 0.55f, 0.55f };
			break;

		case TEXT::L:
			textScale = { 0.65f,0.65f };
			break;

		case TEXT::a:
			textScale = { 0.4f, 0.4f };
			break;

		case TEXT::d:
			textScale = { 0.55f, 0.55f };
			break;

		case TEXT::i:
			textScale = { 0.5f, 0.5f };
			break;

		case TEXT::n:
			textScale = { 0.4f, 0.4f };
			break;

		case TEXT::g:
			textScale = { 0.5f, 0.5f };
			break;

		case TEXT::period_1:
		case TEXT::period_2:
		case TEXT::period_3:
			textScale = { 0.2f, 0.2f };
			text[num]->SetUV((1.0f / TEXT_U_NUM) * (10 % TEXT_U_NUM), (1.0f / TEXT_V_NUM) * (10 / TEXT_U_NUM));
			break;

		}
		// スケール全体の倍率をかける
		textScale = textScale * ALL_SCALE;

		text[num]->mTransform.scale = { textScale.x, textScale.y, 1.0f };
		// 色を変える
		text[num]->SetColor({ 255, 192, 103 });
	};

	texWork = texFactory->Fetch(L"asset/UI/LoadCharacter.png");
	character = new LoadCharacter(buffer, texWork);
	character->mTransform.scale = { 1.1f, 1.1f,1.0f };
	character->mTransform.pos.x = TEXT_BASEPOSX - OFFSET_CHARA_TEXT;
	character->mTransform.pos.z = TEXT_POSZ;
	character->SetColor({ 255, 192, 103 });
}

NowLoadingText::~NowLoadingText()
{
	for (int i = 0; i < static_cast<int>(TEXT::NUM); i++)
	{
		CLASS_DELETE(text[i]);
	}

	CLASS_DELETE(character);

	SAFE_RELEASE(buffer);
}

void NowLoadingText::Update()
{
	for (int i = 0; i < static_cast<int>(TEXT::NUM); i++)
	{
		// 角度を増やしていく
		degree[i] += TEXT_MOVESPEED;

		// 上下に動かす
		text[i]->mTransform.pos.y = TEXT_SIN_BASEPOSY + TEXT_AMPLITUDE * sin(DirectX::XMConvertToRadians(degree[i]));
	}
}

void NowLoadingText::Draw()
{
	character->Draw();

	for (int i = 0; i < static_cast<int>(TEXT::NUM); i++)
	{
		text[i]->Draw();
	}

}

void NowLoadingText::SetPosZ(float _setZ)
{
	for (int i = 0; i < static_cast<int>(TEXT::NUM); i++)
	{
		text[i]->mTransform.pos.z = _setZ;
	}

	character->mTransform.pos.z = _setZ;
}
