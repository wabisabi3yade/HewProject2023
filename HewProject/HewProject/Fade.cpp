#include "Fade.h"
#include "FadeUI.h"
#include "NowLoadingText.h"
#include "TextureFactory.h"
#include "CScene.h"
#include"xa2.h"
#include "Vector2.h"
#include "StageMoveText.h"

#define FADESCALE_X (20.0f)
#define FADESCALE_Y (9.0f)
#define FADE_BASE_POSZ (-0.498f)	// フェードの基準座標
#define FADEOUT_POSX (16.0f + FADESCALE_X / 2.0f)	// フェードアウトの時に向かうX座標

#define FADE_TIME (1.5f)
#define LOAD_TIME (2.0f)	// ロード時間

#define LOADING_BACKSPEED (0.007f)	// ローディング時に動く背景の速度 
#define NOWLOADING_OFFSET_Z (0.1f)	// NowLoadingのテキストが背景からの差 

#define FADEIN_DELAYTIME (0.5f)	// フェードイン呼ばれてフェードインするまでに待機時間

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
	backGround->mTransform.scale = { FADESCALE_X, FADESCALE_Y, 1.0f };
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

	CLASS_DELETE(moveText);
}

void Fade::SceneChange()
{
	isSceneChange = true;
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

	backGround->dotween->Update();

	// 状態ごとに毎フレーム行う処理
	switch (state)
	{
	case STATE::STAY:
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

	case STATE::MOVING:
		MovingUpdate();
		break;


	default:
		MessageBoxA(NULL, "FadeクラスUpdateでstateの値が範囲外です", "エラー", MB_ICONERROR | MB_OK);
		break;
	}

	if (isFadeInEnd)
	{
		isFadeInEnd = false;

		FadeOutInit();
	}


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
	isLoadChange = true;
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
	if (func != nullptr)
	{
		func();
	}
	// シーンを変えるときに呼ぶ関数
	if (nextScene != CScene::SCENE_NAME::NONE)
		SceneChange();

	Vector3 v = Vector3::zero;
	v.x = FADEOUT_POSX;
	v.z = FADE_BASE_POSZ;

	backGround->dotween->Stop();
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

	// 次のシーンを代入する
	nextScene = _setScene;


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

	backGround->dotween->DelayedCall(FADEIN_DELAYTIME, [&]
		{
			XA_Play(SOUND_LABEL::S_FADE_IN);
		});
	backGround->dotween->DoDelay(FADEIN_DELAYTIME);
	backGround->dotween->Append(v, FADE_TIME, DoTweenUI::FUNC::EASE_OUTCUBIC);
	backGround->dotween->OnComplete([&]()
		{
			switch (nextState)
			{
			case STATE::FADE_OUT:
				/*FadeOutInit();*/ isFadeInEnd = true;
				break;

			case STATE::LOADING:
				LoadingInit();
				break;

			case STATE::MOVING:
				MovingInit();
				break;

			default:
				MessageBoxA(NULL, "FadeのFadeIn関数で指定した状態が範囲外です", "エラー", MB_ICONERROR | MB_OK);
				break;
			}
		});
}

void Fade::MovingInit()
{
	//シーンをロードシーンに行く
	ChangeLoadScene();

	state = STATE::MOVING;
	loadingTime = 0.0f;

	// 次のステージの数を求める
	INT_XY nextStageNum = JudgeNum();

	moveText = new StageMoveText(nextStageNum.x, nextStageNum.y);
}

void Fade::MovingUpdate()
{
	// 右側に動く
	float vecX = 1.0f;

	// 背景を移動させる
	backGround->mTransform.pos.x += vecX * LOADING_BACKSPEED;

	if (moveText != nullptr)
		moveText->Update();

	// 1フレームの時間
	loadingTime += 1.0f / 60;
	// ロード時間が超えたら
	if (loadingTime < LOAD_TIME) return;

	// テキストを解放する
	CLASS_DELETE(moveText);

	state = STATE::FADE_OUT;	// フェードアウトする

	FadeOutInit();
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

	if (moveText != nullptr)
	{
		moveText->Draw();
	}
}


Fade::INT_XY Fade::JudgeNum()
{
	INT_XY w_sNum = {};
	switch (nextScene)
	{
	case CScene::STAGE1_1:
	case CScene::STAGE1_2:
	case CScene::STAGE1_3:
	case CScene::STAGE1_4:
	case CScene::STAGE1_5:
	case CScene::STAGE1_6:
		w_sNum.x = 1;
		break;

	case CScene::STAGE2_1:
	case CScene::STAGE2_2:
	case CScene::STAGE2_3:
	case CScene::STAGE2_4:
		w_sNum.x = 2;
		break;

	case CScene::STAGE3_1:
	case CScene::STAGE3_2:
	case CScene::STAGE3_3:
	case CScene::STAGE3_4:
		w_sNum.x = 3;
		break;

	case CScene::STAGE4_1:
	case CScene::STAGE4_2:
	case CScene::STAGE4_3:
	case CScene::STAGE4_4:
		w_sNum.x = 4;
		break;

	default:
		break;
	}

	switch (nextScene)
	{
	case CScene::STAGE1_1:
	case CScene::STAGE2_1:
	case CScene::STAGE3_1:
	case CScene::STAGE4_1:
		w_sNum.y = 1;
		break;

	case CScene::STAGE1_2:
	case CScene::STAGE2_2:
	case CScene::STAGE3_2:
	case CScene::STAGE4_2:
		w_sNum.y = 2;
		break;

	case CScene::STAGE1_3:
	case CScene::STAGE2_3:
	case CScene::STAGE3_3:
	case CScene::STAGE4_3:
		w_sNum.y = 3;
		break;


	case CScene::STAGE1_4:
	case CScene::STAGE2_4:
	case CScene::STAGE3_4:
	case CScene::STAGE4_4:
		w_sNum.y = 4;
		break;


	case CScene::STAGE1_5:
		w_sNum.y = 5;
		break;
	case CScene::STAGE1_6:
		w_sNum.y = 6;
		break;

	default:
		break;
	}

	return w_sNum;
}

bool Fade::GetIsChange()
{
	if (isSceneChange)
	{
		isSceneChange = false;
		return true;
	}

	return false;
}

bool Fade::GetLoadChange()
{
	if (isLoadChange)
	{
		isLoadChange = false;
		return true;
	}

	return false;
}

int Fade::GetNextScene()
{
	return nextScene;
}


