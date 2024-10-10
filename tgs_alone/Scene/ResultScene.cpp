#include "ResultScene.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
#include <math.h>
#include "DxLib.h"

bool ResultScene::result_tran = false;

ResultScene::ResultScene():back_img{0},bgm(0),se(0), star_img(0), star_cnt(0), transition(0), tran_img(0), tran_flg(false),cnt(0),rank_num(0),rank_cnt(0),level_max(0),level_num(0),combo_max(0),combo_num(0),mis_max(0),mis_num(0),numanim_cnt(0)
{
	for (int i = 0; i < 10; i++)
	{
		num_img[i] = 0;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			rank_img[i][j] = 0;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		level[i] = NULL;
		rank[i] = NULL;
		combo[i] = NULL;
		button_img[i] = 0;

		for (int j = 0; j < 10; j++)
		{
			name[i][j] = '\0';
		}
	}
}

ResultScene::~ResultScene()
{
	// 画像データの削除
	DeleteGraph(back_img[0]);
	DeleteGraph(back_img[1]);

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(num_img[i]);
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			DeleteGraph(rank_img[i][j]);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(button_img[i]);
	}

	DeleteGraph(tran_img);

	// 音データの削除
	DeleteSoundMem(se);
	DeleteSoundMem(bgm);
}

void ResultScene::Initialize()
{
	// 画像データの読み込み
	/*back_img[0] = LoadGraph("Resource/images/result/result.png");
	back_img[1] = LoadGraph("Resource/images/result/result2.png");*/

	back_img[0] = LoadGraph("Resource/images/result/result5.png");
	back_img[1] = LoadGraph("Resource/images/result/result3.png");
	LoadDivGraph("Resource/images/ranking/rank_num1.png", 10, 5, 2, 50, 50, num_img);
	rank_img[0][0] = LoadGraph("Resource/images/result/D1.png");
	rank_img[0][1] = LoadGraph("Resource/images/result/D2.png");
	rank_img[0][2] = LoadGraph("Resource/images/result/D3.png");
	rank_img[0][3] = LoadGraph("Resource/images/result/D4.png");
	rank_img[0][4] = LoadGraph("Resource/images/result/D.png");

	rank_img[1][0] = LoadGraph("Resource/images/result/C1.png");
	rank_img[1][1] = LoadGraph("Resource/images/result/C2.png");
	rank_img[1][2] = LoadGraph("Resource/images/result/C3.png");
	rank_img[1][3] = LoadGraph("Resource/images/result/C4.png");
	rank_img[1][4] = LoadGraph("Resource/images/result/C.png");

	rank_img[2][0] = LoadGraph("Resource/images/result/B_r1.png");
	rank_img[2][1] = LoadGraph("Resource/images/result/B_r2.png");
	rank_img[2][2] = LoadGraph("Resource/images/result/B_r3.png");
	rank_img[2][3] = LoadGraph("Resource/images/result/B_r4.png");
	rank_img[2][4] = LoadGraph("Resource/images/result/B_r.png");

	rank_img[3][0] = LoadGraph("Resource/images/result/A1.png");
	rank_img[3][1] = LoadGraph("Resource/images/result/A2.png");
	rank_img[3][2] = LoadGraph("Resource/images/result/A3.png");
	rank_img[3][3] = LoadGraph("Resource/images/result/A4.png");
	rank_img[3][4] = LoadGraph("Resource/images/result/A.png");

	rank_img[4][0] = LoadGraph("Resource/images/result/S1.png");
	rank_img[4][1] = LoadGraph("Resource/images/result/S2.png");
	rank_img[4][2] = LoadGraph("Resource/images/result/S3.png");
	rank_img[4][3] = LoadGraph("Resource/images/result/S4.png");
	rank_img[4][4] = LoadGraph("Resource/images/result/S.png");

	rank_img[5][0] = LoadGraph("Resource/images/result/fairy1.png");
	rank_img[5][1] = LoadGraph("Resource/images/result/fairy2.png");
	rank_img[5][2] = LoadGraph("Resource/images/result/fairy3.png");
	rank_img[5][3] = LoadGraph("Resource/images/result/fairy4.png");
	rank_img[5][4] = LoadGraph("Resource/images/result/fairy.png");

	rank_img[6][0] = LoadGraph("Resource/images/result/Princess1.png");
	rank_img[6][1] = LoadGraph("Resource/images/result/Princess2.png");
	rank_img[6][2] = LoadGraph("Resource/images/result/Princess3.png");
	rank_img[6][3] = LoadGraph("Resource/images/result/Princess4.png");
	rank_img[6][4] = LoadGraph("Resource/images/result/Princess.png");

	rank_img[7][0] = LoadGraph("Resource/images/result/mermaid1.png");
	rank_img[7][1] = LoadGraph("Resource/images/result/mermaid2.png");
	rank_img[7][2] = LoadGraph("Resource/images/result/mermaid3.png");
	rank_img[7][3] = LoadGraph("Resource/images/result/mermaid4.png");
	rank_img[7][4] = LoadGraph("Resource/images/result/mermaid.png");

	rank_img[8][0] = LoadGraph("Resource/images/result/Angel1.png");
	rank_img[8][1] = LoadGraph("Resource/images/result/Angel2.png");
	rank_img[8][2] = LoadGraph("Resource/images/result/Angel3.png");
	rank_img[8][3] = LoadGraph("Resource/images/result/Angel4.png");
	rank_img[8][4] = LoadGraph("Resource/images/result/Angel.png");

	star_img = LoadGraph("Resource/images/help/star.png");
	tran_img = LoadGraph("Resource/images/tansition/transition.png");
	button_img[0] = LoadGraph("Resource/images/result/b.png");
	button_img[1] = LoadGraph("Resource/images/result/enter-name1.png");
	button_img[2] = LoadGraph("Resource/images/result/title1.png");

	// 音データの読み込み
	se = LoadSoundMem("Resource/sounds/title/ok.mp3");
	bgm = LoadSoundMem("Resource/sounds/title/bgm.mp3");

	// エラーチェック
	if (back_img[0] == -1)
	{
		throw("Resource/images/result.pngがありません");
	}
	if (back_img[1] == -1)
	{
		throw("Resource/images/result.pngがありません");
	}
	if (star_img == -1)
	{
		throw("Resource/images/help/star.pngがありません");
	}
	if (tran_img == -1)
	{
		throw("Resource/images/tansition/transition.pngがありません");
	}
	if (se == -1)
	{
		throw("Resource/sounds/title/ok.mp3がありません");
	}
	if (bgm == -1)
	{
		throw("Resource/sounds/title/bgm.mp3がありません");
	}

	for (int i = 0; i < 10; i++)
	{
		if (num_img[i] == -1)
		{
			throw("num_img[%d]がありません",i);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (rank_img[i][j] == -1)
			{
				throw("rank_img[%d][%d]がありません", i,j);
			}
		}

		if (button_img[i] == -1)
		{
			throw("button_img[%d]がありません", i);
		}
	}

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);

	// ランキングデータの読み込み
	FILE * fp = nullptr;

	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.txt", "r");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.txtが開けませんでした\n");
	}

	// 対象ファイルから読み込む
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%d %s %d %d", &rank[i], name[i], 15, &level[i], &combo[i]);
	}

	// ファイルクローズ
	fclose(fp);

	// 変数の初期化
	star_cnt = 0;
	transition = -93;
	tran_flg = true;
	result_tran = true;
	rank_num = -1;
	rank_cnt = 0;
	level_max = Theme::theme_num - 2;
	combo_max = Player::combo;
	mis_max = Player::all_mis;
	/*level_max = 12;
	combo_max = 55;
	mis_max = 162;*/
	level_num = 0;
	combo_num = 0;
	mis_num = 0;
}

eSceneType ResultScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	if (cnt >= 90)
	{
		cnt = 0;
	}
	else
	{
		cnt++;
	}

	// 星を回転させる
	StarAnim();

	if (tran_flg == true)
	{
		if (result_tran == true  && transition <= 1943)
		{
			Transition();
		}
		else if (result_tran == true && transition > 1943)
		{
			result_tran = false;
			tran_flg = false;
		}
		else if (TitleScene::back_title == true && transition <= -120)
		{
			Transition();
		}
		else if (TitleScene::back_title == true && transition > -120)
		{
			return eSceneType::E_TITLE;
		}
		else if (transition <= -120)
		{
			Transition();
		}
		else
		{
			return eSceneType::E_INPUT_RANKING;
		}
	}
	else
	{
		// ランクアニメーション
		if (rank_num != 4)
		{
			if (rank_cnt == 0)
			{
				RankAnim();
				rank_cnt++;
			}
			else if (rank_cnt % 2 == 0)
			{
				RankAnim();
				rank_cnt++;
			}
			else
			{
				rank_cnt++;
			}
		}
		

		if (level_num != level_max || combo_num != combo_max || mis_num != mis_max)
		{
			if (numanim_cnt == 0)
			{
				NumAnim();
				numanim_cnt++;
			}
			else if (numanim_cnt % 3 == 0)
			{
				NumAnim();
				numanim_cnt++;
			}
			else
			{
				numanim_cnt++;
			}
		}

		// Bボタンを押したとき
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			// 効果音の再生
			PlaySoundMem(se, DX_PLAYTYPE_NORMAL, TRUE);

			// BGMの再生を止める
			StopSoundMem(bgm);

			if (level[2] < Theme::theme_num - 2)
			{// ランキングに載る成績なら、名前入力画面に遷移
				TitleScene::back_title = false;
				tran_flg = true;
				transition = -1943;
			}
			else if (level[2] == Theme::theme_num - 2 && combo[2] < Player::combo)
			{// ランキングに載る成績なら、名前入力画面に遷移
				TitleScene::back_title = false;
				tran_flg = true;
				transition = -1943;
			}
			else
			{// ランキングに載らない場合、タイトル画面に遷移
				TitleScene::back_title = true;
				tran_flg = true;
				transition = -1943;
			}
		}
	}
	
	return GetNowScene();
}

void ResultScene::Draw() const
{
	// 比較用のデータを格納
	/*int i = Theme::theme_num - 2;
	int j = Player::combo;
	int k = Player::all_mis;*/

	/*int i = 12;
	int j = 19;
	int k = 19;*/

	// 背景の描画
	DrawGraph(0, 0, back_img[0], TRUE);

	// 操作説明の描画
	// 名前入力画面に行くか行かないかで変える
	if (level[2] < level_max)
	{
		DrawGraph(480, 615 + sin(PI * 2 / 90 * cnt) * 6, button_img[0], TRUE);
		DrawGraph(460, 610, button_img[1], TRUE);
	}
	else if (level[2] == level_max && combo[2] < combo_max)
	{
		DrawGraph(480, 615 + sin(PI * 2 / 90 * cnt) * 6, button_img[0], TRUE);
		DrawGraph(460, 610, button_img[1], TRUE);
	}
	else
	{
		DrawGraph(570, 615 + sin(PI * 2 / 90 * cnt) * 6, button_img[0], TRUE);
		DrawGraph(550, 610, button_img[2], TRUE);
	}

	// 星の描画
	DrawRotaGraph(400, 100, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(910, 100, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	/*DrawRotaGraph(120, 640, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1160, 640, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);*/

	SetFontSize(110);

	if (rank_num != -1)
	{
		// ランクの表示
		if (level_max <= 1)
		{// D
			DrawGraph(RANK_X - (4 - rank_num) * 28, RANK_Y - (4 - rank_num) * 23, rank_img[0][rank_num], TRUE);
			//DrawString(RANK_X, RANK_Y, "D", 0x000000);
		}
		else if (level_max <= 3)
		{// C
			DrawGraph(RANK_X - (4 - rank_num) * 28, RANK_Y - (4 - rank_num) * 23, rank_img[1][rank_num], TRUE);
			//DrawString(RANK_X, RANK_Y, "C", 0x000000);
		}
		else if (level_max <= 5)
		{// B
			DrawGraph(RANK_X - (4 - rank_num) * 28, RANK_Y - (4 - rank_num) * 23, rank_img[2][rank_num], TRUE);
			//DrawString(RANK_X, RANK_Y, "B", 0x000000);
		}
		else if (level_max <= 7)
		{// A
			DrawGraph(RANK_X - (4 - rank_num) * 28, RANK_Y - (4 - rank_num) * 23, rank_img[3][rank_num], TRUE);
			//DrawString(RANK_X, RANK_Y, "A", 0x000000);
		}
		else if (level_max <= 9)
		{// S
			DrawGraph(RANK_X - (4 - rank_num) * 28, RANK_Y - (4 - rank_num) * 23, rank_img[4][rank_num], TRUE);
			//DrawString(RANK_X, RANK_Y, "S", 0x000000);
		}
		else if (level_max == 10)
		{// Fairy
			DrawGraph(630 - (4 - rank_num) * 70, RANK_Y + 5 - (4 - rank_num) * 23, rank_img[5][rank_num], TRUE);
			//DrawString(625, RANK_Y, "Fairy", 0x000000);
		}
		else if (level_max == 11)
		{// Princess
			DrawGraph(545 - (4 - rank_num) * 130, RANK_Y + 20 - (4 - rank_num) * 23, rank_img[6][rank_num], TRUE);
			//DrawString(555, RANK_Y, "Princess", 0x000000);
		}
		else if (level_max == 12)
		{// Mermaid
			DrawGraph(535 - (4 - rank_num) * 138, RANK_Y + 20 - (4 - rank_num) * 23, rank_img[7][rank_num], TRUE);
			//DrawString(580, RANK_Y, "Mermaid", 0x000000);
		}
		else
		{// Angel
			DrawGraph(550 - (4 - rank_num) * 90, RANK_Y + 5 - (4 - rank_num) * 23, rank_img[8][rank_num], TRUE);
			//DrawString(625, RANK_Y, "Angel", 0x000000);
		}
	}

	// クリアした最大レベルを表示
	if (level_max < 10)
	{
		/*DrawGraph(335, NUM_Y, num_img[i % 10], TRUE);*/
		DrawGraph(335, NUM_Y, num_img[level_num % 10], TRUE);
	}
	else
	{
		/*DrawGraph(315, NUM_Y, num_img[i / 10], TRUE);
		DrawGraph(360, NUM_Y, num_img[i % 10], TRUE);*/
		DrawGraph(315, NUM_Y, num_img[level_num / 10], TRUE);
		DrawGraph(360, NUM_Y, num_img[level_num % 10], TRUE);
	}

	// 最終的なコンボの表示
	if (combo_max < 10)
	{
		/*DrawGraph(645 + 5, NUM_Y, num_img[j % 10], TRUE);*/
		DrawGraph(645 + 5, NUM_Y, num_img[combo_num % 10], TRUE);

	}
	else if (combo_max >= 10 && combo_max < 20)
	{
		/*DrawGraph(622, NUM_Y, num_img[j / 10], TRUE);
		DrawGraph(667, NUM_Y, num_img[j % 10], TRUE);*/
		DrawGraph(622, NUM_Y, num_img[combo_num / 10], TRUE);
		DrawGraph(667, NUM_Y, num_img[combo_num % 10], TRUE);
	}
	else if (combo_max < 100)
	{
		/*DrawGraph(622 + 5, NUM_Y, num_img[j / 10], TRUE);
		DrawGraph(667 + 5, NUM_Y, num_img[j % 10], TRUE);*/
		DrawGraph(622 + 5, NUM_Y, num_img[combo_num / 10], TRUE);
		DrawGraph(667 + 5, NUM_Y, num_img[combo_num % 10], TRUE);
	}
	else if(combo_max >= 100 && combo_max < 200)
	{
		/*DrawGraph(599, NUM_Y, num_img[j / 100], TRUE);
		DrawGraph(645, NUM_Y, num_img[(j - j / 100 * 100) / 10], TRUE);
		DrawGraph(691, NUM_Y, num_img[j % 10], TRUE);*/
		DrawGraph(599, NUM_Y, num_img[combo_num / 100], TRUE);
		DrawGraph(645, NUM_Y, num_img[(combo_num - combo_num / 100 * 100) / 10], TRUE);
		DrawGraph(691, NUM_Y, num_img[combo_num % 10], TRUE);
	}
	else
	{
		/*DrawGraph(599 + 5, NUM_Y, num_img[j / 100], TRUE);
		DrawGraph(645 + 5, NUM_Y, num_img[(j - j / 100 * 100) / 10], TRUE);
		DrawGraph(691 + 5, NUM_Y, num_img[j % 10], TRUE);*/
		DrawGraph(599 + 5, NUM_Y, num_img[combo_num / 100], TRUE);
		DrawGraph(645 + 5, NUM_Y, num_img[(combo_num - combo_num / 100 * 100) / 10], TRUE);
		DrawGraph(691 + 5, NUM_Y, num_img[combo_num % 10], TRUE);
	}

	// 最終的な間違えた数の表示
	if (mis_max < 10)
	{
		/*DrawGraph(980 + 35, NUM_Y, num_img[k % 10], TRUE);*/
		DrawGraph(980 + 35, NUM_Y, num_img[mis_num % 10], TRUE);
	}
	else if (mis_max >= 10 && mis_max < 20)
	{
		/*DrawGraph(963 + 30, NUM_Y, num_img[k / 10], TRUE);
		DrawGraph(1008 + 30, NUM_Y, num_img[k % 10], TRUE);*/
		DrawGraph(963 + 30, NUM_Y, num_img[mis_num / 10], TRUE);
		DrawGraph(1008 + 30, NUM_Y, num_img[mis_num % 10], TRUE);
	}
	else if (mis_max < 100)
	{
		/*DrawGraph(963 + 35, NUM_Y, num_img[k / 10], TRUE);
		DrawGraph(1008 + 35, NUM_Y, num_img[k % 10], TRUE);*/
		DrawGraph(963 + 35, NUM_Y, num_img[mis_num / 10], TRUE);
		DrawGraph(1008 + 35, NUM_Y, num_img[mis_num % 10], TRUE);
	}
	else if(mis_max >= 100 && mis_max < 200)
	{
		/*DrawGraph(937 + 30, NUM_Y, num_img[k / 100], TRUE);
		DrawGraph(983 + 30, NUM_Y, num_img[(k - k / 100 * 100) / 10], TRUE);
		DrawGraph(1029 + 30, NUM_Y, num_img[k % 10], TRUE);*/
		DrawGraph(937 + 30, NUM_Y, num_img[mis_num / 100], TRUE);
		DrawGraph(983 + 30, NUM_Y, num_img[(mis_num - mis_num / 100 * 100) / 10], TRUE);
		DrawGraph(1029 + 30, NUM_Y, num_img[mis_num % 10], TRUE);
	}
	else
	{
		/*DrawGraph(937 + 37, NUM_Y, num_img[k / 100], TRUE);
		DrawGraph(983 + 37, NUM_Y, num_img[(k - k / 100 * 100) / 10], TRUE);
		DrawGraph(1029 + 37, NUM_Y, num_img[k % 10], TRUE);*/
		DrawGraph(937 + 37, NUM_Y, num_img[mis_num / 100], TRUE);
		DrawGraph(983 + 37, NUM_Y, num_img[(mis_num - mis_num / 100 * 100) / 10], TRUE);
		DrawGraph(1029 + 37, NUM_Y, num_img[mis_num % 10], TRUE);
	}

	if (tran_flg == true)
	{
		DrawGraph(transition, 0, tran_img, TRUE);
	}
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

void ResultScene::StarAnim()
{
	star_cnt++;

	// 180より大きくなったら0にする
	if (star_cnt > 180)
	{
		star_cnt = 0;
	}
}

void ResultScene::Transition()
{
	transition += 50;
}

void ResultScene::RankAnim()
{
	if (rank_num < 4)
	{
		rank_num++;
	}
	else
	{
		rank_num = 4;
	}
}

void ResultScene::NumAnim()
{
	if (level_num < level_max)
	{
		level_num++;
	}
	else
	{
		level_num = level_max;
	}

	if (level_num == level_max)
	{
		if (combo_num < combo_max)
		{
			if (combo_max >= 100)
			{
				combo_num += 15;
			}
			else if (combo_max >= 30)
			{
				combo_num += 7;
			}
			else
			{
				combo_num++;
			}
		}
		else
		{
			combo_num = combo_max;
		}
	}

	if (level_num == level_max && combo_num == combo_max)
	{
		if (mis_num < mis_max)
		{
			if (mis_max >= 100)
			{
				mis_num += 15;
			}
			else if (mis_max >= 30)
			{
				mis_num += 7;
			}
			else
			{
				mis_num++;
			}
		}
		else
		{
			mis_num = mis_max;
		}
	}
}