#include "CItem.h"
#include "CCamera.h"

#define FLOAT_SPEED (2.0f)	// ふわふわ浮く速さ
#define HALF_AMPLITUDE_SIZE (0.07f)	// ふわふわ浮く動きの半分の振幅
#define MAX_MOVEMENT (360)	// ムーブメントの最大値

#define SHADOW_SCALETIMES (0.8f)	// アイテムの大きさに掛け合わせる
#define ITEMTOSHADOW_DISY_TIMES (0.30f)	// スケールと掛け合わせるアイテムと影との距離係数
#define ITEMTOSHADOW_DISZ (0.001f)	// アイテムと影とのZ座標距離
using namespace DirectX;

CItem::CItem(D3DBUFFER vb, D3DTEXTURE tex)
	: CGridObject(vb, tex)
{
	shadow = new CShadow(vb, NULL);
}

CItem::~CItem()
{
	CLASS_DELETE(shadow);
}

void CItem::Update()
{
	CGridObject::Update();

	drawPos.x = mTransform.pos.x;
	drawPos.z = mTransform.pos.z;

	// ふわふわ浮かせる
	movement += FLOAT_SPEED;
	// 最大値を超えたら
	if (movement > MAX_MOVEMENT)
	{
		//最大値を引く
		movement -= MAX_MOVEMENT;
	}
	drawPos.y = mTransform.pos.y + HALF_AMPLITUDE_SIZE *  mTransform.scale.y 
		* sin(XMConvertToRadians(movement));

	FloatingFluffy();
}

void CItem::FloatingFluffy()
{
	
}

void CItem::Draw()
{
	if (!isActive) return;

	shadow->Draw();

	// uv座標を宣言
	FLOAT_XY uv = { 0,0 };

	// アニメーションするオブジェクトなら
	if (mAnim != nullptr)
	{
		// アニメーションの更新
		mAnim->Update();
		// uv座標を取得
		uv = mAnim->GetUV();
	}

	ConstBuffer cb;

	// View変換行列の作成　＝　カメラ用の行列
	XMVECTOR eye = XMVectorSet(mCamera->GetPos().x, mCamera->GetPos().y, -1, 0); // 視点の位置（カメラの位置）
	XMVECTOR focus = XMVectorSet(mCamera->GetPos().x, mCamera->GetPos().y, 1, 0);	// 見ている位置
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);	// カメラの上方向
	XMMATRIX matrixView = XMMatrixLookAtLH(eye, focus, up);

	//float scaleScreen = 1.0f;	// 画像の大きさ（値が小さくなるほど画像は大きくなる）

	// 平行投影の行列作成
	// 引数　①②：映し出す面の横縦の長さ　
	// 　　　③④：映し出す空間の奥行（手前と最奥の距離）
	cb.matrixProj = XMMatrixOrthographicLH(SCREEN_RATIO_W * mCamera->scaleScreen * mCamera->mTransform.scale.x, SCREEN_RATIO_H * mCamera->scaleScreen * mCamera->mTransform.scale.y, 0.0f, 3.0f);
	// XMMatrixTranspose = 転置行列を作る(並び方を整える）
	// カメラを反映
	cb.matrixProj = XMMatrixTranspose(matrixView * cb.matrixProj);

	// ワールド変換行列の作成
	// 移動行列
	// gCamera（カメラ）からの相対的な座標で描画する
	XMMATRIX matrixMove = XMMatrixTranslation(drawPos.x * mCamera->scaleScreen, drawPos.y * mCamera->scaleScreen, drawPos.z);
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

void CItem::InitItem(D3DTEXTURE _shadowTex)
{
	SetShadow(_shadowTex);

	// 描画座標を設定する
	drawPos = mTransform.pos;
}

void CItem::SetShadow(D3DTEXTURE _shadowTex)
{
	// 影のテクスチャを設定する
	shadow->SetTexture(_shadowTex);
	// 大きさをアイテムと同じ大きさにする
	shadow->mTransform.scale = { mTransform.scale.x * SHADOW_SCALETIMES, mTransform.scale.y * SHADOW_SCALETIMES, 1.0f };

	// 影の座標を設定する
	shadow->mTransform.pos = mTransform.pos;
	shadow->mTransform.pos.y -= mTransform.scale.y * ITEMTOSHADOW_DISY_TIMES;
	shadow->mTransform.pos.z += ITEMTOSHADOW_DISZ;
}
