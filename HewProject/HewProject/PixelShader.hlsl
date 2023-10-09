// ピクセルシェーダー

// ピクセルあたりの情報（受け取り用）
struct PS_IN
{
    float4 pos : SV_POSITION; // ピクセルの位置座標
    float2 tex : TEXCOORD; // ピクセルのUV座標
};
 
// グローバル変数の宣言
// ※C言語側からデータを渡された時にセットされる変数
Texture2D myTexture : register(t0); //テクスチャー
SamplerState mySampler : register(s0); //サンプラー

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

// ピクセルシェーダーのエントリポイント
float4 ps_main( PS_IN input ) : SV_Target
{
    // Sample関数→テクスチャから該当のUV位置のピクセル色を取って来る
    float4 color = myTexture.Sample(mySampler, input.tex);
    
        // ピクセルシェーダーの役目は色を決定すること
        // 決定した色　と　マテリアル色を掛けた値をreturnする。
    return color * materialDiffuse;
}