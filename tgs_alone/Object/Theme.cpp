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
	img[4] = LoadGraph("Resource/images/Abotton2.png");
	img[5] = LoadGraph("Resource/images/Bbotton2.png");
	img[6] = LoadGraph("Resource/images/Ybotton2.png");
	img[7] = LoadGraph("Resource/images/Xbotton2.png");

	// エラーチェック
	if (img[0] == -1)
	{
		throw("Resource/images/Abotton.pngがありません\n");
	}
	if (img[1] == -1)
	{
		throw("Resource/images/Bbotton.pngがありません\n");
	}
	if (img[2] == -1)
	{
		throw("Resource/images/Ybotton.pngがありません\n");
	}
	if (img[3] == -1)
	{
		throw("Resource/images/Xbotton.pngがありません\n");
	}
	if (img[4] == -1)
	{
		throw("Resource/images/Abotton2.pngがありません\n");
	}
	if (img[5] == -1)
	{
		throw("Resource/images/Bbotton2.pngがありません\n");
	}
	if (img[6] == -1)
	{
		throw("Resource/images/Ybotton2.pngがありません\n");
	}
	if (img[7] == -1)
	{
		throw("Resource/images/Xbotton2.pngがありません\n");
	}

	theme_flg = true;

	theme_num = 3;
}

void Theme::Update()
{
	// お題をランダムに生成
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
	if (theme_num <= 10)
	{
		// お題表示
		for (int i = 0; i < theme_num; i++)
		{
			DrawGraph((500 - 57 * (theme_num - 3)) + i * 110, 250, img[theme[i]], TRUE);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
			DrawGraph((540 - 50 * (theme_num - 3)) + i * 90, 500, img[theme[i] + 4], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else if(theme_num >= 11)
	{
		// お題表示
		for (int i = 0; i < theme_num; i++)
		{
			if (i < 8)
			{
				DrawGraph(225 + i * 110, 160, img[theme[i]], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(300 + i * 90, 490, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				DrawGraph((100 - 54 * (theme_num - 2)) + i * 110, 300, img[theme[i]], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void Theme::Finalize()
{
}