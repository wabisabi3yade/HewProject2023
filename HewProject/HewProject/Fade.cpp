#include "Fade.h"
#include "CObject.h"

Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	mTransform.pos = {};
	mTransform.rotation = {};
	mTransform.scale = { 1,1,1 };

	mTexture = NULL;

	D3D_CreateSquare({ 1,1 }, &mVertexBuffer);

}

// �`��Ɏg�p����e�N�X�`��
Fade::~Fade()
{
	
}

Fade* Fade::GetInstance()
{
	// �쐬���Ă��Ȃ��Ȃ�
	if (instance == nullptr)
	{
		instance = new Fade();
	}

	return instance;
}

void Fade::Delete()
{
	CLASS_DELETE(instance);
}

void Fade::Update()
{
	if (!isActive) return;
}

void Fade::Draw()
{
	if (!isActive) return;

	// uv���W��錾
	FLOAT_XY uv = { 0,0 };

	ConstBuffer cb;

	float scaleScreen = 1.0f;	// �摜�̑傫���i�l���������Ȃ�قǉ摜�͑傫���Ȃ�j

	// ���s���e�̍s��쐬
	// �����@�@�A�F�f���o���ʂ̉��c�̒����@
	// �@�@�@�B�C�F�f���o����Ԃ̉��s�i��O�ƍŉ��̋����j
	cb.matrixProj = XMMatrixOrthographicLH(SCREEN_RATIO_W, SCREEN_RATIO_H, 0.0f, 3.0f);
	// XMMatrixTranspose = �]�u�s������(���ѕ��𐮂���j
	cb.matrixProj = XMMatrixTranspose(cb.matrixProj);

	// ���[���h�ϊ��s��̍쐬
	// �ړ��s��
	// gCamera�i�J�����j����̑��ΓI�ȍ��W�ŕ`�悷��
	XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x , mTransform.pos.y, mTransform.pos.z);
	// �g��k���s��
	XMMATRIX matrixScale = XMMatrixScaling(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);
	// ��]�s��(Z���j
	XMMATRIX matrixRotZ = XMMatrixRotationZ(XMConvertToRadians(mTransform.rotation.z));

	// �s��͊|���Z�ō����ł��� ���|���鏇�Ԃ��e������
	cb.matrixWorld = matrixScale * matrixRotZ * matrixMove;
	// XMMatrixTranspose = �]�u�s������(���ѕ��𐮂���j
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UV�A�j���[�V�����̍s��쐬
	// XMMatrixTranslation = �ړ��s������֐�
	cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	cb.materialDiffuse = materialDiffuse;

	// �s����V�F�[�_�[�ɓn��
	// cb�̃f�[�^��
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	// ������Draw���钸�_�o�b�t�@�i���f���j���w�肷��
	m_pImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// �e�N�X�`�����s�N�Z���V�F�[�_�[�ɓn��
	m_pImmediateContext->PSSetShaderResources(0, 1, &mTexture);

	// ���f����`�悷�閽��
	// ��P�����F�`�悷�钸�_��
	m_pImmediateContext->Draw(6, 0);
}

