#include "Time.h"
#include "DxLib.h"
#include <tgmath.h>

Time::Time() :time(0.0f),time_flg(false)
{
	for (int i = 0; i < 10; i++)
	{
		img_b[i] = 0;
		img_r[i] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		time2[i] = 0.0f;
	}
}

Time::~Time()
{
}

void Time::Initialize()
{
	// 画像データの読み込み
	LoadDivGraph("Resource/images/numberb.png", 10, 5, 2, 75, 75, img_b);
	LoadDivGraph("Resource/images/numberr.png", 10, 5, 2, 75, 75, img_r);

	for (int i = 0; i < 10; i++)
	{
		if (img_b[i] == -1)
		{
			throw("Resource/images/numberb.pngがありません\n");
		}
		if (img_r[i] == -1)
		{
			throw("Resource/images/numberr.pngがありません\n");
		}
	}

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

		time2[0] = time / 10;
		time2[1] = time / 1.0f;
		time2[2] = time / 0.1f;
		time2[3] = time / 0.01f;
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

			for (int i = 0; i < 4; i++)
			{
				DrawGraph(565, 110, img_r[i], TRUE);
			}
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

	//DrawGraph(0, 0, img_r[4], TRUE);
}

void Time::Finalize()
{
}