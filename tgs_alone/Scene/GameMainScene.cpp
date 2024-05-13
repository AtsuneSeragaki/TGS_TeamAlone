#include "GameMainScene.h"
#include "DxLib.h"

GameMainScene::GameMainScene() :back_img(0), bgm(0), se(0),  correct_num(0), player(nullptr), time(nullptr), theme(nullptr), begin_time(0),begin_cnt(0),draw_cnt(0),timeup_flg(false),timeup_cnt(0),ui_img(0),combo(0)
{
	for (int i = 0; i < 5; i++)
	{
		sound[i] = 0;
		
	}

	for (int i = 0; i < 6; i++)
	{
		img[i] = 0;
	}
}

GameMainScene::~GameMainScene()
{
	// オブジェクトの削除
	delete player;
	delete time;
	delete theme;

	// 音データの削除
	DeleteSoundMem(sound[0]);

	// 画像データの削除
	DeleteGraph(ui_img);
}

void GameMainScene::Initialize()
{
	// 画像の読み込み
	ui_img = LoadGraph("Resource/images/UI_botton.png");
	img[3] = LoadGraph("Resource/images/count3.png");
	img[2] = LoadGraph("Resource/images/count2.png");
	img[1] = LoadGraph("Resource/images/count1.png");
	img[0] = LoadGraph("Resource/images/start.png");
	img[4] = LoadGraph("Resource/images/main.png");
	img[5] = LoadGraph("Resource/images/timeup.png");

	// サウンド読み込み
	sound[0] = LoadSoundMem("Resource/sounds/maou_bgm_cyber44.ogg");
	sound[1] = LoadSoundMem("Resource/sounds/countdown.mp3");
	sound[2] = LoadSoundMem("Resource/sounds/start.mp3");
	sound[3] = LoadSoundMem("Resource/sounds/game_end.mp3");
	sound[4] = LoadSoundMem("Resource/sounds/stop.mp3");

	// エラーチェック
	if (ui_img == -1)
	{
		throw("Resource/images/UI_botton.pngがありません\n");
	}
	if (img[0] == -1)
	{
		throw("Resource/images/start.pngがありません\n");
	}
	if (img[1] == -1)
	{
		throw("Resource/images/count1.pngがありません\n");
	}
	if (img[2] == -1)
	{
		throw("Resource/images/count2.pngがありません\n");
	}
	if (img[3] == -1)
	{
		throw("Resource/images/count3.pngがありません\n");
	}
	if (img[4] == -1)
	{
		throw("Resource/images/main.pngがありません\n");
	}
	if (img[5] == -1)
	{
		throw("Resource/images/timeup.pngがありません\n");
	}
	if (sound[0] == -1)
	{
		throw("Resource/sounds/maou_bgm_cyber44.oggがありません\n");
	}
	if (sound[1] == -1)
	{
		throw("Resource/sounds/countdown.mp3がありません\n");
	}
	if (sound[2] == -1)
	{
		throw("Resource/sounds/start.mp3がありません\n");
	}
	if (sound[3] == -1)
	{
		throw("Resource/sounds/game_end.mp3がありません\n");
	}
	if (sound[4] == -1)
	{
		throw("Resource/sounds/game_end_voice.mp3がありません\n");
	}

	// 開始のカウントダウン初期化
	begin_time = 3;

	// オブジェクトの生成
	player = new Player;
	time = new Time;
	theme = new Theme;

	// オブジェクトの初期化
	player->Initialize();
	time->Initialize();
	theme->Initialize();

	// BGMの音量設定
	ChangeVolumeSoundMem(100, sound[0]);

	combo = 0;
}

eSceneType GameMainScene::Update()
{
	// 開始のカウントダウン
	if (begin_time != -1)
	{
		if (begin_time == 3 && begin_cnt == 0)
		{
			PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
		}

		begin_cnt++;

		if (begin_cnt % 60 == 0)
		{
			begin_time--;

			if (begin_time > 0)
			{
				PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
			}
			else if(begin_time == 0)
			{
				PlaySoundMem(sound[2], DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}
	
	// カウントダウン後に開始
	if (begin_time == -1)
	{
		//制限時間が0になったら
		if (time->GetTime() <= 0.0f)
		{
			// BGMを止める
			StopSoundMem(sound[0]);

			// 終了の表示
			TimeupAnim();

			// 終了の表示後、リザルト画面へ
			if (timeup_flg == true)
			{
				if (draw_cnt != 0)
				{
					draw_cnt = 0;
				}

				//return eSceneType::E_RESULT;
			}
		}
		else
		{
			theme->Update();
			player->SetPlayerTheme(theme->GetThemeNum());
			time->Update();
			player->Update();
			PlaySoundMem(sound[0], DX_PLAYTYPE_LOOP, FALSE);

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

			//制限時間が0になったら
			//if (time->GetTime() <= 0.0f)
			//{
			//	// BGMを止める
			//	StopSoundMem(sound[0]);

			//	// 終了の表示
			//	TimeupAnim();
			//}

			// 全てクリアしたら時間を止める
			/*if (correct_num == THEME_MAX)
			{
				time->SetTimeFlg(false);
				draw_cnt++;
				if (draw_cnt > 60)
				{
					TimeupAnim();
				}
			}*/

			
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

	// 背景描画
	//DrawBox(0, 0, 1280, 720, 0xf5f5f5, TRUE);
	DrawGraph(0, 0, img[4], TRUE);
	
	if (begin_time == -1)
	{
		// ボタンの位置(UI)描画
		//DrawGraph(1100, 20, ui_img, TRUE);

		// コンボ数表示
		SetFontSize(50);
		DrawFormatString(250, 73,0x000000,"%d",combo);

		// 制限時間の描画
		time->Draw();

		// お題の描画
		theme->Draw();

		// プレイヤーの入力を描画
		player->Draw();
	}
	else if (begin_time == 0)
	{
		// ゲーム開始の描画
		//SetFontSize(60);
		//DrawString(550, 200, "START", 0x000000);

		DrawGraph(0, 0, img[0], TRUE);

	}
	else
	{
		// ゲーム開始までのカウントダウン描画
		//SetFontSize(60);
		//DrawFormatString(600, 200, 0x000000, "%d", begin_time);

		DrawGraph(0, 0, img[begin_time], TRUE);
	
	}

	if (timeup_cnt != 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (correct_num == THEME_MAX)
		{// お題を全てクリアしたら
			SetFontSize(100);
			DrawString(470, 200, "PERFECT!", 0x000000);
		}
		else
		{// 制限時間が0になったら
			//SetFontSize(100);
			//DrawString(470, 200, "TIME UP!", 0x000000);

			DrawGraph(30, -50, img[5], TRUE);
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

	// プレイヤーの入力とお題を比較
	if (tm[correct_num] == ip[correct_num])
	{// 同じだった場合
		correct_num++;
		combo++;
		player->SetPlayerInput();
	}
	else
	{// 異なる場合
		combo = 0;
		player->SetPlayerMis(correct_num);
		player->ResetPlayerInput(correct_num);
		player->ResetInputDraw(correct_num);
	}
	
}

void GameMainScene::TimeupAnim()
{
	timeup_cnt++;

	if (timeup_cnt == 1)
	{
		PlaySoundMem(sound[3], DX_PLAYTYPE_BACK, TRUE);
	}

	if (timeup_cnt == 50)
	{
		PlaySoundMem(sound[4], DX_PLAYTYPE_BACK, TRUE);
	}

	if (timeup_cnt == 130)
	{
		timeup_flg = true;
	}
}