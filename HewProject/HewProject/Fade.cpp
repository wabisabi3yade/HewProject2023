#include "Fade.h"
#include "CObject.h"

Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	mTransform.pos = {};
	mTransform.rotation = {};
	mTransform.scale = { 1,1,1 };

	mTexture = NULL;

	D3D_CreateSquare({ 1,1 }, &mVertexBuffer);

}

// 描画に使用するテクスチャ
Fade::~Fade()
{
	
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
}

void Fade::Draw()
{
	if (!isActive) return;

	// uv座標を宣言
	FLOAT_XY uv = { 0,0 };

	ConstBuffer cb;

	float scaleScreen = 1.0f;	// 画像の大きさ（値が小さくなるほど画像は大きくなる）

	// 平行投影の行列作成
	// 引数　①②：映し出す面の横縦の長さ　
	// 　　　③④：映し出す空間の奥行（手前と最奥の距離）
	cb.matrixProj = XMMatrixOrthographicLH(SCREEN_RATIO_W, SCREEN_RATIO_H, 0.0f, 3.0f);
	// XMMatrixTranspose = 転置行列を作る(並び方を整える）
	cb.matrixProj = XMMatrixTranspose(cb.matrixProj);

	// ワールド変換行列の作成
	// 移動行列
	// gCamera（カメラ）からの相対的な座標で描画する
	XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x , mTransform.pos.y, mTransform.pos.z);
	// 拡大縮小行列
	XMMATRIX matrixScale = XMMatrixScaling(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);
	// 回転行列(Z軸）
	XMMATRIX matrixRotZ = XMMatrixRotationZ(XMConvertToRadians(mTransform.rotation.z));

	// 行列は掛け算で合成できる ※掛ける順番が影響する
	cb.matrixWorld = matrixScale * matrixRotZ * matrixMove;
	// XMMatrixTranspose = 転置行列を作る(並び方を整える）
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UVアニメーションの行列作成
	// XMMatrixTranslation = 移動行列を作る関数
	cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	cb.materialDiffuse = materialDiffuse;

	// 行列をシェーダーに渡す
	// cbのデータを
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	// 今からDrawする頂点バッファ（モデル）を指定する
	m_pImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// テクスチャをピクセルシェーダーに渡す
	m_pImmediateContext->PSSetShaderResources(0, 1, &mTexture);

	// モデルを描画する命令
	// 第１引数：描画する頂点数
	m_pImmediateContext->Draw(6, 0);
}

