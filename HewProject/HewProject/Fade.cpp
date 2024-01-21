#include "Fade.h"
#include "FadeUI.h"

#define FADE_BASE_POSZ (-0.5f)	// フェードの基準座標
#define FADEOUT_POSX (3.0f)	// フェードアウトの時に向かうX座標
#define FADE_TIME (2.0f)
#define LOAD_TIME (5.0f)	// ロード時間

#define LOADING_BACKSPEED (0.001f)	// ローディング時に動く背景の速度 


Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	// 初期化
	isActive = false;
	state = STATE::STAY;
	time = 0.0f;

	// 空オブジェクト
	// Dotween使用する
	fadeBase = new UI();
	fadeBase->MakeDotween();
	fadeBase->mTransform.pos.z = FADE_BASE_POSZ;

	// 背景
	D3D_LoadTexture(L"asset/BackGround/fade2.png", &tex);
	D3D_CreateSquare({ 1,1 }, &vb);

	backGround = new FadeUI(vb, tex);
	backGround->mTransform.scale = { 3.0f, 2.0f, 1.0f };
	backGround->SetActive(false);

}

// 描画に使用するテクスチャ
Fade::~Fade()
{
	CLASS_DELETE(fadeBase);

	CLASS_DELETE(backGround);

	SAFE_RELEASE(tex);
	SAFE_RELEASE(vb);
}

Fade* Fade::GetInstance()
{
	// 作成していないなら
	if (instance == nullptr)
	{
		instance = new Fade();
	}

	return instance;
}

void Fade::Delete()
{
	CLASS_DELETE(instance);
}

void Fade::Update()
{
	if (!isActive) return;

	// 状態ごとに毎フレーム行う処理
	switch (state)
	{
	case STATE::STAY:;
		break;

	case STATE::FADE_IN:
		FadeInUpdate();
		break;

	case STATE::LOADING:
		LoadingUpdate();
		break;

	case STATE::FADE_OUT:
		FadeOutUpdate();
		break;

	default:
		MessageBoxA(NULL, "FadeクラスUpdateでstateの値が範囲外です", "エラー", MB_ICONERROR | MB_OK);
		break;
	}

	fadeBase->dotween->Update();
}

void Fade::FadeInUpdate()
{
	time += 1.0f / 60;

	// 右に移動する(イージング)
	backGround->mTransform.pos.x  = startPos + distance * (1 - std::pow(1 - time / FADE_TIME, 3));

	// 真ん中についたら
	if (time > FADE_TIME)
	{
		// 次の状態でやることをする
		switch (nextState)
		{
		case STATE::FADE_OUT:
			FadeOutInit();
			break;

		case STATE::LOADING:
			LoadingInit();
			break;

		default:
			MessageBoxA(NULL, "FadeのFadeIn関数で指定した状態が範囲外です", "エラー", MB_ICONERROR | MB_OK);
			break;
		}
	}
}

void Fade::LoadingInit()
{
	state = STATE::LOADING;
	time = 0.0f;
}

void Fade::LoadingUpdate()
{
	// 右側に動く
	float vecX = 1.0f;

	// 背景を移動させる
	backGround->mTransform.pos.x += vecX * LOADING_BACKSPEED;

	// 1フレームの時間
	time += 1.0f / 60;
	// ロード時間が超えたら
	if (time < LOAD_TIME) return;

	state = STATE::FADE_OUT;	// フェードアウトする

	FadeOutInit();
}

void Fade::FadeOutInit()
{
	// 状態を更新する
	state = STATE::FADE_OUT;

	//距離を測る
	startPos = backGround->mTransform.pos.x;
	distance = FADEOUT_POSX - startPos;

	time = 0.0f;
}

void Fade::FadeOutUpdate()
{
	time += 1.0f / 60;

	// 右に移動する
	backGround->mTransform.pos.x  = startPos + distance * (1 - std::pow(1 - time / FADE_TIME, 3));

	// 背景が画面外に行ったなら
	if (time > FADE_TIME)
	{
		// 非表示にする
		isActive = false;
		// 背景を非表示にする
		backGround->SetActive(false);
		// 待機状態にする
		state = STATE::STAY;
	}
}

void Fade::FadeIn(const STATE& _nextState)
{
	if (state != Fade::STATE::STAY) return;

	// フェード全体を表示
	isActive = true;

	// 現在、次のの状態を更新する
	state = STATE::FADE_IN;
	nextState = _nextState;

	// 画面左端に配置する
	backGround->mTransform.pos.x = -FADEOUT_POSX;

	//距離を測る
	startPos = backGround->mTransform.pos.x;
	distance = 0.0f - startPos;

	time = 0.0f;

	// 背景の初期化する
	backGround->SetActive(true);
}

void Fade::Draw()
{
	if (!isActive) return;
	
	// 背景描画
	backGround->Draw();
}



