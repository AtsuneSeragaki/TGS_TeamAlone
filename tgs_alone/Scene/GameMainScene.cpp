#include "GameMainScene.h"
#include "DxLib.h"

GameMainScene::GameMainScene() :back_img(0), bgm(0), se(0), player_input{ -1 }, correct_num(0),player(nullptr), time(nullptr), theme(nullptr)
{
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete time;
	delete theme;
}

void GameMainScene::Initialize()
{
	// オブジェクトの生成
	player = new Player;
	time = new Time;
	theme = new Theme;

	// オブジェクトの初期化
	player->Initialize();
	time->Initialize();
	theme->Initialize();
}

eSceneType GameMainScene::Update()
{
	theme->Update();
	time->Update();
	player->Update();

	if (player->GetPlayerInput()== true)
	{
		Comparison();
	}

	if (correct_num == theme->GetThemeNum() && theme->GetThemeNum() <= THEME_MAX && time->GetTime() > 0.0f)
	{
		//time->SetTimeFlg(false);
		for (int i = 0; i < INPUT_MAX; i++)
		{
			player->ResetPlayerInput(i);
		}
		correct_num = 0;
		theme->SetThemeNum();
		theme->SetThemeFlg(true);
	}

	//if (time->GetTime() <= 0.0f)
	//{
	//	return eSceneType::E_RESULT;
	//}

	//if (theme->GetThemeNum() > THEME_MAX)
	//{
	//	return eSceneType::E_RESULT;
	//}

	/*if (theme->GetThemeFlg() == false)
	{
		time->SetTimeFlg(true);
	}*/

	return GetNowScene();
}

void GameMainScene::Draw() const
{
#ifdef _DEBUG
	SetFontSize(20);
	DrawString(0, 0, "GameMain", 0xffffff);

	if (time->GetTime() <= 0.0f)
	{
		DrawString(0,200,"Time Up",0xffffff);
	}

	if (theme->GetThemeNum() > THEME_MAX)
	{
		DrawString(0, 200, "MAX", 0xffffff);
	}

#endif // _DEBUG

	time->Draw();

	theme->Draw();

	player->Draw();
}

void GameMainScene::Finalize()
{
}

eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

void GameMainScene::Comparison()
{
	int tm[THEME_MAX];
	int ip[INPUT_MAX];
	int num;

	num = theme->GetThemeNum();
	tm[correct_num] = theme->GetTheme(correct_num);
	ip[correct_num] = player->GetPlayerInputData(correct_num);

	if (tm[correct_num] == ip[correct_num])
	{
		player_input[correct_num] = tm[correct_num];
		correct_num++;
		player->SetPlayerInput();
	}
	else
	{
		player->ResetPlayerInput(correct_num);
		player->SetPlayerInput();
	}
	
}

void GameMainScene::TimeupAnim()
{
}