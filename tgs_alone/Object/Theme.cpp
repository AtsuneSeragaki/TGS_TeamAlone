#include "Theme.h"
#include "DxLib.h"

int Theme::theme_num = 0;

Theme::Theme() : img{0},theme{-1},theme_flg(false),sound(0)
{
	for (int i = 0; i < 10; i++)
	{
		level_img[i] = 0;
	}
}

Theme::~Theme()
{
	// 音データの削除
	DeleteSoundMem(sound);

	// 画像データの削除
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(img[i]);
	}
}

void Theme::Initialize()
{
	// 画像の読み込み
	img[0] = LoadGraph("Resource/images/Abotton.png");
	img[1] = LoadGraph("Resource/images/Bbotton.png");
	img[2] = LoadGraph("Resource/images/Ybotton.png");
	img[3] = LoadGraph("Resource/images/Xbotton.png");
	LoadDivGraph("Resource/images/level.png", 10, 5, 2, 50, 50, level_img);

	// サウンド読み込み
	sound = LoadSoundMem("Resource/sounds/theme.mp3");

	// エラーチェック
	for (int i = 0; i < 4; i++)
	{
		if (img[i] == -1)
		{
			throw("img[%d]がありません\n", i);
		}
	}

	if (sound == -1)
	{
		throw("Resource/sounds/Theme.mp3がありません\n");
	}

	// 変数の初期化
	theme_flg = true;
	theme_num = 3;
}

void Theme::Update()
{
	// お題をランダムに生成
	if (theme_flg == true)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);

		for (int i = 0; i < theme_num; i++)
		{
			theme[i] = GetRand(3);
		}

		theme_flg = false;
	}
}

void Theme::Draw()
{
	if (theme_num < 10)
	{
		/*SetFontSize(50);
		DrawFormatString(295, 250, 0x000000, "%d", theme_num - 2);*/
		//DrawGraph(280, 245, level_img[0], TRUE);
		DrawGraph(300, 245, level_img[(theme_num - 2) % 10], TRUE);
	}
	else
	{
		/*SetFontSize(50);
		DrawFormatString(285, 250, 0x000000, "%d", theme_num - 2);*/
		DrawGraph(277, 245, level_img[(theme_num - 2) / 10], TRUE);
		DrawGraph(314, 245, level_img[(theme_num - 2) % 10], TRUE);
	}
	

	if (theme_num < 10)
	{
		// お題表示
		for (int i = 0; i < theme_num; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
			DrawGraph((500 - 57 * (theme_num - 3)) + i * 110, 410, img[theme[i]], TRUE);
			//DrawGraph((540 - 50 * (theme_num - 3)) + i * 90, 500, img[theme[i] + 4], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else if (theme_num == 10)
	{
		// お題表示
		for (int i = 0; i < theme_num; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
			DrawGraph(90 + i * 110, 410, img[theme[i]], TRUE);
			//DrawGraph((540 - 50 * (theme_num - 3)) + i * 90, 500, img[theme[i] + 4], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else if(theme_num >= 11 && theme_num < 16)
	{
		// お題表示
		for (int i = 0; i < theme_num; i++)
		{
			if (i < 8)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(225 + i * 110, 355, img[theme[i]], TRUE);
				//DrawGraph(300 + i * 90, 490, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph((100 - 54 * (theme_num - 2)) + i * 110, 500, img[theme[i]], TRUE);
				//DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	else if(theme_num == 16)
	{
		for (int i = 0; i < theme_num; i++)
		{
			if (i < 8)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(225 + i * 110, 355, img[theme[i]], TRUE);
				//DrawGraph(300 + i * 90, 490, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(225 + (i - 8) * 110, 500, img[theme[i]], TRUE);
				//DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	else if (theme_num == 17)
	{
		for (int i = 0; i < theme_num; i++)
		{
			if (i < 9)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(160 + i * 110, 355, img[theme[i]], TRUE);
				//DrawGraph(300 + i * 90, 490, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(215 + (i - 9) * 110, 500, img[theme[i]], TRUE);
				//DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	else if (theme_num == 18)
	{
		for (int i = 0; i < theme_num; i++)
		{
			if (i < 9)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(160 + i * 110, 355, img[theme[i]], TRUE);
				//DrawGraph(300 + i * 90, 490, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(160 + (i - 9) * 110, 500, img[theme[i]], TRUE);
				//DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	else if (theme_num == 19)
	{
		for (int i = 0; i < theme_num; i++)
		{
			if (i < 10)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(90 + i * 110, 355, img[theme[i]], TRUE);
				//DrawGraph(300 + i * 90, 490, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(160 + (i - 10) * 110, 500, img[theme[i]], TRUE);
				//DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	else
	{
		for (int i = 0; i < theme_num; i++)
		{
			if (i < 10)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(90 + i * 110, 355, img[theme[i]], TRUE);
				//DrawGraph(300 + i * 90, 490, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
				DrawGraph(90 + (i - 10) * 110, 500, img[theme[i]], TRUE);
				//DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[theme[i] + 4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void Theme::Finalize()
{
}