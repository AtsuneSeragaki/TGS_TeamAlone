#include "GameMainScene.h"
#include "DxLib.h"

GameMainScene::GameMainScene() :back_img(0), theme_img{ 0 }, bgm(0), se(0), time(0.0f),time_cnt(0),theme{0}, theme_flg(true), theme_num(3)
{
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Initialize()
{
	time = 60.0f;
}

eSceneType GameMainScene::Update()
{
	// Ç®ëËÇÃê›íË
	if (theme_flg == true)
	{
		SetTheme();
	}
	else
	{
		// êßå¿éûä‘
		time_cnt++;

		if (time_cnt > 60)
		{
			if (time > 0)
			{
				time -= 1.0f;
			}
			else
			{
				time = 0.0f;
			}

			time_cnt = 0;
		}
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
#ifdef _DEBUG
	DrawString(0, 0, "GameMain", 0xffffff);

#endif // _DEBUG

	// êßå¿éûä‘ï\é¶
	DrawFormatString(600, 10, 0xffffff, "%f", time);

	// Ç®ëËï\é¶
	for (int i = 0; i < theme_num; i++)
	{
		//DrawGraph(100 + i * 20, 300, theme_img[theme[i]], TRUE);
		DrawFormatString(100 + i * 20, 300, 0xffffff, "%d", theme[i]);
	}
}

void GameMainScene::Finalize()
{
}

eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

void GameMainScene::SetTheme(void)
{
	for (int i = 0; i < theme_num; i++)
	{
		theme[i] = GetRand(3);
	}

	theme_flg = false;
}