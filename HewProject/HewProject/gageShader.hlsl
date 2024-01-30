//角度
float Angle : register(t1);
//カラーテクスチャ
Texture2D<float4> Texture : register(t0);
//サンプラー
sampler TextureSampler : register(s0);

//ピクセルシェーダー
//引き数はこれで固定です、多分
float4 ps_main(
	float4 color : COLOR0,
	float2 texCoord : TEXCOORD0) : SV_Target0
{
	float PI = 3.14159f;
//こっからなんかおかしいかもしれません
float2 Center = {0.5f,0.5f};
float2 Up = { 0.5f,1.0f };
float2 Vector1 = {0.0f,-1.0f};
float2 Vector2 = texCoord - Center;
Vector1 = normalize(Vector1);
Vector2 = normalize(Vector2);
float Deg = acos(dot(Vector1, Vector2));
Deg = abs(Deg);
//中心からピクセルの座標へのベクトルと中心から上方向へのベクトルの内積を求め
//逆コサインをとり、設定した角度より小さければ表示、大きければピクセルを破棄する
if (Vector2.x < Vector1.x) {
	Deg = PI + (PI - Deg);
}
if (Deg >= Angle) {
	//ピクセルを破棄する
	clip(-1);
}
float4 Color = Texture.Sample(TextureSampler, texCoord);
return Color;
}