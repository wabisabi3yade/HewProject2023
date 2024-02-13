#include "Fade.h"
#include "FadeUI.h"
#include "NowLoadingText.h"
#include "TextureFactory.h"
#include "CScene.h"



#define FADESCALE_X (20.0f)
#define FADESCALE_Y (9.0f)
#define FADE_BASE_POSZ (-0.45f)	// フェードの基準座標
#define FADEOUT_POSX (16.0f + FADESCALE_X / 2.0f)	// フェードアウトの時に向かうX座標

#define FADE_TIME (1.5f)
#define LOAD_TIME (2.5f)	// ロード時間

#define LOADING_BACKSPEED (0.007f)	// ローディング時に動く背景の速度 
#define NOWLOADING_OFFSET_Z (0.1f)	// NowLoadingのテキストが背景からの差 

Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	// 初期化
	isActive = false;
	state = STATE::STAY;
	loadingTime = 0.0f;

	// 空オブジェクト
	// Dotween使用する
	fadeBase = new UI();
	fadeBase->MakeDotween();
	fadeBase->mTransform.pos.z = FADE_BASE_POSZ;

	// 背景
	tex = TextureFactory::GetInstance()->Fetch(L"asset/UI/fade_BackBlue.png");
	D3D_CreateSquare({ 1,1 }, &vb);

	backGround = new FadeUI(vb, tex);
	backGround->MakeDotween();
	backGround->mTransform.scale = {FADESCALE_X, FADESCALE_Y, 1.0f };
	backGround->SetActive(false);
	backGround->mTransform.pos.z = FADE_BASE_POSZ;
}

// 描画に使用するテクスチャ
Fade::~Fade()
{
	CLASS_DELETE(fadeBase);

	CLASS_DELETE(backGround);

	CLASS_DELETE(nowLoading);

	SAFE_RELEASE(vb);
}

void Fade::SceneChange(int _set)
{
	isSceneChange = true;

	nextScene = _set;
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

	backGround->dotween->Update();

	if (nowLoading != nullptr)
	{
		nowLoading->Update();
	}
}

void Fade::FadeInUpdate()
{
}

void Fade::LoadingInit()
{
	//シーンをロードシーンに行く
	ChangeLoadScene();

	state = STATE::LOADING;
	loadingTime = 0.0f;


	// テキストを作成する
	nowLoading = new NowLoadingText();
}

void Fade::ChangeLoadScene()
{
	isSceneChange = true;
}

void Fade::LoadingUpdate()
{
	// 右側に動く
	float vecX = 1.0f;

	// 背景を移動させる
	backGround->mTransform.pos.x += vecX * LOADING_BACKSPEED;

	// 1フレームの時間
	loadingTime += 1.0f / 60;
	// ロード時間が超えたら
	if (loadingTime < LOAD_TIME) return;

	// テキストを解放する
	CLASS_DELETE(nowLoading);

	state = STATE::FADE_OUT;	// フェードアウトする

	FadeOutInit();
}

void Fade::FadeOutInit()
{
	// 状態を更新する
	state = STATE::FADE_OUT;

	// ここで代入した関数を実行する
	func();

	// シーンを変えるときに呼ぶ関数
	


	Vector3 v = Vector3::zero;
	v.x = FADEOUT_POSX;
	v.z = FADE_BASE_POSZ;
	backGround->dotween->DoEaseOutCubic(v, FADE_TIME);
	backGround->dotween->OnComplete([&]()
		{
			// 非表示にする
			isActive = false;
			// 背景を非表示にする
			backGround->SetActive(false);
			// 待機状態にする
			state = STATE::STAY;
		});
}

void Fade::FadeOutUpdate()
{
}

void Fade::FadeIn(const STATE& _nextState, std::function<void()> _onFunc, int _setScene)
{
	if (state != Fade::STATE::STAY) return;

	// ラムダ式を代入する
	func = _onFunc;

	ChangeLoadScene();


	// フェード全体を表示
	isActive = true;

	// 現在、次のの状態を更新する
	state = STATE::FADE_IN;
	nextState = _nextState;

	// 画面左端に配置する
	backGround->mTransform.pos.x = -FADEOUT_POSX;

	// 背景の初期化する
	backGround->SetActive(true);

	// フェードが画面端に到達する瞬間の座標
	Vector3 v = Vector3::zero;
	v.z = FADE_BASE_POSZ;
	backGround->dotween->DoEaseOutCubic(v, FADE_TIME);
	backGround->dotween->OnComplete([&]()
		{
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
		});
}

void Fade::Draw()
{
	if (!isActive) return;

	// 背景描画
	backGround->Draw();

	if (nowLoading != nullptr)
	{
		nowLoading->Draw();
	}
}

bool Fade::GetIsChange()
{
	return false;
}

bool Fade::GetLoadChange()
{
	if (isSceneChange)
	{
		isSceneChange = false;
		return true;
	}

	return false;
}


