#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

int TitleScene::menu_cursor = 0;

TitleScene::TitleScene() : back_img(0),bgm(0),star_img(0),star_cnt(0),star_blend(0)
{
	se[0] = 0;
	se[1] = 0;

	for (int i = 0; i < 8; i++)
	{
		menu_img[i] = 0;
	}
}

TitleScene::~TitleScene()
{
	// 画像データの削除
	DeleteGraph(back_img);

	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(menu_img[i]);
	}
}

void TitleScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/title/title.png");
	menu_img[0] = LoadGraph("Resource/images/title/starty.png");
	menu_img[1] = LoadGraph("Resource/images/title/start.png");
	menu_img[2] = LoadGraph("Resource/images/title/helpy.png");
	menu_img[3] = LoadGraph("Resource/images/title/help.png");
	menu_img[4] = LoadGraph("Resource/images/title/rankingy.png");
	menu_img[5] = LoadGraph("Resource/images/title/ranking.png");
	menu_img[6] = LoadGraph("Resource/images/title/endy.png");
	menu_img[7] = LoadGraph("Resource/images/title/end.png");

	star_img = LoadGraph("Resource/images/help/star.png");

	se[0] = LoadSoundMem("Resource/sounds/title/move.mp3");
	se[1] = LoadSoundMem("Resource/sounds/title/ok.mp3");

	bgm = LoadSoundMem("Resource/sounds/title/bgm3.mp3");

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);


	if (back_img == -1)
	{
		throw("Resource/images/title.pngがありません");
	}

	for (int i = 0; i < 4; i++)
	{
		if (menu_img[i] == -1)
		{
			throw("menu_img[%d]がありません",i);
		}
	}

	star_cnt = 0;
	star_blend = 255;
}

eSceneType TitleScene::Update()
{
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	star_cnt++;

	if (star_cnt <= 51)
	{
		star_blend = 255 - star_cnt * 5;
	}
	else if(star_cnt <= 101)
	{
		star_blend = 255 - (star_cnt - 51) * 5;
	}
	else if (star_cnt <= 152)
	{
		star_blend = (star_cnt - 152) * 5;
	}
	else
	{
		star_blend = (star_cnt - 152) * 5;
	}

	if (star_cnt > 202)
	{
		star_cnt = 0;
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		menu_cursor++;

		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		menu_cursor--;

		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);
		StopSoundMem(bgm);

		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_HELP;
		case 2:
			return eSceneType::E_RANKING;
		case 3:
			return eSceneType::E_END;
		default:
			break;
		}
	}

	return GetNowScene();
}

void TitleScene::Draw() const
{
	// 背景表示
	DrawGraph(0, 0, back_img, TRUE);

	

	
	if (star_cnt <= 101)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, star_blend);
		DrawGraph(80, 220, star_img, TRUE);
		DrawGraph(430, 220, star_img, TRUE);
		DrawGraph(800, 220, star_img, TRUE);
		DrawGraph(1200, 220, star_img, TRUE);
		DrawGraph(250, 380, star_img, TRUE);
		DrawGraph(950, 380, star_img, TRUE);
		DrawGraph(430, 600, star_img, TRUE);
		DrawGraph(800, 600, star_img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, star_blend);
		DrawGraph(250, 220, star_img, TRUE);
		DrawGraph(950, 220, star_img, TRUE);
		DrawGraph(80, 350, star_img, TRUE);
		DrawGraph(430, 350, star_img, TRUE);
		DrawGraph(800, 350, star_img, TRUE);
		DrawGraph(1200, 350, star_img, TRUE);
		DrawGraph(300, 600, star_img, TRUE);
		DrawGraph(900, 600, star_img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
	

	switch (menu_cursor)
	{
	case 0:
		DrawGraph(555, 240, menu_img[0], TRUE);
		DrawGraph(575, 340, menu_img[3], TRUE);
		DrawGraph(510, 443, menu_img[5], TRUE);
		DrawGraph(585, 540, menu_img[7], TRUE);
		break;
	case 1:
		DrawGraph(555, 240, menu_img[1], TRUE);
		DrawGraph(575, 340, menu_img[2], TRUE);
		DrawGraph(510, 443, menu_img[5], TRUE);
		DrawGraph(585, 540, menu_img[7], TRUE);
		break;
	case 2:
		DrawGraph(555, 240, menu_img[1], TRUE);
		DrawGraph(575, 340, menu_img[3], TRUE);
		DrawGraph(510, 443, menu_img[4], TRUE);
		DrawGraph(585, 540, menu_img[7], TRUE);
		break;
	case 3:
		DrawGraph(555, 240, menu_img[1], TRUE);
		DrawGraph(575, 340, menu_img[3], TRUE);
		DrawGraph(510, 443, menu_img[5], TRUE);
		DrawGraph(585, 540, menu_img[6], TRUE);
		break;
	default:
		break;
	}

	DrawFormatString(0, 0, 0x000000, "%d", star_blend);
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}