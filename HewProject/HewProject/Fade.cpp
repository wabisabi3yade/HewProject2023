#include "Fade.h"
#include "FadeUI.h"

#define FADE_BASE_POSZ (-0.5f)	// フェードの基準座標
#define FADEOUT_POSX (2.0f)	// フェードアウトの時に向かうX座標
#define FADE_SPEED (0.02f)	// フェードイン・アウト時の速度
#define LOAD_TIME (5.0f)	// ロード時間

#define LOADING_BACKSPEED (0.001f)	// ローディング時に動く背景の速度 


Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	// 初期化
	isActive = false;
	state = STATE::STAY;

	// 空オブジェクト
	// Dotween使用する
	fadeBase = new UI();
	fadeBase->MakeDotween();
	fadeBase->mTransform.pos.z = FADE_BASE_POSZ;

	// 背景
	D3D_LoadTexture(L"asset/BackGround/fade2.png", &tex);
	D3D_CreateSquare({ 1,1 }, &vb);
	
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		backGround[i] = new FadeUI(vb, tex);
		backGround[i]->mTransform.scale = { 3.0f, 2.0f, 1.0f };
		backGround[i]->SetActive(false);
	}
}

// 描画に使用するテクスチャ
Fade::~Fade()
{
	CLASS_DELETE(fadeBase);
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		CLASS_DELETE(backGround[i]);
	}

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

	// フェード全体の中心座標を背景に更新する
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		backGround[i]->SetBasePos(fadeBase->mTransform.pos);
	}	
}

void Fade::FadeInUpdate()
{
	// 右に移動する
	fadeBase->mTransform.pos.x += FADE_SPEED;

	// 真ん中についたら
	if (fadeBase->mTransform.pos.x > 0.0f)
	{
		fadeBase->mTransform.pos.x = 0.0f;

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
	loadingTime = 0.0f;

	//// 2枚目の画像を表示する
	//backGround[1]->SetActive(true);
	// 座標を1枚目の画像の左にする
	Vector3 v = { -backGround[1]->mTransform.scale.x , 0.0f, 0.0f };
	backGround[1]->SetOffset(v);


}

void Fade::LoadingUpdate()
{
	// 右側に動く
	float vecX = 1.0f;

	// フェード全体の中心座標を背景に更新する
	for (int i = 0; i < 1/*FADE_BACK_NUM*/; i++)
	{
		// 背景を移動させる
		float back_offset = backGround[i]->GetOffset().x;
		back_offset += vecX * LOADING_BACKSPEED;
		backGround[i]->SetOffset(back_offset);
	}


	// 1フレームの時間
	loadingTime += 1.0f / 60;
	// ロード時間が超えたら
	if (loadingTime < LOAD_TIME) return;

	state = STATE::FADE_OUT;	// フェードアウトする
}

void Fade::FadeOutInit()
{
	// 状態を更新する
	state = STATE::FADE_OUT;
}

void Fade::FadeOutUpdate()
{
	// 右に移動する
	fadeBase->mTransform.pos.x += FADE_SPEED;

	// 背景がどっちも画面外に行ったなら
	if (backGround[0]->mTransform.pos.x - backGround[0]->mTransform.scale.x / 2 > FADEOUT_POSX /*&&
		backGround[1]->mTransform.pos.x - backGround[1]->mTransform.scale.x / 2 > FADEOUT_POSX*/)
	{
		// 非表示にする
		isActive = false;
		// 待機状態にする
		state = STATE::STAY;
		// 背景を非表示にしておく
		for (int i = 0; i < FADE_BACK_NUM; i++)
		{
			// オフセットを戻しておく
			backGround[i]->SetOffset(Vector3::zero);
			backGround[i]->SetActive(false);
		}
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

	// 背景1枚目の初期化する
	backGround[0]->SetActive(true);
	// 画像が左画面端に合うようにオフセットを調整する
	Vector3 v = { (FADEOUT_POSX - backGround[0]->mTransform.scale.x) / 2, 0, 0};
	backGround[0]->SetOffset(v);

	// 最初にここに置く
	fadeBase->mTransform.pos = { -FADEOUT_POSX, 0.0f, 0.0f };
}

void Fade::Draw()
{
	if (!isActive) return;
	// 背景描画
	
	for (int i = 0; i < FADE_BACK_NUM; i++)
	{
		backGround[i]->Draw();
	}
	
}



