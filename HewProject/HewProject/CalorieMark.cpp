#include "CalorieMark.h"
#include "TextureFactory.h"

#define ONEMARK_DEGREE_OFFSET (360.0f / MARKNUM_MAX)	// 一目盛りごとの角度の差分
#define OFFSET_MARK_POSZ (0.0001f)	// 1目盛りごとのZ座標の差分

CalorieMark::CalorieMark()
{
	mTransform.scale = Vector3::one;

	// テクスチャ、バッファ作成
	markTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/gage.png");
	D3D_CreateSquare({ 1,1 }, &markBuffer);

	// 目盛りを最大数分、作成
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i] = new UI(markBuffer, markTex);

		mark[i]->mTransform.scale.x = mTransform.scale.x;
		mark[i]->mTransform.scale.y = mTransform.scale.y;

		// 目盛りごとに角度を設定する
		mark[i]->mTransform.rotation.z = i * ONEMARK_DEGREE_OFFSET;

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

void CalorieMark::SetPosition(const Vector3& _setPos)
{
	const Vector3& scWork = this->mTransform.scale;

	// 座標を設定する
	mTransform.pos = _setPos;

	// 目盛りを最大数分、作成
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		const float startDegree = 90.0f;
		float radWork = DirectX::XMConvertToRadians(startDegree + i * ONEMARK_DEGREE_OFFSET);
		// 座標
		mark[i]->mTransform.pos.x = this->mTransform.pos.x + (scWork.x * baseRadius)
			* cos(radWork);

		mark[i]->mTransform.pos.y = this->mTransform.pos.y + (scWork.y * baseRadius)
			* sin(radWork);

		mark[i]->mTransform.pos.z = this->mTransform.pos.z - i * OFFSET_MARK_POSZ;
	}
}

void CalorieMark::SetScale(const Vector3& _setScale)
{
	// 全体の大きさを設定する
	this->mTransform.scale = _setScale;

	// 作業用変数
	const Vector2 radiusWork = { this->mTransform.scale.x * baseRadius ,  this->mTransform.scale.y * baseRadius };	 // 半径の大きさ

	// 目盛りを最大数分、作成
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		// スケール設定する
		mark[i]->mTransform.scale.x = this->mTransform.scale.y;
		mark[i]->mTransform.scale.y = this->mTransform.scale.y;

		const float startDegree = 90.0f;
		float radWork = DirectX::XMConvertToRadians(startDegree + i * ONEMARK_DEGREE_OFFSET);

		// 座標も設定する
		mark[i]->mTransform.pos.x = this->mTransform.pos.x +
			(this->mTransform.scale.x * radiusWork.x) * cos(radWork);
		mark[i]->mTransform.pos.y = this->mTransform.pos.y +
			(this->mTransform.scale.y * radiusWork.y) * sin(radWork);
	}
}
