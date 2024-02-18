#pragma once
#include "CAnimation.h"
class CPlayerAnim :
    public CAnimation
{
public:
    enum class PATTERN
    {
        STAY_DOWN,	// �ҋ@��
        STAY_LEFT,	// �ҋ@��
        STAY_RIGHT,	// �ҋ@�E
        STAY_UP,	// �ҋ@��

        WALK_DOWN,	// ������
        WALK_LEFT,	// ������
        WALK_RIGHT,	// �����E
        WALK_UP,    // ������

        PANIC_DOWN, //�ł��Ă��������
        PANIC_LEFT, //�ł��Ă��������
        PANIC_RIGHT,//�ł��Ă�������E
        PANIC_UP,   //�ł��Ă��������

        CANNON_DOWN, //��C�̓�����
        CANNON_LEFT, //��C�̓�����
        CANNON_RIGHT,//��C�̓����E
        CANNON_UP,   //��C�̓�����

        EAT_RIGHT,   //�H�ׂ�E����
        EAT_LEFT,    //�H�ׂ鍶����

        PUNCH,       //�p���`

        //�o�E���N�[�w���̓���
        BAUM,

        //�S�[���p�̃p���`
        GALL_PUNCH,

        //�S�[���p�̐H�ׂ�A�j���[�V����
        GALL_EAT,

        //�v���C���[�}�b�`���ɂȂ�Ƃ��̃A�j���[�V����
        MAKEOVER_RIGHT,
        MAKEOVER_LEFT,
    };
private:
    float AnimSpeedRate;
    bool Now_IsFall;
    bool Old_IsFall;
public:
    CPlayerAnim();
    ~CPlayerAnim();
    void Update()override;
    void PlayWalk(int num , float _animSpeedRate = 1.0f);
    void StopWalk(int _num = 0);
    void PlayFall(int _num, float _animSpeedRate = 1.0f);
    void PlayCannon(int _dir, float _animSpeedRate = 1.0f);
    void PlayEat(int _dir, float _animSpeedRate = 1.0f);
    void PlayPunch( float _animSpeedRate = 1.0f , bool _isGall = false);
    void PlayBaum(int _dir, float _animSpeedRate);
    bool GetIsFall() { return Now_IsFall; }
    bool GetOldIsFall() { return Old_IsFall; }
    void SetIsFall(bool _isFall) { Now_IsFall = _isFall ;}
    void SetAnimSpeedRate(float _animSpeedRate) { AnimSpeedRate = _animSpeedRate; }
    void PlayGallEat(float _animSpeedRate = 1.0f);
    void PlayMakeover(int _dir , float _animSpeedRate = 1.0f);
};

