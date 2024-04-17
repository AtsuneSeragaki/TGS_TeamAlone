#include "Theme.h"
#include "DxLib.h"

Theme::Theme() : img{0},theme{-1},theme_flg(false),theme_num(0)
{
}

Theme::~Theme()
{
}

void Theme::Initialize()
{
	// 画像の読み込み
	img[0] = LoadGraph("Resource/images/Abotton.png");
	img[1] = LoadGraph("Resource/images/Bbotton.png");
	img[2] = LoadGraph("Resource/images/Ybotton.png");
	img[3] = LoadGraph("Resource/images/Xbotton.png");
	theme_flg = true;

	theme_num = 3;
}

void Theme::Update()
{
	if (theme_flg == true)
	{
		for (int i = 0; i < theme_num; i++)
		{
			theme[i] = GetRand(3);
		}

		theme_flg = false;
	}
}

void Theme::Draw()
{
	//if (theme_num >= 6)
	//{
	//	// お題表示
	//	for (int i = 0; i < 4; i++)
	//	{
	//		DrawGraph(390 + i * 150, 180, theme_img[theme[i]], TRUE);
	//		/*SetFontSize(40);
	//		DrawFormatString((650 - 30 * theme_num) + i * 60, 300, 0xffffff, "%d", theme[i]);*/
	//	}

	//	// お題表示
	//	for (int i = 4; i < theme_num; i++)
	//	{
	//		DrawGraph(550 + (i - 4) * 150, 300, theme_img[theme[i]], TRUE);
	//		/*SetFontSize(40);
	//		DrawFormatString((650 - 30 * theme_num) + i * 60, 300, 0xffffff, "%d", theme[i]);*/
	//	}
	//}
	//else
	//{
	//	// お題表示
		for (int i = 0; i < theme_num; i++)
		{
			DrawGraph((500 - 60 * (theme_num - 3)) + i * 110, 250, img[theme[i]], TRUE);
			/*SetFontSize(40);
			DrawFormatString((650 - 30 * theme_num) + i * 60, 300, 0xffffff, "%d", theme[i]);*/
		}
	//}
}

void Theme::Finalize()
{
}