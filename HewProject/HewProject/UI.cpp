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
	if (!isActive) return;  // ��\���Ȃ珈���I��

	// uv���W��錾
	FLOAT_XY uv = { 0,0 };

	// �A�j���[�V��������I�u�W�F�N�g�Ȃ�
	if (mAnim != nullptr)
	{
		//�A�j���[�V�����̍X�V
			mAnim->Update();
		//uv���W���擾
			uv = mAnim->GetUV();

		if (!mAnim->isPlaying) return;
	}

	ConstBuffer cb;
	// ���e�s���P�ʍs��ɂ��邱�ƂŁA���z���E�ł͂Ȃ����ډ��z��ʂɃ|���S����z�u�ł���    
	cb.matrixProj = XMMatrixIdentity();
	cb.matrixProj = XMMatrixTranspose(cb.matrixProj);

	// ���[���h�ϊ��s��̍쐬
	// �ړ��s��
	XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x, mTransform.pos.y, mTransform.pos.z);
	// �g��k���s��
	XMMATRIX matrixScale = XMMatrixScaling(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);
	// ��]�s��@XMMatrixRotationZ�֐�
	XMMATRIX matrixRotate = XMMatrixRotationZ(XMConvertToRadians(mTransform.rotation.z));
	// �s��͊|���Z�ō����ł��� �i���j�|���鏇�Ԃ��e������
	cb.matrixWorld = matrixScale * matrixRotate * matrixMove;
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UV�A�j���[�V�����̍s��쐬
	// XMMatrixTranslation���ړ��s������֐�
	cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	// XMMatrixTranspose���]�u�s������
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);
	// �s����V�F�[�_�[�ɓn��
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL,
		&cb, 0, 0);

	// ������Draw���钸�_�o�b�t�@�i���f���j���w�肷��
	m_pImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer,
		&strides, &offsets);
	// �s�N�Z���V�F�[�_�[�Ƀe�N�X�`����n��
	m_pImmediateContext->PSSetShaderResources(0, 1, &mTexture);
	// ��P�����@���@�`�悷�钸�_��
	m_pImmediateContext->Draw(6, 0); // �`�施��
	// uv���W��錾
	//FLOAT_XY uv = { 0,0 };

	// �A�j���[�V��������I�u�W�F�N�g�Ȃ�
	//if (mAnim != nullptr)
	//{
	//	 �A�j���[�V�����̍X�V
	//	mAnim->Update();
	//	 uv���W���擾
	//	uv = mAnim->GetUV();

	//	if (!mAnim->isPlaying) return;
	//}

	//ConstBuffer cb;


	//float scaleScreen = 1.0f;	// �摜�̑傫���i�l���������Ȃ�قǉ摜�͑傫���Ȃ�j

	// ���s���e�̍s��쐬
	// �����@�@�A�F�f���o���ʂ̉��c�̒����@
	// �@�@�@�B�C�F�f���o����Ԃ̉��s�i��O�ƍŉ��̋����j
	//cb.matrixProj = XMMatrixOrthographicLH(16.0f, 9.0f, -1.0f, 3.0f);
	// XMMatrixTranspose = �]�u�s������(���ѕ��𐮂���j

	// ���[���h�ϊ��s��̍쐬
	// �ړ��s��
	// gCamera�i�J�����j����̑��ΓI�ȍ��W�ŕ`�悷��
	//XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x, mTransform.pos.y , mTransform.pos.z);
	// �g��k���s��
	//XMMATRIX matrixScale = XMMatrixScaling(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);
	// ��]�s��(Z���j
	//XMMATRIX matrixRotZ = XMMatrixRotationZ(XMConvertToRadians(mTransform.rotation.z));

	// �s��͊|���Z�ō����ł��� ���|���鏇�Ԃ��e������
	//cb.matrixWorld = matrixScale * matrixRotZ * matrixMove;
	// XMMatrixTranspose = �]�u�s������(���ѕ��𐮂���j
	//cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	// UV�A�j���[�V�����̍s��쐬
	// XMMatrixTranslation = �ړ��s������֐�
	//cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	//cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	//cb.materialDiffuse = materialDiffuse;

	// �s����V�F�[�_�[�ɓn��
	// cb�̃f�[�^��
	//m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	// ������Draw���钸�_�o�b�t�@�i���f���j���w�肷��
	//m_pImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// �e�N�X�`�����s�N�Z���V�F�[�_�[�ɓn��
	//m_pImmediateContext->PSSetShaderResources(0, 1, &mTexture);

	// ���f����`�悷�閽��
	// ��P�����F�`�悷�钸�_��
	//m_pImmediateContext->Draw(6, 0);
}

void UI::MakeDotween()
{
	if (dotween != nullptr) return;

	dotween = new DoTweenUI(this);
}
