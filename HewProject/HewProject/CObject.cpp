#include "CObject.h"

#include "CCamera.h"

using namespace DirectX;

CObject::CObject()
{
}

CObject::~CObject()
{
	CLASS_DELETE(mAnim);
}

CObject::CObject(D3DBUFFER vb, D3DTEXTURE tex)
{
	// 各種設定
	mVertexBuffer = vb;
	mTexture = tex;
	mTransform.scale = { 1.0f,1.0f,1.0f };
	// カメラのポインタを渡す
	mCamera = CCamera::GetInstance();
}


void CObject::Update()
{
}

void CObject::LateUpdate()
{
}

void CObject::Draw()
{
	if (!isActive || IsInvisible) return;

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
	cb.matrixProj = XMMatrixOrthographicLH(SCREEN_RATIO_W * mCamera->scaleScreen, SCREEN_RATIO_H * mCamera->scaleScreen, 0.0f, 3.0f);
	// XMMatrixTranspose = 転置行列を作る(並び方を整える）
	// カメラを反映
	cb.matrixProj = XMMatrixTranspose(matrixView * cb.matrixProj);

	// ワールド変換行列の作成
	// 移動行列
	// gCamera（カメラ）からの相対的な座標で描画する
	XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x * mCamera->scaleScreen, mTransform.pos.y * mCamera->scaleScreen, mTransform.pos.z);
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

void CObject::SetDir(Vector3 setdir)
{
	mDir = setdir;
}

void CObject::ChangeInvisible()
{
	IsInvisible = !IsInvisible;
}
