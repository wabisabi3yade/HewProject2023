#include "CObject.h"

#include "CCamera.h"

using namespace DirectX;

CObject::CObject()
{
}

CObject::~CObject()
{
	CLASS_DELETE(mAnim);
}

CObject::CObject(D3DBUFFER vb, D3DTEXTURE tex)
{
	// �e��ݒ�
	mVertexBuffer = vb;
	mTexture = tex;
	mTransform.scale = { 1.0f,1.0f,1.0f };
	// �J�����̃|�C���^��n��
	mCamera = CCamera::GetInstance();
}


void CObject::Update()
{
}

void CObject::LateUpdate()
{
}

void CObject::Draw()
{
	if (!isActive || IsInvisible) return;

	// uv���W��錾
	FLOAT_XY uv = { 0,0 };

	// �A�j���[�V��������I�u�W�F�N�g�Ȃ�
	if (mAnim != nullptr)
	{
		// �A�j���[�V�����̍X�V
		mAnim->Update();
		// uv���W���擾
		uv = mAnim->GetUV();
	}

	ConstBuffer cb;

	// View�ϊ��s��̍쐬�@���@�J�����p�̍s��
	XMVECTOR eye = XMVectorSet(mCamera->GetPos().x, mCamera->GetPos().y, -1, 0); // ���_�̈ʒu�i�J�����̈ʒu�j
	XMVECTOR focus = XMVectorSet(mCamera->GetPos().x, mCamera->GetPos().y, 1, 0);	// ���Ă���ʒu
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);	// �J�����̏����
	XMMATRIX matrixView = XMMatrixLookAtLH(eye, focus, up);

	//float scaleScreen = 1.0f;	// �摜�̑傫���i�l���������Ȃ�قǉ摜�͑傫���Ȃ�j

	// ���s���e�̍s��쐬
	// �����@�@�A�F�f���o���ʂ̉��c�̒����@
	// �@�@�@�B�C�F�f���o����Ԃ̉��s�i��O�ƍŉ��̋����j
	cb.matrixProj = XMMatrixOrthographicLH(SCREEN_RATIO_W * mCamera->scaleScreen, SCREEN_RATIO_H * mCamera->scaleScreen, 0.0f, 3.0f);
	// XMMatrixTranspose = �]�u�s������(���ѕ��𐮂���j
	// �J�����𔽉f
	cb.matrixProj = XMMatrixTranspose(matrixView * cb.matrixProj);

	// ���[���h�ϊ��s��̍쐬
	// �ړ��s��
	// gCamera�i�J�����j����̑��ΓI�ȍ��W�ŕ`�悷��
	XMMATRIX matrixMove = XMMatrixTranslation(mTransform.pos.x * mCamera->scaleScreen, mTransform.pos.y * mCamera->scaleScreen, mTransform.pos.z);
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

void CObject::SetDir(Vector3 setdir)
{
	mDir = setdir;
}

void CObject::ChangeInvisible()
{
	IsInvisible = !IsInvisible;
}
