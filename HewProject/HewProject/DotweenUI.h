#pragma once
#include <list>
#include <iostream>
#include <functional>
#include "Vector2.h"
#include "Vector3.h"

class UI;

class DoTweenUI
{
public:
	// DoTween�̎�ޗ񋓌^
	enum class FUNC
	{
		NONE,
		MOVE,
		MOVE_XY,
		MOVE_X,
		MOVE_Y,
		MOVE_Z,
		SCALE,
		ROTATION,
		MOVECURVE,
		DELAY
	};

	// �n�܂�Ƃ��̎��
	enum class START
	{
		DO,	// �����n�܂�
		APPEND,	// �O�̂��I���Ǝn�܂�
		JOIN	// �O�̂Ɠ��^�C�~���O�Ŏn�܂�
	};

	enum class STATE
	{
		WAIT,	// �ҋ@���
		PLAY,	// �Đ���
		END		// �I��
	};

	struct VALUE
	{
		STATE state = STATE::WAIT;

		FUNC dotweenType = FUNC::NONE;	// Dotween�̎�ޕϐ�
		START start = START::DO;	//�@�n�܂���@�̎�ޕϐ�
		Vector3 oldPos = {};	//	�ړ��J�n���̍��W�ێ��p�iCURVE�j
		float curvePos = 0.0f;
		float nowTime = 0.0f;	// Dotween�n�܂������̎���(ms)
		float moveTime = 0.0f;	// �ړ��ɂ����鎞��(ms)
		float moveSpeed = 0.0f;	// �ړ����x
		
		Vector3 moveDir = Vector3::zero;	// �ړ�����(X,Y,Z��)
		Vector3 targetValue = Vector3::zero;	// �ڕW�̍��W 
	};

	/*template <typename T>*/
	// 1�A�̗���̍\����
	struct FLOW
	{
		std::list<VALUE> flowList;	// ���������鏇���iflow)
		int actNum = 1;	// �c��̎��s��(-1�͉i�v���[�v)
		std::function<void()> onComplete = nullptr;	// OnComplete�ŏ������郉���_��
													//�i�֐����s���Ȃ��Ȃ�nullptr�j 
	};
	
private:
	UI* uiPtr;	// �������I�u�W�F�N�g�̃|�C���^

	std::list<FLOW> sequence;	// �V�[�P���X�iflow���i�[����j
	
	// Dotween�Ŏg���ϐ��i�����x�N�g���A���x�A�Đ��t���O�j�����߂�
	void GetValue(VALUE* _value);

	/// <summary>
	/// 2�_�Ԃ̒P�ʃx�N�g�������߂�
	/// </summary>
	/// <param name="_start">�n�_</param>
	/// <param name="_target">�I�_</param>
	/// <returns>�P�ʃx�N�g��</returns>
	Vector3 GetVector(Vector3 _start, Vector3 _end);

	/// <summary>
	/// MoveX���Ŏg����x�N�g�������߂�
	/// </summary>
	/// <param name="_start"></param>
	/// <param name="_end"></param>
	/// <returns></returns>
	float GetVector(float _start, float _end);

	/// <summary>
	/// ���x�����߂�
	/// </summary>
	/// <param name="_start">�n�_</param>
	/// <param name="_end">�I�_</param>
	/// <param name="_time">����(s)</param>
	/// <returns>���x</returns>
	float GetSpeed(Vector3 _start, Vector3 _end, float _time);

	// ���[�v����Ƃ��Ƀ��Z�b�g����
	void flowLoopSet(std::list<VALUE>* _resetList);

public:
	void Update();

	DoTweenUI(UI* _uiPtr);

	~DoTweenUI();

	/// <summary>
	/// �O�̏������I���ƌĂ΂��
	/// </summary>
	/// <param name="_target">�ڕW�̒l</param>
	/// <param name="_moveTime">����</param>
	/// <param name="_type">Dotween�̎�ށiDoTween::FUNC::�`�ŌĂ�łˁj</param>
	/// <param name="_curvepos">�W�����v���g�p����Ƃ��W�����v�̍ō��n�_(PosY�����Ă�������) </param>
	void Append(Vector3 _target, float _moveTime, FUNC _type, float _curvepos = 0);
	void Append(float _target, float _moveTime, FUNC _type, float _curvepos = 0);

	/// <summary>
	/// �O�̏����Ɠ����^�C�~���O�ŌĂ΂��
	/// </summary>
	/// <param name="_target">�ڕW�̒l</param>
	/// <param name="_moveTime">����</param>
	/// <param name="_type">Dotween�̎�ށiDoTween::FUNC::�`�ŌĂ�łˁj</param>
	void Join(Vector3 _target, float _moveTime, FUNC _type);
	void Join(float _target, float _moveTime, FUNC _type);

	/// <summary>
	/// �O��flow�̃��[�v�����邩���߂�
	/// </summary>
	/// <param name="_loopNum">���[�v��(-1�͉i�v���[�v)</param>
	void SetLoop(int _loopNum);

	
	void OnComplete(std::function<void()> _onComplete);

	/// <summary>
	/// ���A�o�^���Ă��鏈����S�Ď~�߂�
	/// </summary>
	void Stop();

	/// <summary>
	/// </summary>
	/// <param name="_Objptr">�Ώۂ̃I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_targetPos">�ړI���W</param>
	/// <param name="_moveTime">�ړ�����</param>
	void DoMove(Vector3 _targetPos, float _moveTime);

	void DoMoveXY(Vector2 _targetPos, float _moveTime);

	/// <summary>
	/// �ړI��X���W�܂ŉ��b�ňړ�����֐�
	/// </summary>
	/// <param name="_Objptr">�Ώۂ̃I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_targetPosX">�ړI��X���W</param>
	/// <param name="_moveTime">�ړ�����</param>
	void DoMoveX(float _targetPosX, float _moveTime);

	/// <summary>
	/// �ړI��Y���W�܂ŉ��b�ňړ�����֐�
	/// </summary>
	/// <param name="_Objptr">�Ώۂ̃I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_targetPosX">�ړI��Y���W</param>
	/// <param name="_moveTime">�ړ�����</param>
	void DoMoveY(float _targetPosY, float _moveTime);

	/// <summary>
	/// �ړI��Z���W�܂ŉ��b�ňړ�����֐�
	/// </summary>
	/// <param name="_Objptr">�Ώۂ̃I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_targetPosX">�ړI��Z���W</param>
	/// <param name="_moveTime">�ړ�����</param>
	void DoMoveZ(float _targetPosZ, float _moveTime);

	/// <summary>
	/// �ړI�̑傫���܂ŉ��b�ŕω�����֐�
	/// </summary>
	/// <param name="_Objptr">�Ώۂ̃I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_targetPosX">�ړI�̑傫��</param>
	/// <param name="_moveTime">�ړ�����</param>
	void DoScale(Vector3 _targetScale, float _moveTime);

	/// <summary>
	/// �ړI�̊p�x�܂ŉ��b�ŉ�]����֐�
	/// </summary>
	/// <param name="_Objptr">�Ώۂ̃I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_targetAngle">�ړI�̑傫��</param>
	/// <param name="_moveTime">�ړ�����</param>
	void DoRotation(Vector3 _targetAngle, float _moveTime);

	// �x�点�鏈��
	void DoDelay(float _delayTime);
	/// <summary>
	/// �ړI�̍��W�܂łɃJ�[�u���Ȃ���ړ�����֐�
	/// </summary>
	/// <param name="_targetPosXY">�ړI��XY���W</param>
	/// <param name="_moveTime">�ړ�����</param>
	/// <param name="_curvePos">�J�[�u����ő�̍���</param>
	void DoMoveCurve(Vector2 _targetPosXY, float _moveTime ,float _curvePos = 1.0f);

	// ����ȍ~�̏�����x�点��
	void AppendDelay(float _delayTime);

	// ���b��Ɏ��s���鏈��
	void DelayedCall(float _delayTime, std::function<void()> _onComplete);
};