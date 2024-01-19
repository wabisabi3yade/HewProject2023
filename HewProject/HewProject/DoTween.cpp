//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

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
		bool isDelete = false;	// ����̃��[�v�Ń��X�g���폜�������ǂ���

		for (auto itr2 = (*itr1).flowList.begin(); itr2 != (*itr1).flowList.end();)
		{
			// �Đ����Ȃ��Ȃ�Ԃ�
			if ((*itr2).state != STATE::PLAY)
			{
				itr2++;
				continue;
			}
			// ���ݎ��Ԃ��ړ��ɂ����鎞�Ԃ𒴂��Ă��Ȃ��Ȃ�
			if ((*itr2).nowTime <= (*itr2).moveTime - 1.0f / 60)
			{
				/*nowTime += Time::deltaTime;*/
				(*itr2).nowTime += 1.0f / 60;
				switch ((*itr2).dotweenType)
				{
				case FUNC::MOVE:
					objPtr->mTransform.pos.x += (*itr2).moveDir.x * (*itr2).moveSpeed;
					objPtr->mTransform.pos.y += (*itr2).moveDir.y * (*itr2).moveSpeed;
					objPtr->mTransform.pos.z += (*itr2).moveDir.z * (*itr2).moveSpeed;
					break;

				case FUNC::MOVE_X:
					objPtr->mTransform.pos.x += (*itr2).moveDir.x * (*itr2).moveSpeed;
					break;
				case FUNC::MOVE_Y:
					objPtr->mTransform.pos.y += (*itr2).moveDir.y * (*itr2).moveSpeed;
					break;
				case FUNC::MOVE_Z:
					objPtr->mTransform.pos.z += (*itr2).moveDir.z * (*itr2).moveSpeed;
					break;

				case FUNC::MOVE_XY:
					objPtr->mTransform.pos.x += (*itr2).moveDir.x * (*itr2).moveSpeed;
					objPtr->mTransform.pos.y += (*itr2).moveDir.y * (*itr2).moveSpeed;
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
				case FUNC::MOVECURVE:

					float t = (*itr2).nowTime * (1.0f / (*itr2).moveTime);

					//B�X�v���C���Ȑ��̌v�Z��
					objPtr->mTransform.pos.x =
						(pow((1 - t), 2) * (*itr2).oldPos.x)
						+ (2 * t) * (1 - t) * (((*itr2).oldPos.x + (*itr2).targetValue.x) / 2)
						+ (pow(t, 2) * (*itr2).targetValue.x);

					objPtr->mTransform.pos.y =
						(pow((1 - t), 2) * (*itr2).oldPos.y)
						+ (2 * t) * (1 - t) * (((*itr2).oldPos.y + (*itr2).targetValue.y) / 2 + ((*itr2).oldPos.y * 2))
						+ (pow(t, 2) * (*itr2).targetValue.y);
					break;
				}

				itr2++;	// ���̃C�e���[�^�ɐi��
				
			}

			// ���Ԃ��I���� /////////////////////////////////////
			else
			{
				(*itr2).state = STATE::END;
				switch ((*itr2).dotweenType)
				{
				case FUNC::MOVE:
					objPtr->mTransform.pos = (*itr2).targetValue;
					break;

				case FUNC::MOVE_X:
					objPtr->mTransform.pos.x = (*itr2).targetValue.x;
					break;
				case FUNC::MOVE_Y:
					objPtr->mTransform.pos.y = (*itr2).targetValue.y;
					break;
				case FUNC::MOVE_Z:
					objPtr->mTransform.pos.z = (*itr2).targetValue.z;
					break;

				case FUNC::MOVE_XY:
					objPtr->mTransform.pos.x = (*itr2).targetValue.x;
					objPtr->mTransform.pos.y = (*itr2).targetValue.y;
					break;

				case FUNC::SCALE:
					objPtr->mTransform.scale = (*itr2).targetValue;
					break;

				case FUNC::ROTATION:
					objPtr->mTransform.rotation = (*itr2).targetValue;
					break;
				case FUNC::MOVECURVE:
					objPtr->mTransform.pos.x = (*itr2).targetValue.x;
					objPtr->mTransform.pos.y = (*itr2).targetValue.y;
				}

				auto nextItr = std::next(itr2);

				// �I������v�f�̎��̂��̂�APPEND�Ȃ�
				if (nextItr != (*itr1).flowList.end() && (*nextItr).start == START::APPEND)
				{
					// ���̗v�f��Dotween���n�߂�
					GetValue(&*nextItr);

					// Join�̏���
					while (true)
					{
						// APPEND�̎���Join�Ȃ炻����n�߂�i����ȍ~��Join�Ȃ炻����j
						nextItr++;

						if (nextItr == (*itr1).flowList.end() ||
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

				// �����Ă��郊�X�g�ōĐ����̕��𐔂���
				int count = std::count_if((*itr1).flowList.begin(), (*itr1).flowList.end(),
					[](VALUE v) {return(v.state == STATE::PLAY); });

				// �Đ����̂��̂��Ȃ��Ȃ�
				if (count <= 0)
				{
					// �i�v���[�v�͉񐔂������Ȃ�
					if ((*itr1).actNum != -1)
					{
						(*itr1).actNum--;
					}
					// ���s�񐔂�0�Ȃ�
					if ((*itr1).actNum == 0)
					{
						// OnComplete�͂����Ŏ��s����//////////////

						// OnComplete�֐������s���Ă���Ȃ�
						if ((*itr1).onComplete != nullptr)
						{
							// ��������
							(*itr1).onComplete();
						}

						// �S�ďI���ƃV�[�P���X���炱��flow���폜����
						itr1 = sequence.erase(itr1);
						isDelete = true;
						break;
					}
					else
					{
						// ���[�v�����ŕK�v�ȏ��������s��
						flowLoopSet(&(*itr1).flowList);
					}
				}
				itr2++;	// ���̃C�e���[�^�ɐi��
			}
		}

		if (!isDelete)
		{
			itr1++;	// ����flow�ɐi��
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

	set.state = STATE::WAIT;

	// �V�[�P���X�̍Ō�̗v�f�ɒǉ�����
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
		set.targetValue.z = _target;
		break;
	}
	set.moveTime = _moveTime;
	set.dotweenType = _type;
	set.start = START::APPEND;

	set.state = STATE::WAIT;

	// �V�[�P���X�̍Ō�̗v�f�ɒǉ�����
	sequence.back().flowList.push_back(set);
}

void DoTween::Join(Vector3 _target, float _moveTime, FUNC _type)
{
	VALUE set;

	set.targetValue = _target;
	set.moveTime = _moveTime;
	set.dotweenType = _type;
	set.start = START::JOIN;

	set.state = STATE::WAIT;

	if (sequence.back().flowList.back().state == STATE::PLAY)
	{
		GetValue(&set);
	}

	// �V�[�P���X�̍Ō�̗v�f�ɒǉ�����
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

	set.state = STATE::WAIT;

	if (sequence.back().flowList.back().state == STATE::PLAY)
	{
		GetValue(&set);
	}

	// �V�[�P���X�̍Ō�̗v�f�ɒǉ�����
	sequence.back().flowList.push_back(set);
}

void DoTween::SetLoop(int _loopNum)
{
	sequence.back().actNum = _loopNum;
}

void DoTween::OnComplete(std::function<void()> _onComplete)
{
	sequence.back().onComplete = _onComplete;
}

void DoTween::Stop()
{

	sequence.clear();	// �S�Ă�����
}


void DoTween::DoMove(Vector3 _targetPos, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::MOVE;
	set.start = START::DO;
	set.targetValue = _targetPos;
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);


}

void DoTween::DoMoveXY(Vector2 _targetPos, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::MOVE_XY;
	set.start = START::DO;
	set.targetValue = {_targetPos.x, _targetPos.y,0};
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);
}

void DoTween::DoMoveX(float _targetPosX, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::MOVE_X;
	set.start = START::DO;
	set.targetValue.x = _targetPosX;
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);
}

void DoTween::DoMoveY(float _targetPosY, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::MOVE_Y;
	set.start = START::DO;
	set.targetValue.y = _targetPosY;
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);
}

void DoTween::DoMoveZ(float _targetPosZ, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::MOVE_Z;
	set.start = START::DO;
	set.targetValue.z = _targetPosZ;
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);
}

void DoTween::DoScale(Vector3 _targetScale, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::SCALE;
	set.start = START::DO;
	set.targetValue = _targetScale;
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);
}

void DoTween::DoRotation(Vector3 _targetAngle, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::ROTATION;
	set.start = START::DO;
	set.targetValue = _targetAngle;
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);

}

void DoTween::DoDelay(float _delayTime)
{
	//�Ȃɂ����Ȃ������i���Ԗьo�߂��邾���j
	VALUE set;
	set.dotweenType = FUNC::DELAY;
	set.start = START::DO;
	set.moveTime = _delayTime;

	set.state = STATE::PLAY;	// Dotween�N��
	set.nowTime = 0;	// ������

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);
}

void DoTween::DoMoveCurve(Vector2 _targetPosXY, float _moveTime)
{
	//�@�ݒ������
	VALUE set;
	set.dotweenType = FUNC::MOVECURVE;
	set.start = START::DO;
	set.oldPos = objPtr->mTransform.pos;
	set.targetValue = { _targetPosXY.x, _targetPosXY.y,0 };
	set.moveTime = _moveTime;

	// �ݒ肵���p�����[�^����x�N�g���A���x�����߂�
	GetValue(&set);

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);
}

void DoTween::AppendDelay(float _delayTime)
{
	VALUE set;

	set.moveTime = _delayTime;
	set.dotweenType = FUNC::DELAY;
	set.start = START::APPEND;

	set.state = STATE::WAIT;

	// �V�[�P���X�̍Ō�̗v�f�ɒǉ�����
	sequence.back().flowList.push_back(set);
}

void DoTween::DelayedCall(float _delayTime, std::function<void()> _onComplete)
{
	//�Ȃɂ����Ȃ������i���Ԗьo�߂��邾���j
	VALUE set;
	set.dotweenType = FUNC::DELAY;
	set.start = START::DO;
	set.moveTime = _delayTime;

	set.state = STATE::PLAY;	// Dotween�N��
	set.nowTime = 0;	// ������

	// flow�̍ŏ��̗v�f�Ƃ��Ēǉ�����
	FLOW flow;	// 1�A�̗���
	// �ҋ@���X�g�ɒǉ�
	flow.flowList.push_back(set);

	// �V�[�P���X�̍Ō��flow������
	sequence.push_back(flow);

	// �I�������ɏ���������
	OnComplete(_onComplete);
}

void DoTween::GetValue(VALUE* _value)
{
	_value->state = STATE::PLAY;	// Dotween�N��
	_value->nowTime = 0;	// ������

	// �P�ʃx�N�g�������߂�
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
		_value->targetValue.x = objPtr->mTransform.pos.x;
		_value->targetValue.y = objPtr->mTransform.pos.y;
		_value->moveDir = GetVector(objPtr->mTransform.pos, _value->targetValue);
		_value->moveSpeed = GetSpeed(objPtr->mTransform.pos, _value->targetValue, _value->moveTime);
		break;

	case FUNC::MOVE:
		_value->moveDir = GetVector(objPtr->mTransform.pos, _value->targetValue);
		_value->moveSpeed = GetSpeed(objPtr->mTransform.pos, _value->targetValue, _value->moveTime);
		break;

	case FUNC::MOVE_XY:
		_value->targetValue.z = objPtr->mTransform.pos.z;
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
	// �x�N�g�������߂�
	Vector3 vec = { _end.x - _start.x,
					_end.y - _start.y,
					_end.z - _start.z };

	// �x�N�g���̒��������߂�
	double dis = pow((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z), 0.5);

	if (dis == 0.0f)
	{
		vec = Vector3::zero;
	}
	else
	{
		// �P�ʃx�N�g�������߂�
		vec = { vec.x / (float)dis,vec.y / (float)dis, vec.z / (float)dis };
	}
	return vec;

}

float DoTween::GetVector(float _start, float _end)
{
	float vec = 0;

	// �ڕW���W�����݂̍��W��萳�̕����ɂ���Ȃ�
	if (_end - _start > 0)
	{
		vec = 1;
	}
	// ���Ȃ�
	else if (_end - _start < 0)
	{
		vec = -1;
	}
	// ����0(�ړ����Ȃ��Ȃ�)
	else
	{
		vec = 0;
	}

	return vec;
}

float DoTween::GetSpeed(Vector3 _start, Vector3 _end, float _time)
{
	// �x�N�g�������߂�
	Vector3 vec = { _end.x - _start.x,
					_end.y - _start.y,
					_end.z - _start.z };
	// �x�N�g���̒��������߂�
	double dis = pow((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z), 0.5);

	float spd = dis / (_time * 60);

	/*spd *= Time::slowTime;*/

	return spd;
}

void DoTween::flowLoopSet(std::list<VALUE>* _resetList)
{
	// �S�đҋ@��Ԃɖ߂�
	for (auto i = _resetList->begin(); i != _resetList->end(); i++)
	{
		(*i).state = STATE::WAIT;
	}

	// ���[�v�Đ�����flow�̍ŏ��̃C�e���[�^���擾
	auto itr = _resetList->begin();

	// �Đ����鏈���iDo,Join�j�͕����x�N�g���Ƃ������߂�
	while (true)
	{
		GetValue(&*itr);

		itr++;

		// ���Ă���v�f�����X�g�͈͊O�@�������́@Join�@�Ȃ�@�I���
		if ( itr == _resetList->end() || (*itr).start != START::JOIN) break;
	}

}



DoTween::~DoTween()
{
	sequence.clear();
}

