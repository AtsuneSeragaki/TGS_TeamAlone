#include "Time.h"
#include "DxLib.h"

Time::Time() :time(0.0f),time_flg(false)
{
}

Time::~Time()
{
}

void Time::Initialize()
{
	// 制限時間の初期化
	time = 60.0f;
	time_flg = true;
}

void Time::Update()
{
	if (time_flg == true)
	{
		// 1フレーム0.016ずつマイナス
		if (time > 0)
		{
			time -= 0.016f;
		}
		else
		{
			time = 0.0f;
		}
	}
}

void Time::Draw()
{
	// 制限時間表示
	SetFontSize(50);
	DrawFormatString(600, 10, 0xffffff, "%.2f", time);
}

void Time::Finalize()
{
}

void Time::SetTimeFlg(bool flg)
{
	time_flg = flg;
}