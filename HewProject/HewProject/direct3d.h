#pragma once // 重複インクルード防止

#include <d3d11.h> // DirectX11というライブラリのヘッダー
#include <DirectXMath.h>	// DirectXの数学関連のヘッダーファイル

// クラス解放するマクロ
#define CLASS_DELETE(p)	{ if( p != nullptr ) { delete p; p = nullptr; }}

// Direct3D解放を簡易化するマクロ
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

// 既存の型名を別名でも使えるようにする
typedef ID3D11ShaderResourceView* D3DTEXTURE;

typedef ID3D11Buffer* D3DBUFFER;


// 構造体の定義
// x,yを表す構造体
struct FLOAT_XY
{
	float x, y;
};

// 定数バッファ用構造体(c++からシェーダーにパラメータを渡すための構造体）
struct ConstBuffer
{
	// UV座標移動行列
	DirectX::XMMATRIX matrixTex;

	// 投影行列
	DirectX::XMMATRIX matrixProj;

	// ワールド変換行列
	DirectX::XMMATRIX matrixWorld;

	// マテリアル色
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };
};

// 関数のプロトタイプ宣言
HRESULT D3D_Create(HWND hwnd);
void    D3D_Release();

// 四角形ポリゴンを作成し、頂点バッファ生成を行う
void D3D_CreateSquare(FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb);	// **vb:ポインタ変数のアドレスが格納されたポインタ変数

// テクスチャを読み込む関数
// 第1引数：テクスチャのファイル名、第2引数：テクスチャ格納用変数のアドレス
// 戻り値：エラーチェックの結果
HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** Texture);

// 画面塗りつぶしと設定を行う関数
void D3D_ClearScreen();

//画面更新する関数
void D3D_UpdateScreen();

// グローバル変数のextern宣言（名簿だけを作成する、これで違うcppファイルからもアクセスできる）
extern ID3D11DeviceContext* m_pImmediateContext;
extern ID3D11Buffer* m_pConstantBuffer;
extern const UINT strides;
extern const UINT offsets;
extern ID3D11BlendState* m_pBlendStateAlpha;
extern ID3D11BlendState* m_pBlendStateAdditive;