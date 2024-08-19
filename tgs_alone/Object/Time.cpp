#include "Time.h"
#include "DxLib.h"
#include <tgmath.h>

Time::Time() :time(0),time_flg(false), time2(0),time3(0.0f),add_flg(false),add_time(0),add_cnt(0), transparency(0)
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
	//time = 0;
	time2 = 0;
	time3 = 0.0f;
	time_flg = true;
	add_flg = false;
	add_time = 0;
	add_cnt = 0;
	transparency = 0;
}

void Time::Update()
{
	//	フラグがtrueのときカウントダウン
	if (time_flg == true)
	{
		time2++;

		if (time2 == 60)
		{
			time--;
			time2 = 0;
		}

		time3 += 0.27f;
	}

	if (add_flg == true)
	{
		add_flg = false;
	}
	else
	{
		if (transparency != 0)
		{
			transparency = 0;
		}
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

	// 減る時間の描画
	if (time > 5)
	{
		if (time3 <= 0.0f)
		{
			DrawBoxAA(340.0f, 260.0f, 990.0f, 275.0f, 0xffe699, TRUE);
		}
		else
		{
			DrawBoxAA(340.0f, 260.0f, 990.0f - time3, 275.0f, 0xffe699, TRUE);
		}
		
	}
	else if(time > 0)
	{
		DrawBoxAA(340.0f, 260.0f, 990.0f - time3, 275.0f, 0xff0000, TRUE);
	}

	// 足す時間の描画
	if (add_flg == true)
	{
		SetFontSize(30);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawFormatString(700, 215, 0xff0000, "+%d", add_time);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (time3 <= 0.0f)
		{
			DrawBoxAA(970.0f, 260.0f, 990.0f, 275.0f, 0x7fbfff, TRUE);
		}
		else
		{
			DrawBoxAA(990.0f - time3, 260.0f, (990.0f - time3) - (16.2f * (float)add_time), 275.0f, 0x7fbfff, TRUE);
		}
	}

	// 時間枠の描画
	DrawBox(340, 260, 990, 275, 0x000000, FALSE);
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

void Time::SetAddTime(bool flg, int num)
{
	add_flg = flg;
	add_time = num;
	time += num;
	time3 -= 16.2f * num;
}

void Time::FadeInOut(bool flg)
{
	if (flg == false)
	{
		if (transparency <= 230)
		{
			transparency += 25;
		}
		else
		{
			transparency = 255;
		}
	}
	else
	{
		if (transparency >= 13)
		{
			transparency -= 13;
		}
		else
		{
			transparency = 0;
		}
	}
}