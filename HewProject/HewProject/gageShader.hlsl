//�p�x
float Angle : register(t1);
//�J���[�e�N�X�`��
Texture2D<float4> Texture : register(t0);
//�T���v���[
sampler TextureSampler : register(s0);

//�s�N�Z���V�F�[�_�[
//�������͂���ŌŒ�ł��A����
float4 ps_main(
	float4 color : COLOR0,
	float2 texCoord : TEXCOORD0) : SV_Target0
{
	float PI = 3.14159f;
//��������Ȃ񂩂���������������܂���
float2 Center = {0.5f,0.5f};
float2 Up = { 0.5f,1.0f };
float2 Vector1 = {0.0f,-1.0f};
float2 Vector2 = texCoord - Center;
Vector1 = normalize(Vector1);
Vector2 = normalize(Vector2);
float Deg = acos(dot(Vector1, Vector2));
Deg = abs(Deg);
//���S����s�N�Z���̍��W�ւ̃x�N�g���ƒ��S���������ւ̃x�N�g���̓��ς�����
//�t�R�T�C�����Ƃ�A�ݒ肵���p�x��菬������Ε\���A�傫����΃s�N�Z����j������
if (Vector2.x < Vector1.x) {
	Deg = PI + (PI - Deg);
}
if (Deg >= Angle) {
	//�s�N�Z����j������
	clip(-1);
}
float4 Color = Texture.Sample(TextureSampler, texCoord);
return Color;
}