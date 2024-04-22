#include "GameMainScene.h"
#include "DxLib.h"

GameMainScene::GameMainScene() :back_img(0), bgm(0), se(0),  correct_num(0), player(nullptr), time(nullptr), theme(nullptr), begin_time(0),begin_cnt(0),draw_cnt(0),timeup_flg(false),timeup_cnt(0),ui_img(0)
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
	ui_img = LoadGraph("Resource/images/UI_botton.png");
	begin_time = 3;
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
	// 開始のカウントダウン
	if (begin_time != -1)
	{
		begin_cnt++;

		if (begin_cnt % 60 == 0)
		{
			begin_time--;
		}
	}
	
	// カウントダウン後に開始
	if (begin_time == -1)
	{
		theme->Update();
		player->SetPlayerTheme(theme->GetThemeNum());
		time->Update();
		player->Update();

		// プレイヤーの入力とお題の比較
		if (player->GetPlayerInput() == true && correct_num < THEME_MAX && player->GetInputDraw(correct_num) == 0)
		{
			Comparison();
		}

		// プレイヤーがお題を全てクリアしたら次のお題へ
		if (correct_num == theme->GetThemeNum() && theme->GetThemeNum() < THEME_MAX && time->GetTime() > 0.0f && player->GetInputDraw(correct_num - 1) == 0)
		{
			if (draw_cnt == 15)
			{
				for (int i = 0; i < INPUT_MAX; i++)
				{
					player->ResetPlayerInput(i);
					player->ResetInputDraw(i);
				}
				correct_num = 0;
				theme->SetThemeNum();
				player->SetPlayerTheme(theme->GetThemeNum());
				draw_cnt = 0;
				theme->SetThemeFlg(true);
			}
			else
			{	
				draw_cnt++;
			}
			
		}

		//制限時間が0になったら終了のアニメーション
		if (time->GetTime() <= 0.0f)
		{
			TimeupAnim();
		}

		// 全てクリアしたら時間を止める
		if (correct_num == THEME_MAX)
		{
			time->SetTimeFlg(false);
			draw_cnt++;
			if (draw_cnt > 60)
			{
				TimeupAnim();
			}
		}

		// アニメーションの後、リザルト画面へ
		if (timeup_flg == true)
		{
			if (draw_cnt != 0)
			{
				draw_cnt = 0;
			}
			return eSceneType::E_RESULT;
		}
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
#ifdef _DEBUG
	SetFontSize(20);
	DrawString(0, 0, "GameMain", 0xffffff);

	if (theme->GetThemeNum() > THEME_MAX)
	{
		DrawString(0, 200, "MAX", 0xffffff);
	}

	DrawBox(0, 0, 1280, 720, 0x7d7d7d, TRUE);

#endif // _DEBUG


	DrawBox(0, 0, 1280, 720, 0xf5f5f5, TRUE);

	

	if (timeup_cnt != 0)
	{
		if (correct_num == THEME_MAX)
		{
			SetFontSize(100);
			DrawString(470, 200, "PERFECT!", 0x000000);
		}
		else
		{
			SetFontSize(100);
			DrawString(470, 200, "TIME UP!", 0x000000);
		}
	}
	else
	{
		if (begin_time == -1)
		{
			DrawGraph(1050, 490, ui_img, TRUE);

			time->Draw();

			theme->Draw();

			player->Draw();
		}
		else if (begin_time == 0)
		{
			SetFontSize(60);
			DrawString(550, 200, "START", 0x000000);
		}
		else
		{
			SetFontSize(60);
			DrawFormatString(600, 200, 0x000000, "%d", begin_time);
	
		}
	}
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

	tm[correct_num] = theme->GetTheme(correct_num);
	ip[correct_num] = player->GetPlayerInputData(correct_num);

	if (tm[correct_num] == ip[correct_num])
	{
		correct_num++;
		player->SetPlayerInput();
	}
	else
	{
		player->SetPlayerMis(correct_num);
		time->SetTime();
		player->ResetPlayerInput(correct_num);
		player->ResetInputDraw(correct_num);
	}
	
}

void GameMainScene::TimeupAnim()
{
	timeup_cnt++;

	if (timeup_cnt == 110)
	{
		timeup_flg = true;
	}
}