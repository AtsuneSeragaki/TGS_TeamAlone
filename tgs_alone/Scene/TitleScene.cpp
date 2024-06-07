#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

int TitleScene::menu_cursor = 0;

TitleScene::TitleScene() : back_img(0)
{
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
}

eSceneType TitleScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		menu_cursor++;

		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{
		menu_cursor--;

		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
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
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}