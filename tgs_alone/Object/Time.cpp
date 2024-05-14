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
	time = 45.0f;
	time_flg = true;
}

void Time::Update()
{
	//	フラグがtrueのときカウントダウン
	if (time_flg == true)
	{
		if (time >= 0.016f)
		{
			// 1フレーム0.016ずつマイナス
			time -= 0.016f;
		}
		else
		{
			time = 0.000f;
		}
	}
}

void Time::Draw()
{
	/*SetFontSize(20);

	DrawString(620, 0, "Time", 0x000000);*/

	// 制限時間表示
	SetFontSize(70);

	if (time < 11.0f)
	{// 制限時間が10秒以下になったら赤い文字
		if (time >= 10.0f)
		{
			DrawFormatString(565, 110, 0xed1a3d, "%.2f", time);
		}
		else
		{
			DrawFormatString(590, 110, 0xed1a3d, "%.2f", time);
		}
	}
	else
	{
		DrawFormatString(565, 110, 0x000000, "%.2f", time);
	}
}

void Time::Finalize()
{
}