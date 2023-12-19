#pragma once
#include "CObject.h"
#include <list>

#include <iostream>
#include <functional>

class DoTween
{
public:
	// DoTweenの種類列挙型
	enum class FUNC
	{
		NONE,
		MOVE,
		MOVE_X,
		MOVE_Y,
		MOVE_Z,
		SCALE,
		ROTATION
	};

	// 始まるときの種類
	enum class START
	{
		DO,	// すぐ始まる
		APPEND,	// 前のが終わると始まる
		JOIN	// 前のと同タイミングで始まる
	};

	struct VALUE
	{
		bool isPlay = false;

		FUNC dotweenType = FUNC::NONE;	// Dotweenの種類変数
		START start = START::DO;	//　始まる方法の種類変数

		float nowTime = 0.0f;	// Dotween始まった時の時間(ms)
		float moveTime = 0.0f;	// 移動にかかる時間(ms)
		float moveSpeed = 0.0f;	// 移動速度
		
		Vector3 moveDir = Vector3::zero;	// 移動方向(X,Y,Z軸)
		Vector3 targetValue = Vector3::zero;	// 目標の座標 
	};

	/*template <typename T>*/
	// 1連の流れの構造体
	struct FLOW
	{
		std::list<VALUE> flowList;	// 処理をする順序（flow)
		int actNum = 1;	// 残りの実行回数(-1は永久ループ)
		std::function<void()> onComplete = nullptr;	// OnCompleteで処理するラムダ式
													//（関数実行しないならnullptr） 
	};
	
private:
	CObject* objPtr;	// 動かすオブジェクトのポインタ

	std::list<FLOW> sequence;	// シーケンス（flowを格納する）
	
	// Dotweenで使う変数（方向ベクトル、速度、再生フラグ）を決める
	void GetValue(VALUE* _value);

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

	// ループするときにリセットする
	void flowLoopSet(std::list<VALUE>* _resetList);

public:
	void Update();

	DoTween(CObject* _objPtr);

	~DoTween();

	/// <summary>
	/// 前の処理が終わると呼ばれる
	/// </summary>
	/// <param name="_target">目標の値</param>
	/// <param name="_moveTime">時間</param>
	/// <param name="_type">Dotweenの種類（DoTween::FUNC::～で呼んでね）</param>
	void Append(Vector3 _target, float _moveTime, FUNC _type);
	void Append(float _target, float _moveTime, FUNC _type);

	/// <summary>
	/// 前の処理と同じタイミングで呼ばれる
	/// </summary>
	/// <param name="_target">目標の値</param>
	/// <param name="_moveTime">時間</param>
	/// <param name="_type">Dotweenの種類（DoTween::FUNC::～で呼んでね）</param>
	void Join(Vector3 _target, float _moveTime, FUNC _type);
	void Join(float _target, float _moveTime, FUNC _type);

	/// <summary>
	/// 前のflowのループをするか決める
	/// </summary>
	/// <param name="_loopNum">ループ回数(-1は永久ループ)</param>
	void SetLoop(int _loopNum);

	
	void OnComplete(std::function<void()> _onComplete);

	/// <summary>
	/// 今、登録している処理を全て止める
	/// </summary>
	void Stop();

	/// <summary>
	/// </summary>
	/// <param name="_Objptr">対象のオブジェクトのポインタ</param>
	/// <param name="_targetPos">目的座標</param>
	/// <param name="_moveTime">移動時間</param>
	void DoMove(Vector3 _targetPos, float _moveTime);

	/// <summary>
	/// 目的のX座標まで何秒で移動する関数
	/// </summary>
	/// <param name="_Objptr">対象のオブジェクトのポインタ</param>
	/// <param name="_targetPosX">目的のX座標</param>
	/// <param name="_moveTime">移動時間</param>
	void DoMoveX(float _targetPosX, float _moveTime);

	/// <summary>
	/// 目的のY座標まで何秒で移動する関数
	/// </summary>
	/// <param name="_Objptr">対象のオブジェクトのポインタ</param>
	/// <param name="_targetPosX">目的のY座標</param>
	/// <param name="_moveTime">移動時間</param>
	void DoMoveY(float _targetPosY, float _moveTime);

	/// <summary>
	/// 目的の大きさまで何秒で変化する関数
	/// </summary>
	/// <param name="_Objptr">対象のオブジェクトのポインタ</param>
	/// <param name="_targetPosX">目的の大きさ</param>
	/// <param name="_moveTime">移動時間</param>
	void DoScale(Vector3 _targetScale, float _moveTime);

	/// <summary>
	/// 目的の角度まで何秒で回転する関数
	/// </summary>
	/// <param name="_Objptr">対象のオブジェクトのポインタ</param>
	/// <param name="_targetAngle">目的の大きさ</param>
	/// <param name="_moveTime">移動時間</param>
	void DoRotation(Vector3 _targetAngle, float _moveTime);
};

//template<typename T>
//inline void DoTween::OnComplete(T* _recive, T _send)
//{
//	// シーケンスの最後の要素に追加する
//	sequence.back().onComplete = {_recive, _send};
//}
