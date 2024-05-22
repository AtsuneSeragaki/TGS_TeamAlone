#include "ResultScene.h"
#include "GameMainScene.h"
#include "../Object/Theme.h"
#include "DxLib.h"

ResultScene::ResultScene():back_img(0)
{
	for (int i = 0; i < 10; i++)
	{
		num_img[i] = 0;
	}
}

ResultScene::~ResultScene()
{
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(num_img[i]);
	}
}

void ResultScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/result.png");
	LoadDivGraph("Resource/images/result_num.png", 10, 5, 2, 75, 75, num_img);

	// エラーチェック
	if (back_img == -1)
	{
		throw("Resource/images/result.pngがありません");
	}

	for (int i = 0; i < 10; i++)
	{
		if (num_img[i] == -1)
		{
			throw("num_img[%d]がありません",i);
		}
	}
}

eSceneType ResultScene::Update()
{
	return GetNowScene();
}

void ResultScene::Draw() const
{
#ifdef _DEBUG
	SetFontSize(20);
	DrawString(0, 0, "Result", 0xffffff);

#endif // _DEBUG
	DrawGraph(0, 0, back_img, TRUE);

	int i = Theme::theme_num;
	int j = GameMainScene::combo;

	if (i < 10)
	{
		DrawGraph(428, NUM_Y, num_img[0], TRUE);
		DrawGraph(490, NUM_Y, num_img[i % 10], TRUE);
	}
	else
	{
		DrawGraph(428, NUM_Y, num_img[i / 10], TRUE);
		DrawGraph(490, NUM_Y, num_img[i % 10], TRUE);
	}

	if (i < 10)
	{
		DrawGraph(898, NUM_Y, num_img[0], TRUE);
		DrawGraph(960, NUM_Y, num_img[j % 10], TRUE);
	}
	else
	{
		DrawGraph(898, NUM_Y, num_img[j / 10], TRUE);
		DrawGraph(960, NUM_Y, num_img[j % 10], TRUE);
	}
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}