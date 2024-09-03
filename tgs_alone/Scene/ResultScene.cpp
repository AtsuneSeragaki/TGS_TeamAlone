#include "ResultScene.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
#include <math.h>
#include "DxLib.h"

bool ResultScene::result_tran = false;

ResultScene::ResultScene():back_img{0},bgm(0),se(0), star_img(0), star_cnt(0), transition(0), tran_img(0), tran_flg(false),cnt(0)
{
	for (int i = 0; i < 10; i++)
	{
		num_img[i] = 0;
	}

	for (int i = 0; i < 9; i++)
	{
		rank_img[i] = 0;
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
		DeleteGraph(rank_img[i]);
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

	back_img[0] = LoadGraph("Resource/images/result/result4.png");
	back_img[1] = LoadGraph("Resource/images/result/result3.png");
	LoadDivGraph("Resource/images/result/result_num1.png", 10, 5, 2, 50, 50, num_img);
	rank_img[0] = LoadGraph("Resource/images/result/rank1.png");
	rank_img[1] = LoadGraph("Resource/images/result/rank2.png");
	rank_img[2] = LoadGraph("Resource/images/result/rank3.png");
	rank_img[3] = LoadGraph("Resource/images/result/rank3.png");
	rank_img[4] = LoadGraph("Resource/images/result/rank3.png");
	rank_img[5] = LoadGraph("Resource/images/result/rank3.png");
	rank_img[6] = LoadGraph("Resource/images/result/rank3.png");
	rank_img[7] = LoadGraph("Resource/images/result/rank3.png");
	rank_img[8] = LoadGraph("Resource/images/result/rank3.png");
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
		if (rank_img[i] == -1)
		{
			throw("rank_img[%d]がありません", i);
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

	int i = 12;
	int j = 200;
	int k = 200;

	// 背景の描画
	DrawGraph(0, 0, back_img[0], TRUE);

	// 操作説明の描画
	// 名前入力画面に行くか行かないかで変える
	if (level[2] < i)
	{
		DrawGraph(470, 600 + sin(PI * 2 / 90 * cnt) * 6, button_img[0], TRUE);
		DrawGraph(460, 600, button_img[1], TRUE);
	}
	else if (level[2] == i && combo[2] < j)
	{
		DrawGraph(470, 600 + sin(PI * 2 / 90 * cnt) * 6, button_img[0], TRUE);
		DrawGraph(460, 600, button_img[1], TRUE);
	}
	else
	{
		DrawGraph(550, 600 + sin(PI * 2 / 90 * cnt) * 6, button_img[0], TRUE);
		DrawGraph(550, 600, button_img[2], TRUE);
	}

	// 星の描画
	DrawRotaGraph(400, 100, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(910, 100, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	/*DrawRotaGraph(120, 640, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1160, 640, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);*/

	SetFontSize(110);

	// ランクの表示
	if (i <= 1)
	{// D
		//DrawGraph(RANK_X, RANK_Y, rank_img[0], TRUE);
		DrawString(RANK_X, RANK_Y, "D", 0x000000);
	}
	else if (i <= 3)
	{// C
		//DrawGraph(RANK_X, RANK_Y, rank_img[1], TRUE);
		DrawString(RANK_X, RANK_Y, "C", 0x000000);
	}
	else if (i <= 5)
	{// B
		//DrawGraph(RANK_X, RANK_Y, rank_img[2], TRUE);
		DrawString(RANK_X, RANK_Y, "B", 0x000000);
	}
	else if (i <= 7)
	{// A
		//DrawGraph(RANK_X, RANK_Y, rank_img[3], TRUE);
		DrawString(RANK_X, RANK_Y, "A", 0x000000);
	}
	else if (i <= 9)
	{// S
		//DrawGraph(RANK_X, RANK_Y rank_img[4], TRUE);
		DrawString(RANK_X, RANK_Y, "S", 0x000000);
	}
	else if (i == 10)
	{// Fairy
		//DrawGraph(573, RANK_Y, rank_img[5], TRUE);
		DrawString(625, RANK_Y, "Fairy", 0x000000);
	}
	else if (i == 11)
	{// Princess
		//DrawGraph(573, RANK_Y, rank_img[6], TRUE);
		DrawString(555, RANK_Y, "Princess", 0x000000);
	}
	else if (i == 12)
	{// Mermaid
		//DrawGraph(573, RANK_Y, rank_img[7], TRUE);
		DrawString(580, RANK_Y, "Mermaid", 0x000000);
	}
	else
	{// Angel
		//DrawGraph(573, RANK_Y, rank_img[8], TRUE);
		DrawString(625, RANK_Y, "Angel", 0x000000);
	}

	// クリアした最大レベルを表示
	if (i < 10)
	{
		DrawGraph(350, NUM_Y, num_img[i % 10], TRUE);
	}
	else
	{
		DrawGraph(328, NUM_Y, num_img[i / 10], TRUE);
		DrawGraph(372, NUM_Y, num_img[i % 10], TRUE);
	}

	// 最終的なコンボの表示
	if (j < 10)
	{
		DrawGraph(645, NUM_Y, num_img[j % 10], TRUE);
	}
	else if (j < 100)
	{
		DrawGraph(622, NUM_Y, num_img[j / 10], TRUE);
		DrawGraph(667, NUM_Y, num_img[j % 10], TRUE);
	}
	else
	{
		DrawGraph(599, NUM_Y, num_img[j / 100], TRUE);
		DrawGraph(645, NUM_Y, num_img[(j - j / 100 * 100) / 10], TRUE);
		DrawGraph(691, NUM_Y, num_img[j % 10], TRUE);
	}

	// 最終的な間違えた数の表示
	if (k < 10)
	{
		DrawGraph(980, NUM_Y, num_img[k % 10], TRUE);
	}
	else if (k < 100)
	{
		DrawGraph(963, NUM_Y, num_img[k / 10], TRUE);
		DrawGraph(1008, NUM_Y, num_img[k % 10], TRUE);
	}
	else
	{
		DrawGraph(937, NUM_Y, num_img[k / 100], TRUE);
		DrawGraph(983, NUM_Y, num_img[(k - k / 100 * 100) / 10], TRUE);
		DrawGraph(1029, NUM_Y, num_img[k % 10], TRUE);
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