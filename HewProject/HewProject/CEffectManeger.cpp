#include "CEffectManeger.h"
#include "Vector3.h"
//#include "CObject.h"
EffectManeger* EffectManeger::instance = nullptr;

//======???????????????======//
typedef struct
{
	bool aLoop;			// trueでループ。通常BGMはture、SEはfalse。
} Effect;

EffectManeger::EffectManeger()
{
	std::vector<const wchar_t*> effectTexPath{
		L"asset/kawada/Red_Slash.png",
		L"asset/kawada/bullets.png",
		L"asset/kawada/Red_Slash.png",
	};

	// 画像をロードしてテクスチャの配列に入れる
	for (int i = 0; i < effectTexPath.size(); i++)
	{
		effectTexBox.push_back(0);
		D3D_LoadTexture(effectTexPath[i], &effectTexBox[i]);
	}

	D3D_CreateSquare({ 3,4 }, &charBuffer);
}

//==============デスストラクタ==============//
EffectManeger::~EffectManeger()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		SAFE_RELEASE(effectTexBox[i]);
	}

	// エフェクトを解放
	for (auto itr = EffectList.begin(); itr != EffectList.end(); itr++)
	{
		CLASS_DELETE((*itr));
	}
	EffectList.clear();
}
// シーンマネージャーを取得
// 初めて呼び出されたらインスタンスを生成
EffectManeger* EffectManeger::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EffectManeger();
	}

	return instance;
}
//------------------------------------------//
void EffectManeger::Play(Vector3 _pos, Vector3 _scale, FX_TYPE _type, bool _isLoop)
{
	// テクスチャのパスの種類数よりも多い　または　負の値　なら
	if ((int)_type > effectTexBox.size() - 1 || (int)_type < 0)
	{
		MessageBoxA(NULL, "エフェクトマネージャーPlay関数で指定できないテクスチャ番号です", "エラー", MB_ICONERROR | MB_OK);

		return;
	}

	charObj = new CEffect(charBuffer, effectTexBox[_type]);

	//ループをするか決める(falseならループ)
	charObj->GetmAnim()->SetEffectLoop(_isLoop);
	//エフェクト大きさ
	charObj->mTransform.scale = _scale;
	//エフェクト位置
	charObj->mTransform.pos = _pos;

	charObj->GetmAnim()->animSpeed = 0.3f;

	//EffectlistにcharObjを追加
	EffectList.push_back(charObj);
}

void EffectManeger::Draw()
{
	//listの最初の値を取得;	list最後の値じゃない場合続行;	値を1追加
	for (auto itr = EffectList.begin(); itr != EffectList.end(); itr++)
	{
		//CEffectのDrawを実行
		(*itr)->Draw();
	}
}

//listの中身をupdateする
void EffectManeger::Update()
{
	//listの最初の値を取得;	list最後の値じゃない場合続行;
	for (auto itr = EffectList.begin(); itr != EffectList.end();)
	{
		//CEffectのUpdateを実行
		(*itr)->Update();

		// 再生が終わったなら削除する
		if (!(*itr)->GetIsPlaying())
		{
			delete *itr;

			// リストから削除する
			itr = EffectList.erase(itr);

			continue;
		}

		// 次に進める
		itr++;
	}
}

void EffectManeger::Delete()
{
	CLASS_DELETE(instance);
}
