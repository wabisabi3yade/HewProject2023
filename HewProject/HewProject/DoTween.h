#pragma once
#include "CObject.h"
enum MOVEDIR
{
	NONE,
	RIGHT,
	LEFT,
	UP,
	DOWN,
	TO_TOP_LEFT,
	TO_TOP_RIGHT,
	TO_BOTTOM_LEFT,
	TO_BOTTOM_RIGHT,
};

class DoTween
{
private:
	// DoTween�̎�ޗ񋓌^
	enum class TYPE
	{
		NONE,
		MOVE,
		SCALE
	};
	CObject* objptr;	// �I�u�W�F�N�g�̃|�C���^
	float nowTime;	// Dotween�n�܂������̎���(ms)
	float moveTime;	// �ړ��ɂ����鎞��(ms)
	float moveSpeed;	// �ړ����x(�����Ŏ��Ԃ��g��Ȃ��֐��Ŏg����)
	float curvePos;
	bool IsDoMove;	// Dotween�̃t���O
	TYPE state;	// Dotween�̎�ޕϐ�
	Vector3 moveDir;	// �ړ�����(X,Y,Z��)
	Vector3 oldPos;	// �J�[�u�Ŏg��
	Vector3 targetPos;	// �ڕW�̍��W 

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

public:
	void Update();

	DoTween();
	~DoTween();

	/// <summary>
	/// �ړI�̍��W�ɉ��b�ňړ�����֐�
	/// </summary>
	/// <param name="_Objptr">�Ώۂ̃I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_targetPos">�ړI���W</param>
	/// <param name="_moveTime">�ړ�����</param>
	void DoMove(CObject* _Objptr, Vector3 _targetPos, float _moveTime);

	void DoMoveX(CObject* _Objptr, float _targetPosX, float _moveTime);

	void DoMoveY(CObject* _Objptr, float _targetPosY, float _moveTime);

	void DoScale(CObject* _Objptr, Vector3 _targetScale, float _moveTime);

	void DoScaleDown(CObject* _Objptr, float _moveSpeed, float _moveTime);
	void DoMoveCurve(CObject* _Objptr, Vector3 _movePos, float _curvePos, float _moveTime);
};

