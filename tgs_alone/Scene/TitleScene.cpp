#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene() : back_img(0)
{
	for (int i = 0; i < 4; i++)
	{
		menu_img[i] = 0;
	}
}

TitleScene::~TitleScene()
{
	// 画像データの削除
	DeleteGraph(back_img);

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(menu_img[i]);
	}
}

void TitleScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/title.png");
	menu_img[0] = LoadGraph("Resource/images/menu1.png");
	menu_img[1] = LoadGraph("Resource/images/menu2.png");
	menu_img[2] = LoadGraph("Resource/images/menu3.png");
	menu_img[3] = LoadGraph("Resource/images/menu4.png");

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
	return GetNowScene();
}

void TitleScene::Draw() const
{
	// 背景表示
	DrawGraph(0, 0, back_img, TRUE);

	DrawGraph(550, 250, menu_img[0], TRUE);
	DrawGraph(550, 350, menu_img[1], TRUE);
	DrawGraph(550, 453, menu_img[2], TRUE);
	DrawGraph(550, 550, menu_img[3], TRUE);
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}