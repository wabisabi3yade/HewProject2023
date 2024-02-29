#include "CItem.h"
#include "CCamera.h"

#define FLOAT_SPEED (2.0f)	// �ӂ�ӂ핂������
#define HALF_AMPLITUDE_SIZE (0.07f)	// �ӂ�ӂ핂�������̔����̐U��
#define MAX_MOVEMENT (360)	// ���[�u�����g�̍ő�l

#define SHADOW_SCALETIMES (0.8f)	// �A�C�e���̑傫���Ɋ|�����킹��
#define ITEMTOSHADOW_DISY_TIMES (0.30f)	// �X�P�[���Ɗ|�����킹��A�C�e���Ɖe�Ƃ̋����W��
#define ITEMTOSHADOW_DISZ (0.001f)	// �A�C�e���Ɖe�Ƃ�Z���W����
using namespace DirectX;

CItem::CItem(D3DBUFFER vb, D3DTEXTURE tex)
	: CGridObject(vb, tex)
{
	shadow = new CShadow(vb, NULL);
}

CItem::~CItem()
{
	CLASS_DELETE(shadow);
}

void CItem::Update()
{
	CGridObject::Update();

	drawPos.x = mTransform.pos.x;
	drawPos.z = mTransform.pos.z;

	// �ӂ�ӂ핂������
	movement += FLOAT_SPEED;
	// �ő�l�𒴂�����
	if (movement > MAX_MOVEMENT)
	{
		//�ő�l������
		movement -= MAX_MOVEMENT;
	}
	drawPos.y = mTransform.pos.y + HALF_AMPLITUDE_SIZE *  mTransform.scale.y 
		* sin(XMConvertToRadians(movement));

	FloatingFluffy();
}

void CItem::FloatingFluffy()
{
	
}

void CItem::Draw()
{
	if (!isActive) return;

	shadow->Draw();

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
	cb.matrixProj = XMMatrixOrthographicLH(SCREEN_RATIO_W * mCamera->scaleScreen * mCamera->mTransform.scale.x, SCREEN_RATIO_H * mCamera->scaleScreen * mCamera->mTransform.scale.y, 0.0f, 3.0f);
	// XMMatrixTranspose = �]�u�s������(���ѕ��𐮂���j
	// �J�����𔽉f
	cb.matrixProj = XMMatrixTranspose(matrixView * cb.matrixProj);

	// ���[���h�ϊ��s��̍쐬
	// �ړ��s��
	// gCamera�i�J�����j����̑��ΓI�ȍ��W�ŕ`�悷��
	XMMATRIX matrixMove = XMMatrixTranslation(drawPos.x * mCamera->scaleScreen, drawPos.y * mCamera->scaleScreen, drawPos.z);
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

void CItem::InitItem(D3DTEXTURE _shadowTex)
{
	SetShadow(_shadowTex);

	// �`����W��ݒ肷��
	drawPos = mTransform.pos;
}

void CItem::SetShadow(D3DTEXTURE _shadowTex)
{
	// �e�̃e�N�X�`����ݒ肷��
	shadow->SetTexture(_shadowTex);
	// �傫�����A�C�e���Ɠ����傫���ɂ���
	shadow->mTransform.scale = { mTransform.scale.x * SHADOW_SCALETIMES, mTransform.scale.y * SHADOW_SCALETIMES, 1.0f };

	// �e�̍��W��ݒ肷��
	shadow->mTransform.pos = mTransform.pos;
	shadow->mTransform.pos.y -= mTransform.scale.y * ITEMTOSHADOW_DISY_TIMES;
	shadow->mTransform.pos.z += ITEMTOSHADOW_DISZ;
}
