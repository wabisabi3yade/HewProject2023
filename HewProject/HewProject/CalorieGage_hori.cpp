#include "CalorieGage_hori.h"
#include "TextureFactory.h"
#include "CalorieMark.h"

#define GAGEUI_OFFSET_Z	 (0.0001f) // ゲージのUIのZ座標の差分

#define ROGO_OFFSET_X (-3.23f)	// ゲージ全体からのロゴのX座標
#define ROGO_OFFSET_Y (0.2f)	// ゲージ全体からのロゴのY座標

#define NUMBER_OFFSETX (0.3f)	// ロゴの中心からの距離
#define NUMBER_OFFSETY (-0.1f)	// ロゴの中心からの距離

#define MARK_BEGIN_OFFSET_X (-2.0f)	// 1目盛り目のX座標
#define MARKTO_OFFSET_X (0.32f)	// 目盛り同士のX座標差分
#define YELLOW_RATIO (1.0f / 3)	// ゲージ全体から見た黄色の割合
#define GREEN_RATIO (2.0f / 3)	// ゲージ全体から見た緑色の割合
#define MARK_SCALETIME (0.75f)	// 目盛り大きくなる時間
CalorieGage_hori::CalorieGage_hori()
{
	// 初期化
	mTransform.pos = {};
	mTransform.scale = { 1,1,1 };
	mTransform.rotation = {};

	TextureFactory* texFactory = TextureFactory::GetInstance();

	// テクスチャを取得する作業用変数
	D3DTEXTURE texWork;

	D3D_CreateSquare({ 1,1 }, &oneBuffer);

	const Vector3& basePos = mTransform.pos;

	// ゲージ背景
	texWork = texFactory->Fetch(L"asset/UI/Gage_Back.png");
	back = new UI(oneBuffer, texWork);
	back->SetAlpha(0.6f);

	// ロゴ
	texWork = texFactory->Fetch(L"asset/UI/Gage_Rogo.png");
	rogo = new UI(oneBuffer, texWork);

	D3D_CreateSquare({ 3,4 }, &numBuffer);
	texWork = texFactory->Fetch(L"asset/UI/Calorie_Number.png");
	for (int i = 0; i < calorieDigits; i++)
	{
		number[i] = new UI(numBuffer, texWork);
	}

	// 目盛りの初期化
	texWork = texFactory->Fetch(L"asset/UI/Carorie_Mark.png");
	D3D_CreateSquare({ 3,1 }, &markBuffer);
	// 最大数分作成する
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i] = new CalorieMark(markBuffer, texWork);
		mark[i]->MakeDotween();

		//　緑色
		if (i >= MARKNUM_MAX * GREEN_RATIO)
		{
			mark[i]->SetColor(CalorieMark::GREEN);
		}
		// 黄色
		else if(i >= MARKNUM_MAX * YELLOW_RATIO)
		{
			mark[i]->SetColor(CalorieMark::YELLOW);
		}
	}

	// UIを並べる
	SetPosition(mTransform.pos);
	SetScale(mTransform.scale);

	// 目盛りを初期カロリーに反映させる
	SetCalorie(calorieNum, false);

}

CalorieGage_hori::~CalorieGage_hori()
{
	SAFE_RELEASE(markBuffer);
	SAFE_RELEASE(oneBuffer);
	SAFE_RELEASE(numBuffer);

	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		CLASS_DELETE(mark[i]);
	}
	for (int i = 0; i < calorieDigits; i++)
	{
		CLASS_DELETE(number[i]);
	}
	CLASS_DELETE(rogo);
	CLASS_DELETE(back);
}

void CalorieGage_hori::Update()
{
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->Update();
	}
}

void CalorieGage_hori::Draw()
{
	// 背景の描画
	back->Draw();

	// ロゴの描画
	rogo->Draw();

	// 数字の描画
	for (int i = 0; i < calorieDigits; i++)
	{
		number[i]->Draw();
	}

	

	// 目盛りの描画
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->Draw();
	}
}

void CalorieGage_hori::SetPosition(const Vector3& _pos)
{
	mTransform.pos = _pos;

	// UI全ても変える
	const Vector3& basePos = mTransform.pos;
	const Vector3& baseScale = mTransform.scale;

	back->mTransform.pos = basePos;
	back->mTransform.pos.z = basePos.z;

	rogo->mTransform.pos.x = basePos.x + baseScale.x * ROGO_OFFSET_X;
	rogo->mTransform.pos.y = basePos.y + baseScale.y * ROGO_OFFSET_Y;
	rogo->mTransform.pos.z = basePos.z - GAGEUI_OFFSET_Z;

	// 数字UIの設定
	NumUISetting();

	// めもり
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->mTransform.pos.x = basePos.x + baseScale.x * MARK_BEGIN_OFFSET_X;
		mark[i]->mTransform.pos.x += i * baseScale.x * MARKTO_OFFSET_X;
		mark[i]->mTransform.pos.y = basePos.y;
		mark[i]->mTransform.pos.z = basePos.z - (i + 1) * GAGEUI_OFFSET_Z;
	}
}

void CalorieGage_hori::SetScale(const Vector3& _scale)
{
	// 大きさを変える
	mTransform.scale = _scale;

	// UI全ても変える
	const Vector3& basePos = mTransform.pos;


	// スケールを反映させる
	back->mTransform.scale = _scale * backScale;

	rogo->mTransform.pos.x = basePos.x + _scale.x * ROGO_OFFSET_X;
	rogo->mTransform.pos.y = basePos.y + _scale.y * ROGO_OFFSET_Y;
	rogo->mTransform.scale = _scale * rogoScale;
	// スケールのZは固定
	rogo->mTransform.scale.z = 1.0f;

	// 数字UIの設定
	NumUISetting();

	// めもり
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->mTransform.pos.x = basePos.x + _scale.x * MARK_BEGIN_OFFSET_X;
		mark[i]->mTransform.pos.x += i * _scale.x * MARKTO_OFFSET_X;
		mark[i]->mTransform.scale = _scale * markScale;
		mark[i]->mTransform.scale.z = 1.0f;
	}
}

void CalorieGage_hori::SetCalorie(const short& _set, bool action)
{
	// 増える前のカロリー
	const short o_num = calorieNum;

	// 代入する
	calorieNum  = _set;
	if (calorieNum > MARKNUM_MAX)
	{
		calorieNum = MARKNUM_MAX;
	}
	else if (calorieNum < 0)
	{
		calorieNum = 0;
	}

	// 数字のUI
	NumUISetting();

	// 演出ありなら
	if (action)
	{
		// 目盛りに反映させる
		MarkAdd(o_num, _set - o_num);
	}
	else
	{
		// カロリーのゲージまで表示させる
		int roop = 0;
		for (; roop < calorieNum; roop++)
		{
			// 表示させて大きさを変える
			mark[roop]->SetActive(true);
			mark[roop]->mTransform.scale.x = mTransform.scale.x * markScale.x;
			mark[roop]->mTransform.scale.y = mTransform.scale.y * markScale.y;
		}
		
		for (; roop < MARKNUM_MAX; roop++)
		{
			mark[roop]->SetActive(false);
			mark[roop]->mTransform.scale.x = 0.0f;
			mark[roop]->mTransform.scale.y = 0.0f;
		}

	}
	
}

void CalorieGage_hori::AddCalorie(const short& _add)
{
	// 増える前のカロリー
	const short o_num = calorieNum;

	// 足す
	calorieNum += _add;
	if (calorieNum > MARKNUM_MAX)
	{
		calorieNum = MARKNUM_MAX;
	}
	else if (calorieNum < 0)
	{
		calorieNum = 0;
	}
	// 数字のUI
	NumUISetting();
	MarkAdd(o_num, _add);
}

void CalorieGage_hori::MarkAdd(const short& _oldNum, const short& _add)
{
	short targetValue = _oldNum + _add;

	// 増えるなら
	if (_add > 0)
	{
		for (short i = _oldNum; i < targetValue; i++)
		{
			if (i >= MARKNUM_MAX) break;

			mark[i]->SetActive(true);
			mark[i]->mTransform.scale.x = 0.0f;
			mark[i]->mTransform.scale.y = 0.0f;
			// 目標の大きさ
			Vector3 target = mTransform.scale * markScale;
			target.z = 1.0f;
			mark[i]->dotween->DoEaseOutBackScale(target, MARK_SCALETIME);
		}
	}
	// 減るなら
	else
	{
		for(short i = _oldNum; i > targetValue; i--)
		{
			if (i <= 0) break;

			// 目標の大きさ
			mark[i - 1]->dotween->DoEaseInBackScale(Vector3::zero , MARK_SCALETIME);
			mark[i - 1]->dotween->OnComplete([&, i]()
				{
					mark[i - 1]->SetActive(false);
					
					// 減らした後に増やすと時間差で非表示になってしまうので対策
					if (i <= calorieNum)
					mark[i - 1]->SetActive(true);
					
				});
		}
	}
}

void CalorieGage_hori::NumUISetting()
{
	const Vector3& baseScale = mTransform.scale;

	// 数字
	// 2桁未満ならロゴの中心にセットする
	if (calorieNum < 10)
	{
		number[0]->mTransform.pos.x = rogo->mTransform.pos.x;
		number[1]->SetActive(false);

	}
	// 2桁なら中心からずらすようにする
	else
	{
		number[0]->mTransform.pos.x = rogo->mTransform.pos.x + baseScale.x * NUMBER_OFFSETX;
		number[1]->mTransform.pos.x = rogo->mTransform.pos.x - baseScale.x * NUMBER_OFFSETX;
		number[1]->SetActive(true);
	}

	DirectX::XMFLOAT3 rgb;
	// 色決め
	if (calorieNum > MARKNUM_MAX * GREEN_RATIO)
	{
		rgb = { 89, 215, 98 };
	}
	else if (calorieNum > MARKNUM_MAX * YELLOW_RATIO)
	{
		rgb = { 255, 215, 0 };
	}
	else
	{
		rgb = { 252, 100, 100 };
	}

	for (int i = 0; i < calorieDigits; i++)
	{
		number[i]->mTransform.pos.y = rogo->mTransform.pos.y + NUMBER_OFFSETY;
		number[i]->mTransform.pos.z = rogo->mTransform.pos.z - (i + 1) * GAGEUI_OFFSET_Z;
		number[i]->mTransform.scale = baseScale * numScale;
		number[i]->mTransform.scale.z = 1.0f;
		number[i]->SetColor(rgb);
	}

	// UV座標設定
	number[1]->SetUV(1.0f / 3, 0.0f);
	// 1桁の数字を求める
	short oneDigitsNum = calorieNum % 10;
	number[0]->SetUV(oneDigitsNum % 3 * (1.0f / 3), oneDigitsNum / 3 * (1.0f / 4));
}
