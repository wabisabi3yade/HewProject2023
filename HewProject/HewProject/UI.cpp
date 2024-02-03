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
	if (!isActive) return;

	if (dotween != nullptr)
	{
		dotween->Update();
	}
}

void UI::Draw()
{
	if (!isActive) return;  // ��\���Ȃ珈���I��

	// �A�j���[�V��������I�u�W�F�N�g�Ȃ�
	if (mAnim != nullptr)
	{
		//�A�j���[�V�����̍X�V
			mAnim->Update();
		//uv���W���擾
			uv = mAnim->GetUV();
	}

	ConstBuffer cb;
	//// ���e�s���P�ʍs��ɂ��邱�ƂŁA���z���E�ł͂Ȃ����ډ��z��ʂɃ|���S����z�u�ł���    
	//cb.matrixProj = XMMatrixIdentity();
	//cb.matrixProj = XMMatrixTranspose(cb.matrixProj);

	// ���s���e�̍s��쐬
	// �����@�@�A�F�f���o���ʂ̉��c�̒����@
	// �@�@�@�B�C�F�f���o����Ԃ̉��s�i��O�ƍŉ��̋����j
	cb.matrixProj = XMMatrixOrthographicLH(16.0f, 9.0f, -1.0f, 3.0f);
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

	// �F��ύX
	cb.materialDiffuse = materialDiffuse;

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
}

void UI::MakeDotween()
{
	if (dotween != nullptr) return;

	dotween = new DoTweenUI(this);
}

void UI::SetColor(DirectX::XMFLOAT3 _color)
{
	// 255 = 1.0f�ɂ��銄��
	float cr = 1.0f / 255;
	materialDiffuse = { cr * _color.x, cr * _color.y, cr * _color.z, materialDiffuse.w };

	// �͈͒����Ă���C��
	float* check = &materialDiffuse.x;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			break;

		case 1:
			check = &materialDiffuse.y;
			break;

		case 2:
			check = &materialDiffuse.z;
			break;
		}

		// �͈͓��Ɏ��߂�
		if (*check < 0)
		{
			*check = 0.0f;
		}
		else if(*check > 1.0f)
		{
			*check = 1.0f;
		}
	}
}

void UI::SetAlpha(float _alpha)
{
	if (_alpha < 0.0f)
	{
		_alpha = 0.0f;
	}
	else if (_alpha > 1.0f)
	{
		_alpha = 1.0f;
	}

	materialDiffuse.w = _alpha;
}
