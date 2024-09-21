#include "GameMainScene.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include <math.h>
#include "DxLib.h"

GameMainScene::GameMainScene() :player(nullptr), time(nullptr), theme(nullptr),comment(nullptr), begin_time(0),begin_cnt(0),draw_cnt(0),timeup_flg(false),timeup_cnt(0),pause(false),pause_cursor(0), transition(0), tran_img(0), tran_flg(false),restart(false),cnt(0),goal(false)
{
	se[0] = 0;
	se[1] = 0;

	for (int i = 0; i < 6; i++)
	{
		sound[i] = 0;
		
	}

	for (int i = 0; i < 3; i++)
	{
		button[i] = 0;
	}

	for (int i = 0; i < 8; i++)
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
	// 音データの削除
	for (int i = 0; i < 6; i++)
	{
		DeleteSoundMem(sound[i]);
	}

	// 画像データの削除
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(img[i]);
	}

	DeleteGraph(tran_img);
}

void GameMainScene::Initialize()
{
	// 画像の読み込み
	img[3] = LoadGraph("Resource/images/main/count3.png");
	img[2] = LoadGraph("Resource/images/main/count2.png");
	img[1] = LoadGraph("Resource/images/main/count1.png");
	img[0] = LoadGraph("Resource/images/main/start.png");
	//img[4] = LoadGraph("Resource/images/main/main.png");
	img[4] = LoadGraph("Resource/images/main/main5.png");
	img[5] = LoadGraph("Resource/images/main/string/timeup.png");
	img[6] = LoadGraph("Resource/images/main/string/perfect.png");
	img[7] = LoadGraph("Resource/images/main/count.png");

	pause_img[0] = LoadGraph("Resource/images/pause/pause.png");
	pause_img[1] = LoadGraph("Resource/images/pause/resume_choice.png");
	pause_img[2] = LoadGraph("Resource/images/pause/resume_basic.png");
	pause_img[3] = LoadGraph("Resource/images/pause/restart_choice.png");
	pause_img[4] = LoadGraph("Resource/images/pause/restart_basic.png");
	pause_img[5] = LoadGraph("Resource/images/pause/backtotitle_choice.png");
	pause_img[6] = LoadGraph("Resource/images/pause/backtotitle_basic.png");
	pause_img[7] = LoadGraph("Resource/images/title/up-down-select.png");

	tran_img = LoadGraph("Resource/images/tansition/transition.png");

	button[0] = LoadGraph("Resource/images/ranking/a.png");
	button[1] = LoadGraph("Resource/images/ranking/y.png");
	button[2] = LoadGraph("Resource/images/ranking/b.png");

	// サウンド読み込み
	sound[0] = LoadSoundMem("Resource/sounds/main/maou_bgm_cyber44.mp3");
	sound[1] = LoadSoundMem("Resource/sounds/main/se/countdown.mp3");
	sound[2] = LoadSoundMem("Resource/sounds/main/se/start.mp3");
	sound[3] = LoadSoundMem("Resource/sounds/main/se/game_end.mp3");
	sound[4] = LoadSoundMem("Resource/sounds/main/se/timeup2.mp3");
	sound[5] = LoadSoundMem("Resource/sounds/main/se/goal.mp3");

	se[0] = LoadSoundMem("Resource/sounds/title/move.mp3");
	se[1] = LoadSoundMem("Resource/sounds/title/ok.mp3");

	// エラーチェック
	for (int i = 0; i < 8; i++)
	{
		if (img[i] == -1)
		{
			throw("img[%d]がありません\n", i);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (button[i] == -1)
		{
			throw("button[%d]がありません\n", i);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (pause_img[i] == -1)
		{
			throw("pause_img[%d]がありません\n", i);
		}
	}

	if (tran_img == -1)
	{
		throw("Resource/images/tansition/transition.pngがありません");
	}

	for (int i = 0; i < 6; i++)
	{
		if (sound[i] == -1)
		{
			throw("sound[%d]がありません\n", i);
		}
	}

	if (se[0] == -1)
	{
		throw("Resource/sounds/title/move.mp3がありません");
	}
	if (se[1] == -1)
	{
		throw("Resource/sounds/title/ok.mp3がありません");
	}

	// 変数の初期化
	begin_time = 4;
	begin_cnt = 0;
	draw_cnt = 0;
	timeup_flg = false;
	timeup_cnt = 0;
	pause = false;
	pause_cursor = 0;
	transition = -93;
	tran_flg = true;
	cnt = 0;
	goal = false;

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
	if (tran_flg == true)
	{
		if (TitleScene::back_title == true && transition <= -120)
		{
			Transition();
		}
		else if (TitleScene::back_title == true && transition > -120)
		{
			// タイトル画面に遷移
			return eSceneType::E_TITLE;
		}
		else if (restart == true && transition <= -120)
		{
			Transition();
		}
		else if (restart == true && transition > -120)
		{
			restart = false;
			pause = false;
			Finalize();
			Initialize();
		}
		else if (ResultScene::result_tran == true && transition <= -120)
		{
			Transition();
		}
		else if (ResultScene::result_tran == true && transition > -120)
		{
			return eSceneType::E_RESULT;
		}
		else if (transition <= 1934)
		{
			Transition();
		}
		else
		{
			tran_flg = false;
			transition = -1943;
		}
	}
	else
	{
		if (pause == true)
		{// ポーズ中だったら

			// BGMの再生を止める
			StopSoundMem(sound[0]);

			OpeAnim();

			if (InputControl::GetButtonDown(XINPUT_BUTTON_A) == true)
			{
				// 効果音の再生
				PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

				pause_cursor++;

				if (pause_cursor > 2)
				{
					pause_cursor = 0;
				}
			}

			if (InputControl::GetButtonDown(XINPUT_BUTTON_Y) == true)
			{
				// 効果音の再生
				PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

				pause_cursor--;

				if (pause_cursor < 0)
				{
					pause_cursor = 2;
				}
			}

			if (InputControl::GetButtonDown(XINPUT_BUTTON_B) == true)
			{
				// 効果音の再生
				PlaySoundMem(se[1], DX_PLAYTYPE_NORMAL, TRUE);

				switch (pause_cursor)
				{
				case 0:
					pause = false;
					break;

				case 1:
					tran_flg = true;
					restart = true;
					transition = -1943;
					break;

				case 2:
					tran_flg = true;
					TitleScene::back_title = true;
					transition = -1943;
					break;

				default:
					break;
				}
			}
		}
		else
		{// ポーズ中じゃなかったら

			// STARTボタンが押されたら
			if (InputControl::GetButtonDown(XINPUT_BUTTON_START) == true)
			{
				// 効果音の再生
				PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);

				// ポーズ中にする
				pause = true;
			}

			// 開始のカウントダウン
			if (begin_time != -1)
			{
				//if (begin_time == 4 && begin_cnt == 0)
				//{
				//	// 効果音の再生
				//	PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
				//}

				begin_cnt++;

				if (begin_cnt % 60 == 0)
				{
					begin_time--;

					if (begin_time > 0)
					{
						// 効果音の再生
						PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
					}
					else if (begin_time == 0)
					{
						// 効果音の再生
						PlaySoundMem(sound[2], DX_PLAYTYPE_BACK, TRUE);
					}
				}
			}

			// カウントダウン後に開始
			if (begin_time == -1)
			{
				if (time->GetTime() <= 0.0f)
				{//制限時間が0になったら
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

						tran_flg = true;
						ResultScene::result_tran = true;
						transition = -1943;
					}

				}
				else
				{
					// BGMの再生
					PlaySoundMem(sound[0], DX_PLAYTYPE_LOOP, FALSE);

					// お題の更新処理
					theme->Update();

					if (comment->GetDispFlg() == false)
					{
						// タイムの更新処理
						time->Update();
					}

					// プレイヤーの更新処理
					player->Update();

					// コメントの更新処理
					comment->Update();

					if (Player::correct_num == Theme::theme_num && Theme::theme_num == THEME_MAX)
					{
						goal = true;

						player->SetPlayerAnim();

						time->SetTimeFlg(false);

						// BGMを止める
						StopSoundMem(sound[0]);

						// 終了の表示
						TimeupAnim();

						// 終了の表示後、リザルト画面へ
						if (timeup_flg == true)
						{
							goal = false;

							if (draw_cnt != 0)
							{
								draw_cnt = 0;
							}

							tran_flg = true;
							ResultScene::result_tran = true;
							transition = -1943;
						}
					}
					else if (Player::correct_num == Theme::theme_num && player->GetInputDraw(Player::correct_num - 1) == true)
					{// プレイヤーがお題を全てクリアしたら次のお題へ
						player->SetPlayerInput(true);
						comment->SetNum(Player::mis_num, Theme::theme_num);
						comment->SetComNum();
						comment->SetDispFlg(true);

						/*if (draw_cnt <= 10)
						{
							comment->FadeInOut(false);
						}
						else if (draw_cnt >= 50 && draw_cnt <= 70)
						{
							comment->FadeInOut(true);
						}*/

						if (draw_cnt == 0)
						{
							// ノーミスでレベルをクリアしたら時間追加
							if (Player::mis_num == 0)
							{
								if (Theme::theme_num - 2 < 10)
								{
									time->SetAddTime(true, 1);
								}
								else if (Theme::theme_num - 2 < 12)
								{
									time->SetAddTime(true, 2);
								}
								else
								{
									time->SetAddTime(true, 3);
								}
							}
						}

						if (draw_cnt <= 10)
						{
							time->FadeInOut(false);
						}
						else if (draw_cnt >= 50 && draw_cnt <= 70)
						{
							time->FadeInOut(true);

							if (draw_cnt == 68)
							{
								time->Update();
							}
						}

						if (draw_cnt == 71)
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
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	if (begin_time == -1)
	{
		// 背景描画
		DrawGraph(0, 0, img[4], TRUE);

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
	else if (begin_time == 4)
	{
		DrawGraph(0, 0, img[7], TRUE);
	}
	else
	{
		// ゲーム開始までのカウントダウン描画
		DrawGraph(0, 0, img[begin_time], TRUE);
	}

	if (timeup_cnt != 0)
	{
		if (Player::correct_num == Theme::theme_num && Theme::theme_num == THEME_MAX)
		{// お題を全てクリアしたら

			// 背景の描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// Parfectの描画
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

			// Timeupの描画
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
	{// ポーズ中

		// 背景描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawGraph(348, 100, pause_img[0], TRUE);
		DrawGraph(800, 600, pause_img[7], TRUE);
		DrawGraph(803, 600 + sin(PI * 2 / 90 * cnt) * 6, button[1], TRUE);
		DrawGraph(921, 600 + sin(PI * 2 / 90 * cnt) * 6, button[0], TRUE);
		DrawGraph(1092, 600 + sin(PI * 2 / 90 * cnt) * 6, button[2], TRUE);

		// メニューの描画
		switch (pause_cursor)
		{
		case 0:
			DrawGraph(538, 215 + sin(PI * 2 / 90 * cnt) * 6, pause_img[1], TRUE);
			DrawGraph(545, 317, pause_img[4], TRUE);
			DrawGraph(480, 430, pause_img[6], TRUE);
			break;
		case 1:
			DrawGraph(538, 215, pause_img[2], TRUE);
			DrawGraph(545, 317 + sin(PI * 2 / 90 * cnt) * 6, pause_img[3], TRUE);
			DrawGraph(480, 430, pause_img[6], TRUE);
			break;
		case 2:
			DrawGraph(538, 215, pause_img[2], TRUE);
			DrawGraph(545, 317, pause_img[4], TRUE);
			DrawGraph(480, 430 + sin(PI * 2 / 90 * cnt) * 6, pause_img[5], TRUE);
			break;
		default:
			break;
		}
	}

	if (tran_flg == true)
	{
		DrawGraph(transition, 0, tran_img, TRUE);
	}
}

void GameMainScene::Finalize()
{
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
		// サウンドの再生
		PlaySoundMem(sound[3], DX_PLAYTYPE_BACK, TRUE);
	}

	if (timeup_cnt == 50)
	{
		// サウンドの再生
		if (goal == true)
		{
			PlaySoundMem(sound[5], DX_PLAYTYPE_BACK, TRUE);
		}
		else
		{
			PlaySoundMem(sound[4], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	if (timeup_cnt == 200)
	{
		timeup_flg = true;
	}
}

void GameMainScene::Transition()
{
	if (transition <= 1934)
	{
		transition += 50;
	}
}

void GameMainScene::OpeAnim()
{
	if (cnt >= 90)
	{
		cnt = 0;
	}
	else
	{
		cnt++;
	}
}