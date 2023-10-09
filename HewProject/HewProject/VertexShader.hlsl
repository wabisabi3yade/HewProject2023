// ���_�V�F�[�_�[

// ���_�f�[�^�i�󂯎��p�j
struct VS_IN
{
	float4 pos : POSITION0;
	float2 tex : TEX; // UV���W������
};

// ���_�f�[�^�i���M�p�j
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD; // UV���W������
};

// �O���[�o���ϐ��̐錾
// �萔�o�b�t�@�󂯎��p
cbuffer ConstBuffer : register (b0)	//b0��0�߂̃o�b�t�@�Ɩ��O���Ă���
{
	// UV���W�ړ��s��
	matrix matrixTex;
	// ���e�s��
	matrix matrixProj;
	// ���[���h�ϊ��s��
	matrix matrixWorld;
	// �}�e���A���F
	float4 materialDiffuse;
}

// ���_�V�F�[�_�[�̃G���g���|�C���g
// �������钸�_�f�[�^�������ɓ����ēn�����
// vs_main���ł�����������i�Ⴆ�Έړ����j�A���ʂ̃f�[�^��return����B
VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;

	// ���[���h�ϊ��s��𒸓_�ɂ�����(��ɂ��̍s��ŃL�����N�^�[�𓮂����ā��̍s��ŃJ�����𓮂����j
	input.pos = mul(input.pos, matrixWorld);	// mul�͍s��̊|���Z������Ƃ��Ɏg��

	// ���s���e�̂��ߍs��𒸓_�Ɋ|����
	output.pos = mul(input.pos, matrixProj);	

	// U���W���ړ�������
	float4 uv;
	uv.xy = input.tex;	//�s��|���Z�̂���float4�^�Ɉڂ�
	uv.z = 0.0f;
	uv.w = 1.0f;
	uv = mul(uv, matrixTex);	// UV���W�ƈړ��s����|���Z
		
	output.tex = uv.xy;	// �|���Z�̌��ʂ𑗐M�p�ϐ��ɃZ�b�g

	return output;
}