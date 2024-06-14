#include "GameMainScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

GameMainScene::GameMainScene() :player(nullptr), time(nullptr), theme(nullptr),comment(nullptr), begin_time(0),begin_cnt(0),draw_cnt(0),timeup_flg(false),timeup_cnt(0),pause(false),pause_cursor(0)
{
	for (int i = 0; i < 5; i++)
	{
		sound[i] = 0;
		
	}

	for (int i = 0; i < 7; i++)
	{
		img[i] = 0;
	}

	for (int i = 0; i < 8; i++)
	{
		pause_img[i] = 0;
	}
}

GameMainScene::~GameMainScene()
{
	
}

void GameMainScene::Initialize()
{
	// 画像の読み込み
	img[3] = LoadGraph("Resource/images/main/count3.png");
	img[2] = LoadGraph("Resource/images/main/count2.png");
	img[1] = LoadGraph("Resource/images/main/count1.png");
	img[0] = LoadGraph("Resource/images/main/start.png");
	img[4] = LoadGraph("Resource/images/main/main.png");
	img[5] = LoadGraph("Resource/images/main/string/timeup.png");
	img[6] = LoadGraph("Resource/images/main/string/perfect.png");

	pause_img[0] = LoadGraph("Resource/images/pause/pausewin.png");
	pause_img[1] = LoadGraph("Resource/images/pause/resumeb.png");
	pause_img[2] = LoadGraph("Resource/images/pause/resume.png");
	pause_img[3] = LoadGraph("Resource/images/pause/restartb.png");
	pause_img[4] = LoadGraph("Resource/images/pause/restart.png");
	pause_img[5] = LoadGraph("Resource/images/pause/backb.png");
	pause_img[6] = LoadGraph("Resource/images/pause/back.png");
	pause_img[7] = LoadGraph("Resource/images/pause/updownUI.png");

	// サウンド読み込み
	sound[0] = LoadSoundMem("Resource/sounds/main/maou_bgm_cyber44.ogg");
	sound[1] = LoadSoundMem("Resource/sounds/main/se/countdown.mp3");
	sound[2] = LoadSoundMem("Resource/sounds/main/se/start.mp3");
	sound[3] = LoadSoundMem("Resource/sounds/main/se/game_end.mp3");
	sound[4] = LoadSoundMem("Resource/sounds/main/se/stop.mp3");

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
	comment = new Comment;

	// オブジェクトの初期化
	player->Initialize();
	time->Initialize();
	theme->Initialize();
	comment->Initialize();

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
				if (Player::correct_num == theme->GetThemeNum())
				{
					Player::correct_num++;
				}

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
				comment->Update();

				// プレイヤーがお題を全てクリアしたら次のお題へ
				if (Player::correct_num == Theme::theme_num && Theme::theme_num < THEME_MAX && player->GetInputDraw(Player::correct_num - 1) == true)
				{
					comment->SetDispFlg(true);
					comment->SetNum(Player::correct_num, Theme::theme_num);
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

		// コメントの描画
		comment->Draw();
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

	if (pause == true)
	{// ポーズ
		// 背景描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawGraph(348, 140, pause_img[0], TRUE);
		DrawGraph(900, 600, pause_img[7], TRUE);

		switch (pause_cursor)
		{
		case 0:
			DrawGraph(538, 255, pause_img[1], TRUE);
			DrawGraph(545, 347, pause_img[4], TRUE);
			DrawGraph(470, 440, pause_img[6], TRUE);
			break;
		case 1:
			DrawGraph(538, 255, pause_img[2], TRUE);
			DrawGraph(545, 347, pause_img[3], TRUE);
			DrawGraph(470, 440, pause_img[6], TRUE);
			break;
		case 2:
			DrawGraph(538, 255, pause_img[2], TRUE);
			DrawGraph(545, 347, pause_img[4], TRUE);
			DrawGraph(470, 440, pause_img[5], TRUE);
			break;
		default:
			break;
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
	comment->Finalize();
	delete comment;
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