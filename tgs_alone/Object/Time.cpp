﻿#include "Time.h"
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
	time = 50.0f;
	time_flg = true;
}

void Time::Update()
{
	if (time_flg == true)
	{
		// 1フレーム0.016ずつマイナス
		if (time > 0.016f)
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

	if (time < 11.0f)
	{
		DrawFormatString(600, 10, 0xed1a3d, "%.2f", time);
	}
	else
	{
		DrawFormatString(600, 10, 0x000000, "%.2f", time);
	}
}

void Time::Finalize()
{
}

void Time::SetTimeFlg(bool flg)
{
	time_flg = flg;
}