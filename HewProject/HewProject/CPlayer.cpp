#include "CPlayer.h"

// �R���X�g���N�^
CPlayer::CPlayer(float startX, float startY, float speed) : x(startX), y(startY), speed(speed), charObj(nullptr) {}

// ���͂ƈړ�����������A�b�v�f�[�g�֐�
void CPlayer::Update()
{

    // ���͂Ɋ�Â��ăv���C���[���ړ�
    x += Input::GetHorizontal() * speed;
    y += Input::GetVertical() * speed;

}

// �v���C���[��`�悷�郌���_�����O�֐�
void CPlayer::Render()
{
    D3D_CreateSquare({ 3,4 }, &charBuffer);
    D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

    charObj = new CObject(charBuffer, charTexture);
    charObj->mTransform.scale = { 3.0f,3.0f,1.0f };
}

CPlayer::~CPlayer()
{
    CLASS_DELETE(charObj);

    SAFE_RELEASE(charBuffer);

    SAFE_RELEASE(charTexture);
}

// X���W���擾����֐�
float CPlayer::GetX() const
{
    return x;
}

// Y���W���擾����֐�
float CPlayer::GetY() const
{
    return y;
}

// �v���C���[���͂���������֐�
void CPlayer::HandleInput()
{
    // �{�^���̏����͏ȗ����A���E�̈ړ��������l������

    // ���X�e�B�b�N�����������ɓ������ꍇ�A���������Ƀv���C���[���ړ�
    float horizontalInput = Input::GetHorizontal();
    x += horizontalInput * speed;

    // �E�X�e�B�b�N�����������ɓ������ꍇ�A���������Ƀv���C���[���ړ�
    float verticalInput = Input::GetVertical();
    y += verticalInput * speed;
}