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
	if (dotween != nullptr)
	{
		dotween->Update();
	}
}

void UI::Draw()
{
	if (!isActive) return;  // 非表示なら処理終了

	// uv座標を宣言
	FLOAT_XY uv = { 0,0 };

	// アニメーションするオブジェクトなら
	if (mAnim != nullptr)
	{
		//アニメーションの更新
			mAnim->Update();
		//uv座標を取得
			uv = mAnim->GetUV();

		if (!mAnim->isPlaying) return;
	}

	ConstBuffer cb;
	// 投影行列を単位行列にすることで、仮想世界ではなく直接仮想画面にポリゴンを配置できる    
	cb.matrixProj = XMMatrixIdentity();
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
	// uv座標を宣言
	//FLOAT_XY uv = { 0,0 };

	// アニメーションするオブジェクトなら
	//if (mAnim != nullptr)
	//{
	//	 アニメーションの更新
	//	mAnim->Update();
	//	 uv座標を取得
	//	uv = mAnim->GetUV();

	//	if (!mAnim->isPlaying) return;
	//}

	//ConstBuffer cb;


	//float scaleScreen = 1.0f;	// 画像の大きさ（値が小さくなるほど画像は大きくなる）

	// 平行投影の行列作成
	// 引数　①②：映し出す面の横縦の長さ　
	// 　　　③④：映し出す空間の奥行（手前と最奥の距離）
	//cb.matrixProj = XMMatrixOrthographicLH(16.0f, 9.0f, -1.0f, 3.0f);
	// XMMatrixTranspose = 転置行列を作る(並び方を整える）

	// ワールド変換行列の作成
	// 移動行列
	// gCamera（カメラ）からの相対的な座標で描画する
	//XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x, mTransform.pos.y , mTransform.pos.z);
	// 拡大縮小行列
	//XMMATRIX matrixScale = XMMatrixScaling(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);
	// 回転行列(Z軸）
	//XMMATRIX matrixRotZ = XMMatrixRotationZ(XMConvertToRadians(mTransform.rotation.z));

	// 行列は掛け算で合成できる ※掛ける順番が影響する
	//cb.matrixWorld = matrixScale * matrixRotZ * matrixMove;
	// XMMatrixTranspose = 転置行列を作る(並び方を整える）
	//cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UVアニメーションの行列作成
	// XMMatrixTranslation = 移動行列を作る関数
	//cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	//cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	//cb.materialDiffuse = materialDiffuse;

	// 行列をシェーダーに渡す
	// cbのデータを
	//m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	// 今からDrawする頂点バッファ（モデル）を指定する
	//m_pImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// テクスチャをピクセルシェーダーに渡す
	//m_pImmediateContext->PSSetShaderResources(0, 1, &mTexture);

	// モデルを描画する命令
	// 第１引数：描画する頂点数
	//m_pImmediateContext->Draw(6, 0);
}

void UI::MakeDotween()
{
	if (dotween != nullptr) return;

	dotween = new DoTweenUI(this);
}
