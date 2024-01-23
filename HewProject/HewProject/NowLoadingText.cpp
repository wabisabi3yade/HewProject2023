#include "NowLoadingText.h"
#include "LoadCharacter.h"
#include "TextureFactory.h"

#define TEXT_SIN_BASEPOSY (0.0f)	// サイン関数で動かす軸となるY座標
#define TEXT_SPACE_X (0.1f)	// 
#define TEXT_U_NUM (3)
#define TEXT_V_NUM (4)

NowLoadingText::NowLoadingText()
{
	// バッファ作成
	D3D_CreateSquare({ 3,4 }, &buffer);

	// テクスチャ読みこみ
	TextureFactory* texFactory = TextureFactory::GetInstance();
	D3DTEXTURE texWork = texFactory->Fetch(L"asset/UI/NowLoading….png");

	Vector3 textBeginPos = { 0.0f, -0.5f, -0.5f };
	Vector2 textScale = Vector2::zero;
	// テキスト作成
	for (int num = 0; num < static_cast<int>(TEXT::NUM); num++)
	{
		text[num] = new UI(buffer, texWork);

		// 大きさ調整
		switch (static_cast<TEXT>(num))
		{
		case TEXT::N:
			textScale = {0.1f, 0.2f};
			break;

		case TEXT::o_1:
		case TEXT::o_2:
			textScale = { 0.085f, 0.17f };
			break;

		case TEXT::w:
			textScale = { 0.09f, 0.18f };
			break;

		case TEXT::L:
			textScale = { 0.09f, 0.18f };
			break;

		case TEXT::a:
			textScale = { 0.1f, 0.2f };
			break;

		case TEXT::d:
			textScale = { 0.1f, 0.2f };
			break;

		case TEXT::i:
			textScale = { 0.1f, 0.2f };
			break;

		case TEXT::n:
			textScale = { 0.1f, 0.2f };
			break;

		case TEXT::g:
			textScale = { 0.1f, 0.2f };
			break;

		case TEXT::period:
			textScale = { 0.1f, 0.2f };
			break;
		}

		// 左端から文字の距離をとる
		text[num]->mTransform.pos = textBeginPos;
		text[num]->mTransform.pos.x += num * TEXT_SPACE_X;
		text[num]->mTransform.scale = { textScale.x, textScale.y, 1.0f };

		// 画像のUVを設定
		text[num]->SetUV((1.0f / TEXT_U_NUM) * (num % TEXT_U_NUM), (1.0f / TEXT_V_NUM) * (num / TEXT_U_NUM));
	};

	texWork = texFactory->Fetch(L"asset/UI/LoadCharacter.png");
	character = new LoadCharacter(buffer, texWork);
	character->mTransform.scale = { 0.1f, 0.2f,1.0f };
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
