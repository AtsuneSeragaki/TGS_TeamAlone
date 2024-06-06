#include "GameMainScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

GameMainScene::GameMainScene() :player(nullptr), time(nullptr), theme(nullptr), begin_time(0),begin_cnt(0),draw_cnt(0),timeup_flg(false),timeup_cnt(0),pause(false),pause_cursor(0)
{
	for (int i = 0; i < 5; i++)
	{
		sound[i] = 0;
		
	}

	for (int i = 0; i < 7; i++)
	{
		img[i] = 0;
	}
}

GameMainScene::~GameMainScene()
{
	
}

void GameMainScene::Initialize()
{
	// 画像の読み込み
	img[3] = LoadGraph("Resource/images/count3.png");
	img[2] = LoadGraph("Resource/images/count2.png");
	img[1] = LoadGraph("Resource/images/count1.png");
	img[0] = LoadGraph("Resource/images/start.png");
	img[4] = LoadGraph("Resource/images/main.png");
	img[5] = LoadGraph("Resource/images/timeup.png");
	img[6] = LoadGraph("Resource/images/perfect.png");
	
	// サウンド読み込み
	sound[0] = LoadSoundMem("Resource/sounds/maou_bgm_cyber44.ogg");
	sound[1] = LoadSoundMem("Resource/sounds/countdown.mp3");
	sound[2] = LoadSoundMem("Resource/sounds/start.mp3");
	sound[3] = LoadSoundMem("Resource/sounds/game_end.mp3");
	sound[4] = LoadSoundMem("Resource/sounds/stop.mp3");

	// エラーチェック
	for (int i = 0; i < 7; i++)
	{
		if (img[i] == -1)
		{
			throw("img[%d]がありません\n", i);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (sound[i] == -1)
		{
			throw("sound[%d]がありません\n", i);
		}
	}

	// 変数の初期化
	begin_time = 3;
	begin_cnt = 0;
	draw_cnt = 0;
	timeup_flg = false;
	timeup_cnt = 0;
	pause = false;
	pause_cursor = 0;

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
}

eSceneType GameMainScene::Update()
{
	if (pause == true)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A) == true)
		{
			pause_cursor++;

			if (pause_cursor > 2)
			{
				pause_cursor = 0;
			}
		}

		if (InputControl::GetButtonDown(XINPUT_BUTTON_Y) == true)
		{
			pause_cursor--;

			if (pause_cursor < 0)
			{
				pause_cursor = 2;
			}
		}

		if (InputControl::GetButtonDown(XINPUT_BUTTON_B) == true)
		{
			switch (pause_cursor)
			{
			case 0:
				pause = false;
				break;
			case 1:
				pause = false;
				Finalize();
				Initialize();
				break;
			case 2:
				return eSceneType::E_TITLE;
			default:
				break;
			}
		}
	}
	else
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_START) == true)
		{
			pause = true;
		}

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
				else if (begin_time == 0)
				{
					PlaySoundMem(sound[2], DX_PLAYTYPE_BACK, TRUE);
				}
			}
		}

		// カウントダウン後に開始
		if (begin_time == -1)
		{
			//制限時間が0になったら
			if (time->GetTime() <= 0.0f || Player::correct_num == THEME_MAX)
			{
				player->SetPlayerAnim();

				if (Player::correct_num == THEME_MAX)
				{
					time->SetTimeFlg(false);
				}

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

					return eSceneType::E_RESULT;
				}
			}
			else
			{
				PlaySoundMem(sound[0], DX_PLAYTYPE_LOOP, FALSE);
				theme->Update();
				time->Update();
				player->Update();

				// プレイヤーがお題を全てクリアしたら次のお題へ
				if (Player::correct_num == theme->GetThemeNum() && theme->GetThemeNum() < THEME_MAX && player->GetInputDraw(Player::correct_num - 1) == true)
				{
					player->SetPlayerInput(true);

					if (draw_cnt == 10)
					{
						player->ResetPlayerState();
						theme->SetThemeNum();
						draw_cnt = 0;
						theme->SetThemeFlg(true);

						player->SetPlayerInput(false);
					}
					else
					{
						draw_cnt++;
					}
				}
			}
		}
	}
	return GetNowScene();
}

void GameMainScene::Draw() const
{
	if (pause == true)
	{// ポーズ
		// 背景描画
		DrawBox(0, 0, 1280, 720, 0x7d7d7d, TRUE);
		DrawString(0, 0, "Pause", 0xffffff);
		SetFontSize(40);
		DrawFormatString(0, 40, 0x000000, "%d", pause_cursor);
		switch (pause_cursor)
		{
		case 0:
			DrawString(0, 70, "resume", 0xffffff);
			break;
		case 1:
			DrawString(0, 70, "restart", 0xffffff);
			break;
		case 2:
			DrawString(0, 70, "back to title", 0xffffff);
			break;
		default:
			break;
		}
	}
	else
	{
		// 背景描画
		DrawGraph(0, 0, img[4], TRUE);

		if (begin_time == -1)
		{
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
			DrawGraph(0, 0, img[0], TRUE);

		}
		else
		{
			// ゲーム開始までのカウントダウン描画
			DrawGraph(0, 0, img[begin_time], TRUE);

		}

		if (timeup_cnt != 0)
		{
			if (Player::correct_num == THEME_MAX)
			{// お題を全てクリアしたら

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


				if (timeup_cnt <= 78)
				{
					DrawGraph(30, -600 + timeup_cnt * 7, img[6], TRUE);
				}
				else
				{
					DrawGraph(30, -50, img[6], TRUE);
				}
			}
			else
			{// 制限時間が0になったら
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				if (timeup_cnt <= 78)
				{
					DrawGraph(30, -600 + timeup_cnt * 7, img[5], TRUE);
				}
				else
				{
					DrawGraph(30, -50, img[5], TRUE);
				}
			}
		}
	}
}

void GameMainScene::Finalize()
{
	// 音データの削除
	for (int i = 0; i < 5; i++)
	{
		DeleteSoundMem(sound[i]);
	}

	// 画像データの削除
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(img[i]);
	}

	// オブジェクトの削除
	player->Finalize();
	delete player;
	time->Finalize();
	delete time;
	theme->Finalize();
	delete theme;
}

eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
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

	if (timeup_cnt == 200)
	{
		timeup_flg = true;
	}
}