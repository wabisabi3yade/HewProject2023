#include "CalorieMark.h"
#include "TextureFactory.h"

#define ONEMARK_DEGREE_OFFSET (360.0f / MARKNUM_MAX)	// 一目盛りごとの角度の差分

CalorieMark::CalorieMark()
{
	// テクスチャ、バッファ作成
	markTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/gage.png");
	D3D_CreateSquare({ 1,1 }, &markBuffer);

	// 目盛りを最大数分、作成
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i] = new UI(markBuffer, markTex);

		// 目盛りごとに角度を設定する
		mark[i]->mTransform.rotation.z = i * ONEMARK_DEGREE_OFFSET;

		// 目盛りごとの座標も設定する
		// X座標
		mark[i]->mTransform.pos.x = this->mTransform.pos.x + cos(DirectX::XMConvertToRadians(i * ONEMARK_DEGREE_OFFSET));

		// Y座標
		mark[i]->mTransform.pos.y = this->mTransform.pos.y + sin(DirectX::XMConvertToRadians(i * ONEMARK_DEGREE_OFFSET));

	
	}
}

CalorieMark::~CalorieMark()
{
	SAFE_RELEASE(markBuffer);

	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		CLASS_DELETE(mark[i]);
	}
}

void CalorieMark::Update()
{
}

void CalorieMark::Draw()
{
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->Draw();
	}
}
