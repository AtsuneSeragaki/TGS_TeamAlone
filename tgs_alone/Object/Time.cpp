﻿#include "Time.h"
#include "DxLib.h"
#include <tgmath.h>

Time::Time() :time(0),time_flg(false), time2(0),time3(0.0f)
{
	for (int i = 0; i < 10; i++)
	{
		img_b[i] = 0;
		img_r[i] = 0;
	}
}

Time::~Time()
{
	
}

void Time::Initialize()
{
	// 画像データの読み込み
	LoadDivGraph("Resource/images/main/number/numberb.png", 10, 5, 2, 75, 75, img_b);
	img_b[10] = LoadGraph("Resource/images/main/number/period.png");
	LoadDivGraph("Resource/images/main/number/numberr.png", 10, 5, 2, 75, 75, img_r);
	img_r[10] = LoadGraph("Resource/images/main/number/periodr.png");

	// エラーチェック
	for (int i = 0; i < 11; i++)
	{
		if (img_b[i] == -1)
		{
			throw("img_b[%d]がありません\n",i);
		}
		if (img_r[i] == -1)
		{
			throw("img_r[%d]がありません\n", i);
		}
	}

	// 制限時間の初期化
	time = 40;
	time2 = 0;
	time3 = 0.0f;
	//time2 = 99;
	time_flg = true;
}

void Time::Update()
{
	//	フラグがtrueのときカウントダウン
	if (time_flg == true)
	{
		/*if (time2 > 0)
		{
			 1フレームミリ秒を1ずつマイナス
			if (time2 % 3 == 0)
			{
				time2 -= 2;
			}
			else
			{
				time2--;
			}
		}
		else
		{
			time--;
			if (time == 0)
			{
				time2 = 0;
			}
			else
			{
				time2 = 99;
			}
		}*/

		time2++;

		if (time2 == 60)
		{
			time--;
			time2 = 0;
		}

		time3 += 0.27f;
	}
}

void Time::Draw()
{
	// 制限時間表示
	//if (time < 11)
	//{// 制限時間が10秒以下になったら赤い文字

	//	// ピリオド表示
	//	DrawGraph(TIME_X + 78, TIME_Y, img_r[10], TRUE);

	//	if (time < 10)
	//	{
	//		// 時間(秒)表示
	//		DrawGraph(TIME_X, TIME_Y, img_r[0], TRUE);
	//		DrawGraph(TIME_X + 50, TIME_Y, img_r[time % 10], TRUE);

	//		// 時間(ミリ秒)表示
	//		if (time2 < 10)
	//		{
	//			DrawGraph(TIME_X + 120, TIME_Y, img_r[0], TRUE);
	//			DrawGraph(TIME_X + 170, TIME_Y, img_r[time2 % 10], TRUE);
	//		}
	//		else
	//		{
	//			//DrawFormatString(650, 110, 0x000000, "%d", time2);
	//			DrawGraph(TIME_X + 120, TIME_Y, img_r[time2 / 10], TRUE);
	//			DrawGraph(TIME_X + 170, TIME_Y, img_r[time2 % 10], TRUE);
	//		}
	//	}
	//	else
	//	{
	//		// 時間(秒)表示
	//		DrawGraph(TIME_X, TIME_Y, img_r[time / 10], TRUE);
	//		DrawGraph(TIME_X + 50, TIME_Y, img_r[time % 10], TRUE);

	//		// 時間(ミリ秒)表示
	//		if (time2 < 10)
	//		{
	//			DrawGraph(TIME_X + 120, TIME_Y, img_r[0], TRUE);
	//			DrawGraph(TIME_X + 170, TIME_Y, img_r[time2 % 10], TRUE);
	//		}
	//		else
	//		{
	//			DrawGraph(TIME_X + 120, TIME_Y, img_r[time2 / 10], TRUE);
	//			DrawGraph(TIME_X + 170, TIME_Y, img_r[time2 % 10], TRUE);
	//		}
	//	}
	//}
	//else
	//{
	//	// 時間(秒)表示
	//	DrawGraph(TIME_X, TIME_Y, img_b[time / 10], TRUE);
	//	DrawGraph(TIME_X + 50, TIME_Y, img_b[time % 10], TRUE);

	//	// ピリオド表示
	//	DrawGraph(TIME_X + 78,TIME_Y, img_b[10], TRUE);

	//	// 時間(ミリ秒)表示
	//	if (time2 < 10)
	//	{
	//		DrawGraph(TIME_X + 122, TIME_Y, img_b[0], TRUE);
	//		DrawGraph(TIME_X + 172, TIME_Y, img_b[time2 % 10], TRUE);
	//	}
	//	else
	//	{
	//		DrawGraph(TIME_X + 122, TIME_Y, img_b[time2 / 10], TRUE);
	//		DrawGraph(TIME_X + 172, TIME_Y, img_b[time2 % 10], TRUE);
	//	}
	//}

	if (time > 5)
	{
		DrawBoxAA(350.0f, 245.0f, 1000.0f - time3, 260.0f, 0xffd700, TRUE);
		DrawBox(350, 245, 1000, 260, 0x000000, FALSE);
	}
	else if(time > 0)
	{
		DrawBoxAA(350.0f, 245.0f, 1000.0f - time3, 260.0f, 0xff0000, TRUE);
		DrawBox(350, 245, 1000, 260, 0x000000, FALSE);
	}
	else
	{
		DrawBox(350, 245, 1000, 260, 0x000000, FALSE);
	}
	
}

void Time::Finalize()
{
	// 画像データの削除
	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(img_b[i]);
		DeleteGraph(img_r[i]);
	}
}