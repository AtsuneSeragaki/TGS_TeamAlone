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
	// 制限時間の初期化
	time = 60.0f;
}

void Time::Update()
{
	// 制限時間
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
	// 制限時間表示
	DrawFormatString(600, 10, 0xffffff, "%f", time);
}

void Time::Finalize()
{
}