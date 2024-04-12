#include "Theme.h"
#include "DxLib.h"

Theme::Theme() : theme_img{0},theme{-1},theme_flg(false),theme_num(0)
{
}

Theme::~Theme()
{
}

void Theme::Initialize()
{
	// 画像の読み込み
	/*theme_img[0] = LoadGraph("Resource/images/");
	theme_img[1] = LoadGraph("Resource/images/");
	theme_img[2] = LoadGraph("Resource/images/");
	theme_img[3] = LoadGraph("Resource/images/");*/

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
	// お題表示
	for (int i = 0; i < theme_num; i++)
	{
		//DrawGraph(100 + i * 20, 300, theme_img[theme[i]], TRUE);
		SetFontSize(40);
		DrawFormatString((650 - 30 * theme_num) + i * 100, 300, 0xffffff, "%d", theme[i]);
	}
}

void Theme::Finalize()
{
}