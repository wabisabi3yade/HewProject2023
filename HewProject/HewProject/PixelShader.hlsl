// �s�N�Z���V�F�[�_�[

// �s�N�Z��������̏��i�󂯎��p�j
struct PS_IN
{
    float4 pos : SV_POSITION; // �s�N�Z���̈ʒu���W
    float2 tex : TEXCOORD; // �s�N�Z����UV���W
};
 
// �O���[�o���ϐ��̐錾
// ��C���ꑤ����f�[�^��n���ꂽ���ɃZ�b�g�����ϐ�
Texture2D myTexture : register(t0); //�e�N�X�`���[
SamplerState mySampler : register(s0); //�T���v���[

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

// �s�N�Z���V�F�[�_�[�̃G���g���|�C���g
float4 ps_main( PS_IN input ) : SV_Target
{
    // Sample�֐����e�N�X�`������Y����UV�ʒu�̃s�N�Z���F������ė���
    float4 color = myTexture.Sample(mySampler, input.tex);
    
        // �s�N�Z���V�F�[�_�[�̖�ڂ͐F�����肷�邱��
        // ���肵���F�@�Ɓ@�}�e���A���F���|�����l��return����B
    return color * materialDiffuse;
}