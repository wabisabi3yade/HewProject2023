// 頂点シェーダー

// 頂点データ（受け取り用）
struct VS_IN
{
	float4 pos : POSITION0;
	float2 tex : TEX; // UV座標が入る
};

// 頂点データ（送信用）
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD; // UV座標が入る
};

// グローバル変数の宣言
// 定数バッファ受け取り用
cbuffer ConstBuffer : register (b0)	//b0は0個めのバッファと名前つけている
{
	// UV座標移動行列
	matrix matrixTex;
	// 投影行列
	matrix matrixProj;
	// ワールド変換行列
	matrix matrixWorld;
	// マテリアル色
	float4 materialDiffuse;
}

// 頂点シェーダーのエントリポイント
// 処理する頂点データが引数に入って渡される
// vs_main内でそれを処理し（例えば移動し）、結果のデータをreturnする。
VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;

	// ワールド変換行列を頂点にかける(先にこの行列でキャラクターを動かして↓の行列でカメラを動かす）
	input.pos = mul(input.pos, matrixWorld);	// mulは行列の掛け算をするときに使う

	// 平行投影のため行列を頂点に掛ける
	output.pos = mul(input.pos, matrixProj);	

	// U座標を移動させる
	float4 uv;
	uv.xy = input.tex;	//行列掛け算のためfloat4型に移す
	uv.z = 0.0f;
	uv.w = 1.0f;
	uv = mul(uv, matrixTex);	// UV座標と移動行列を掛け算
		
	output.tex = uv.xy;	// 掛け算の結果を送信用変数にセット

	return output;
}