#include "DoTween.h"
#include"Time.h"
#include <algorithm>


DoTween::DoTween(CObject* _objPtr)
{
	objPtr = _objPtr;
}

void DoTween::Update()
{
	for (auto itr1 = sequence.begin(); itr1 != sequence.end(); )
	{
		bool isDelete = false;	// 今回のループでリストを削除したかどうか
		for (auto itr2 = (*itr1).flowList.begin(); itr2 != (*itr1).flowList.end();)
		{
			// 再生しないなら返す
			if (!(*itr2).isPlay)
			{
				itr2++;
				continue;
			}
			// 現在時間が移動にかかる時間を超えていないなら
			if ((*itr2).nowTime < (*itr2).moveTime)
			{
				/*nowTime += Time::deltaTime;*/
				(*itr2).nowTime += 1.0f / 60;
				switch ((*itr2).dotweenType)
				{
				case FUNC::MOVE:
				case FUNC::MOVE_X:
				case FUNC::MOVE_Y:
				case FUNC::MOVE_Z:
					objPtr->mTransform.pos.x += (*itr2).moveDir.x * (*itr2).moveSpeed;
					objPtr->mTransform.pos.y += (*itr2).moveDir.y * (*itr2).moveSpeed;
					objPtr->mTransform.pos.z += (*itr2).moveDir.z * (*itr2).moveSpeed;
					break;

				case FUNC::SCALE:
					objPtr->mTransform.scale.x += (*itr2).moveDir.x * (*itr2).moveSpeed;
					objPtr->mTransform.scale.y += (*itr2).moveDir.y * (*itr2).moveSpeed;
					objPtr->mTransform.scale.z += (*itr2).moveDir.z * (*itr2).moveSpeed;
					break;

				case FUNC::ROTATION:
					objPtr->mTransform.rotation.x += (*itr2).moveDir.x * (*itr2).moveSpeed;
					objPtr->mTransform.rotation.y += (*itr2).moveDir.y * (*itr2).moveSpeed;
					objPtr->mTransform.rotation.z += (*itr2).moveDir.z * (*itr2).moveSpeed;
					break;
				}

				itr2++;	// 次のイテレータに進む
			}

			// 時間が終わると /////////////////////////////////////
			else
			{
				(*itr2).isPlay = false;
				switch ((*itr2).dotweenType)
				{
				case FUNC::MOVE:
				case FUNC::MOVE_X:
				case FUNC::MOVE_Y:
				case FUNC::MOVE_Z:
					objPtr->mTransform.pos = (*itr2).targetValue;
					break;

				case FUNC::SCALE:
					objPtr->mTransform.scale = (*itr2).targetValue;
					break;

				case FUNC::ROTATION:
					objPtr->mTransform.rotation = (*itr2).targetValue;
					break;
				}

				auto nextItr = std::next(itr2);

				// 終わった要素の次のものがAPPENDなら
				if (nextItr != (*itr1).flowList.end() && (*nextItr).start == START::APPEND)
				{
					// その要素のDotweenを始める
					GetValue(&*nextItr);

					// Joinの処理
					while (true)
					{
						// APPENDの次がJoinならそれも始める（それ以降もJoinならそれも）
						nextItr++;

						if ( nextItr == (*itr1).flowList.end() || 
							((*nextItr).start != START::JOIN))
						{
							break;
						}
						else
						{
							GetValue(&*nextItr);
						}

					}
				}

				// 今見ているリストで再生中の物を数える
				int count = std::count_if((*itr1).flowList.begin(), (*itr1).flowList.end(),
					[](VALUE v) {return(v.isPlay); });

				// 再生中のものがないなら
				if (count <= 0)
				{
					// OnCompleteの関数を実行する
					(*itr1).fpCallBack;

					// 永久ループは回数を引かない
					if ((*itr1).actNum != -1)
					{
						(*itr1).actNum--;
					}
					// 実行回数が0なら
					if ((*itr1).actNum == 0)
					{
						// 全て終わるとシーケンスからこのflowを削除する
						itr1 = sequence.erase(itr1);
						isDelete = true;
						break;
					}
					else
					{
						// ループ処理で必要な初期化を行う
						flowLoopSet(&(*itr1).flowList);
					}
				}
				itr2++;	// 次のイテレータに進む
			}
		}

		if (!isDelete)
		{
			itr1++;	// 次のflowに進む
		}

	}


}

void DoTween::Append(Vector3 _target, float _moveTime, FUNC _type)
{
	VALUE set;

	set.targetValue = _target;
	set.moveTime = _moveTime;
	set.dotweenType = _type;
	set.start = START::APPEND;

	set.isPlay = false;

	// シーケンスの最後の要素に追加する
	sequence.back().flowList.push_back(set);
}

void DoTween::Append(float _target, float _moveTime, FUNC _type)
{
	VALUE set;

	switch (_type)
	{
	case FUNC::MOVE_X:
		set.targetValue.x = _target;
		break;
	case FUNC::MOVE_Y:
		set.targetValue.y = _target;
		break;
	case FUNC::MOVE_Z:
		//set.targetValue.z = _target;
		break;
	}
	set.moveTime = _moveTime;
	set.dotweenType = _type;
	set.start = START::APPEND;

	set.isPlay = false;

	// シーケンスの最後の要素に追加する
	sequence.back().flowList.push_back(set);
}

void DoTween::Join(Vector3 _target, float _moveTime, FUNC _type)
{
	VALUE set;



	set.targetValue = _target;
	set.moveTime = _moveTime;
	set.dotweenType = _type;
	set.start = START::JOIN;

	set.isPlay = false;

	if (sequence.back().flowList.back().isPlay)
	{
		GetValue(&set);
	}

	// シーケンスの最後の要素に追加する
	sequence.back().flowList.push_back(set);
}

void DoTween::Join(float _target, float _moveTime, FUNC _type)
{
	VALUE set;

	switch (_type)
	{
	case FUNC::MOVE_X:
		set.targetValue.x = _target;
		break;
	case FUNC::MOVE_Y:
		set.targetValue.y = _target;
		break;
	case FUNC::MOVE_Z:
		//set.targetValue.z = _target;
		break;
	}
	set.moveTime = _moveTime;
	set.dotweenType = _type;
	set.start = START::JOIN;

	set.isPlay = false;

	if (sequence.back().flowList.back().isPlay)
	{
		GetValue(&set);
	}

	// シーケンスの最後の要素に追加する
	sequence.back().flowList.push_back(set);
}

void DoTween::SetLoop(int _loopNum)
{
	sequence.back().actNum = _loopNum;
}

void DoTween::Stop()
{
	
	sequence.clear();	// 全てを消す
}


void DoTween::DoMove(Vector3 _targetPos, float _moveTime)
{
	//　設定をする
	VALUE set;
	set.dotweenType = FUNC::MOVE;
	set.start = START::DO;
	set.targetValue = _targetPos;
	set.moveTime = _moveTime;

	// 設定したパラメータからベクトル、速度を求める
	GetValue(&set);

	// flowの最初の要素として追加する
	FLOW flow;	// 1連の流れ
	// 待機リストに追加
	flow.flowList.push_back(set);

	// シーケンスの最後にflowを入れる
	sequence.push_back(flow);


}

void DoTween::DoMoveX(float _targetPosX, float _moveTime)
{
	//　設定をする
	VALUE set;
	set.dotweenType = FUNC::MOVE_X;
	set.start = START::DO;
	set.targetValue.x = _targetPosX;
	set.moveTime = _moveTime;

	// 設定したパラメータからベクトル、速度を求める
	GetValue(&set);

	// flowの最初の要素として追加する
	FLOW flow;	// 1連の流れ
	// 待機リストに追加
	flow.flowList.push_back(set);

	// シーケンスの最後にflowを入れる
	sequence.push_back(flow);
}

void DoTween::DoMoveY(float _targetPosY, float _moveTime)
{
	//　設定をする
	VALUE set;
	set.dotweenType = FUNC::MOVE_Y;
	set.start = START::DO;
	set.targetValue.y = _targetPosY;
	set.moveTime = _moveTime;

	// 設定したパラメータからベクトル、速度を求める
	GetValue(&set);

	// flowの最初の要素として追加する
	FLOW flow;	// 1連の流れ
	// 待機リストに追加
	flow.flowList.push_back(set);

	// シーケンスの最後にflowを入れる
	sequence.push_back(flow);
}

void DoTween::DoScale(Vector3 _targetScale, float _moveTime)
{
	//　設定をする
	VALUE set;
	set.dotweenType = FUNC::SCALE;
	set.start = START::DO;
	set.targetValue = _targetScale;
	set.moveTime = _moveTime;

	// 設定したパラメータからベクトル、速度を求める
	GetValue(&set);

	// flowの最初の要素として追加する
	FLOW flow;	// 1連の流れ
	// 待機リストに追加
	flow.flowList.push_back(set);

	// シーケンスの最後にflowを入れる
	sequence.push_back(flow);
}

void DoTween::DoRotation(Vector3 _targetAngle, float _moveTime)
{
	//　設定をする
	VALUE set;
	set.dotweenType = FUNC::ROTATION;
	set.start = START::DO;
	set.targetValue = _targetAngle;
	set.moveTime = _moveTime;

	// 設定したパラメータからベクトル、速度を求める
	GetValue(&set);

	// flowの最初の要素として追加する
	FLOW flow;	// 1連の流れ
	// 待機リストに追加
	flow.flowList.push_back(set);

	// シーケンスの最後にflowを入れる
	sequence.push_back(flow);

}

void DoTween::GetValue(VALUE* _value)
{
	_value->isPlay = true;	// Dotween起動
	_value->nowTime = 0;	// 初期化

	// 単位ベクトルを求める
	switch (_value->dotweenType)
	{
	case FUNC::MOVE_X:
		_value->targetValue.y = objPtr->mTransform.pos.y;
		_value->targetValue.z = objPtr->mTransform.pos.z;
		_value->moveDir = GetVector(objPtr->mTransform.pos, _value->targetValue);
		_value->moveSpeed = GetSpeed(objPtr->mTransform.pos, _value->targetValue, _value->moveTime);
		
		break;
	case FUNC::MOVE_Y:
		_value->targetValue.x = objPtr->mTransform.pos.x;
		_value->targetValue.z = objPtr->mTransform.pos.z;
		_value->moveDir = GetVector(objPtr->mTransform.pos, _value->targetValue);
		_value->moveSpeed = GetSpeed(objPtr->mTransform.pos, _value->targetValue, _value->moveTime);
		break;

	case FUNC::MOVE_Z:

		break;

	case FUNC::MOVE:
		_value->moveDir = GetVector(objPtr->mTransform.pos, _value->targetValue);
		_value->moveSpeed = GetSpeed(objPtr->mTransform.pos, _value->targetValue, _value->moveTime);
		break;

	case FUNC::SCALE:
		_value->moveDir = GetVector(objPtr->mTransform.scale, _value->targetValue);
		_value->moveSpeed = GetSpeed(objPtr->mTransform.scale, _value->targetValue, _value->moveTime);
		break;

	case FUNC::ROTATION:
		_value->moveDir = GetVector(objPtr->mTransform.rotation, _value->targetValue);
		_value->moveSpeed = GetSpeed(objPtr->mTransform.rotation, _value->targetValue, _value->moveTime);
		break;
	}
}

Vector3 DoTween::GetVector(Vector3 _start, Vector3 _end)
{
	// ベクトルを求める
	Vector3 vec = { _end.x - _start.x,
					_end.y - _start.y,
					_end.z - _start.z };



	// ベクトルの長さを求める
	double dis = pow((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z), 0.5);

	if (dis == 0.0f)
	{
		vec = Vector3::zero;
	}
	else
	{
		// 単位ベクトルを求める
		vec = { vec.x / (float)dis,vec.y / (float)dis, vec.z / (float)dis };
	}
	return vec;

}

float DoTween::GetVector(float _start, float _end)
{
	float vec = 0;

	// 目標座標が現在の座標より正の方向にあるなら
	if (_end - _start > 0)
	{
		vec = 1;
	}
	// 負なら
	else if (_end - _start < 0)
	{
		vec = -1;
	}
	// 距離0(移動しないなら)
	else
	{
		vec = 0;
	}

	return vec;
}

float DoTween::GetSpeed(Vector3 _start, Vector3 _end, float _time)
{
	// ベクトルを求める
	Vector3 vec = { _end.x - _start.x,
					_end.y - _start.y,
					_end.z - _start.z };
	// ベクトルの長さを求める
	double dis = pow((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z), 0.5);

	float spd = dis / (_time * 60);

	/*spd *= Time::slowTime;*/

	return spd;
}

void DoTween::flowLoopSet(std::list<VALUE>* _resetList)
{
	// ループ再生するflowの最初のイテレータを取得
	auto itr = _resetList->begin();

	// 再生する処理（Do,Join）は方向ベクトルとかを求める
	while (true)
	{
		GetValue(&*itr);

		itr++;

		if ((*itr).start != START::JOIN) break;
	}
	
}



DoTween::~DoTween()
{
	sequence.clear();
}

