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
	// DoTweenの種類列挙型
	enum class TYPE
	{
		NONE,
		MOVE,
		SCALE
	};
	CObject* objptr;	// オブジェクトのポインタ
	float nowTime;	// Dotween始まった時の時間(ms)
	float moveTime;	// 移動にかかる時間(ms)
	float moveSpeed;	// 移動速度(引数で時間を使わない関数で使われる)
	float curvePos;
	bool IsDoMove;	// Dotweenのフラグ
	TYPE state;	// Dotweenの種類変数
	Vector3 moveDir;	// 移動方向(X,Y,Z軸)
	Vector3 oldPos;	// カーブで使う
	Vector3 targetPos;	// 目標の座標 

	/// <summary>
	/// 2点間の単位ベクトルを求める
	/// </summary>
	/// <param name="_start">始点</param>
	/// <param name="_target">終点</param>
	/// <returns>単位ベクトル</returns>
	Vector3 GetVector(Vector3 _start, Vector3 _end);

	/// <summary>
	/// MoveX等で使われるベクトルを求める
	/// </summary>
	/// <param name="_start"></param>
	/// <param name="_end"></param>
	/// <returns></returns>
	float GetVector(float _start, float _end);

	/// <summary>
	/// 速度を求める
	/// </summary>
	/// <param name="_start">始点</param>
	/// <param name="_end">終点</param>
	/// <param name="_time">時間(s)</param>
	/// <returns>速度</returns>
	float GetSpeed(Vector3 _start, Vector3 _end, float _time);

public:
	void Update();

	DoTween();
	~DoTween();

	/// <summary>
	/// 目的の座標に何秒で移動する関数
	/// </summary>
	/// <param name="_Objptr">対象のオブジェクトのポインタ</param>
	/// <param name="_targetPos">目的座標</param>
	/// <param name="_moveTime">移動時間</param>
	void DoMove(CObject* _Objptr, Vector3 _targetPos, float _moveTime);

	void DoMoveX(CObject* _Objptr, float _targetPosX, float _moveTime);

	void DoMoveY(CObject* _Objptr, float _targetPosY, float _moveTime);

	void DoScale(CObject* _Objptr, Vector3 _targetScale, float _moveTime);

	void DoScaleDown(CObject* _Objptr, float _moveSpeed, float _moveTime);
	void DoMoveCurve(CObject* _Objptr, Vector3 _movePos, float _curvePos, float _moveTime);
};

