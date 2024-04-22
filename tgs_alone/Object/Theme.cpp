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
	// お題表示
	for (int i = 0; i < theme_num; i++)
	{
		DrawGraph((500 - 60 * (theme_num - 3)) + i * 110, 250, img[theme[i]], TRUE);
	}
}

void Theme::Finalize()
{
}