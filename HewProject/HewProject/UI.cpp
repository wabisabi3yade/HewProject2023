#include "UI.h"

using namespace DirectX;

UI::UI()
{
	Init();

	mVertexBuffer = NULL;
	mTexture = NULL;
}

UI::UI(D3DBUFFER vb, D3DTEXTURE tex)
{
	Init();

	mVertexBuffer = vb;
	mTexture = tex;
}

UI::~UI()
{
	CLASS_DELETE(dotween);
}

void UI::Init()
{
	mAnim = nullptr;
	dotween = nullptr;
	isActive = true;

	mTransform.pos = {};
	mTransform.pos.z = -0.5f;
	mTransform.scale = { 1,1,1 };
	mTransform.rotation = {};
}

void UI::Update()
{
	if (!isActive) return;

	if (dotween != nullptr)
	{
		dotween->Update();
	}
}

void UI::Draw()
{
	if (!isActive) return;  // 非表示なら処理終了

	// アニメーションするオブジェクトなら
	if (mAnim != nullptr)
	{
		//アニメーションの更新
			mAnim->Update();
		//uv座標を取得
			uv = mAnim->GetUV();
	}

	ConstBuffer cb;
	//// 投影行列を単位行列にすることで、仮想世界ではなく直接仮想画面にポリゴンを配置できる    
	//cb.matrixProj = XMMatrixIdentity();
	//cb.matrixProj = XMMatrixTranspose(cb.matrixProj);

	// 平行投影の行列作成
	// 引数　①②：映し出す面の横縦の長さ　
	// 　　　③④：映し出す空間の奥行（手前と最奥の距離）
	cb.matrixProj = XMMatrixOrthographicLH(16.0f, 9.0f, -1.0f, 3.0f);
	cb.matrixProj = XMMatrixTranspose(cb.matrixProj);

	// ワールド変換行列の作成
	// 移動行列
	XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x, mTransform.pos.y, mTransform.pos.z);
	// 拡大縮小行列
	XMMATRIX matrixScale = XMMatrixScaling(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);
	// 回転行列　XMMatrixRotationZ関数
	XMMATRIX matrixRotate = XMMatrixRotationZ(XMConvertToRadians(mTransform.rotation.z));
	// 行列は掛け算で合成できる （注）掛ける順番が影響する
	cb.matrixWorld = matrixScale * matrixRotate * matrixMove;
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UVアニメーションの行列作成
	// XMMatrixTranslation＝移動行列を作る関数
	cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	// XMMatrixTranspose＝転置行列を作る
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	// 色を変更
	cb.materialDiffuse = materialDiffuse;

	// 行列をシェーダーに渡す
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL,
		&cb, 0, 0);

	// 今からDrawする頂点バッファ（モデル）を指定する
	m_pImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer,
		&strides, &offsets);
	// ピクセルシェーダーにテクスチャを渡す
	m_pImmediateContext->PSSetShaderResources(0, 1, &mTexture);
	// 第１引数　→　描画する頂点数
	m_pImmediateContext->Draw(6, 0); // 描画命令
}

void UI::MakeDotween()
{
	if (dotween != nullptr) return;

	dotween = new DoTweenUI(this);
}

void UI::SetColor(DirectX::XMFLOAT3 _color)
{
	// 255 = 1.0fにする割合
	float cr = 1.0f / 255;
	materialDiffuse = { cr * _color.x, cr * _color.y, cr * _color.z, materialDiffuse.w };

	// 範囲超えてたら修正
	float* check = &materialDiffuse.x;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			break;

		case 1:
			check = &materialDiffuse.y;
			break;

		case 2:
			check = &materialDiffuse.z;
			break;
		}

		// 範囲内に収める
		if (*check < 0)
		{
			*check = 0.0f;
		}
		else if(*check > 1.0f)
		{
			*check = 1.0f;
		}
	}
}

void UI::SetAlpha(float _alpha)
{
	if (_alpha < 0.0f)
	{
		_alpha = 0.0f;
	}
	else if (_alpha > 1.0f)
	{
		_alpha = 1.0f;
	}

	materialDiffuse.w = _alpha;
}
