#include "Time.h"
#include "DxLib.h"

Time::Time() :time(0.0f),time_cnt(0)
{
}

Time::~Time()
{
}

void Time::Initialize()
{
	// �������Ԃ̏�����
	time = 60.0f;
}

void Time::Update()
{
	// ��������
	time_cnt++;

	if (time_cnt > 60)
	{
		if (time > 0)
		{
			time -= 1.0f;
		}
		else
		{
			time = 0.0f;
		}

		time_cnt = 0;
	}
}

void Time::Draw()
{
	// �������ԕ\��
	DrawFormatString(600, 10, 0xffffff, "%f", time);
}

void Time::Finalize()
{
}