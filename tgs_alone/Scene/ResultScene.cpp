#include "ResultScene.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

ResultScene::ResultScene():back_img{0},bgm(0),se(0), star_img(0), star_cnt(0)
{
	for (int i = 0; i < 10; i++)
	{
		num_img[i] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		rank_img[i] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		level[i] = NULL;
		rank[i] = NULL;
		combo[i] = NULL;

		for (int j = 0; j < 10; j++)
		{
			name[i][j] = '\0';
		}
	}
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	// 画像データの読み込み
	back_img[0] = LoadGraph("Resource/images/result/result.png");
	back_img[1] = LoadGraph("Resource/images/result/result2.png");
	LoadDivGraph("Resource/images/result/result_num.png", 10, 5, 2, 75, 75, num_img);
	rank_img[0] = LoadGraph("Resource/images/result/rank1.png");
	rank_img[1] = LoadGraph("Resource/images/result/rank2.png");
	rank_img[2] = LoadGraph("Resource/images/result/rank3.png");
	star_img = LoadGraph("Resource/images/help/star.png");

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
}

eSceneType ResultScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// 星を回転させる
	StarAnim();
	
	// Bボタンを押したとき
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		// 効果音の再生
		PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);

		// BGMの再生を止める
		StopSoundMem(bgm);
		
		if (level[2] < Theme::theme_num - 3)
		{// ランキングに載る成績なら、名前入力画面に遷移
			return eSceneType::E_INPUT_RANKING;
		}
		else if (level[2] == Theme::theme_num - 3 && combo[2] < Player::combo)
		{// ランキングに載る成績なら、名前入力画面に遷移
			return eSceneType::E_INPUT_RANKING;
		}
		else
		{// ランキングに載らない場合、タイトル画面に遷移
			return eSceneType::E_TITLE;
		}
	}
	
	return GetNowScene();
}

void ResultScene::Draw() const
{
	// 比較用のデータを格納
	int i = Theme::theme_num - 3;
	int j = Player::combo;

	// 背景画像表示
	// 名前入力画面に行くか行かないかで変える
	if (level[2] < i)
	{
		DrawGraph(0, 0, back_img[1], TRUE);
	}
	else if (level[2] == i && combo[2] < j)
	{
		DrawGraph(0, 0, back_img[1], TRUE);
	}
	else
	{
		DrawGraph(0, 0, back_img[0], TRUE);
	}

	// 星の描画
	DrawRotaGraph(120, 80, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1160, 80, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(120, 640, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1160, 640, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);

	// ランクの表示
	if (i < 6)
	{
		DrawGraph(625, 253, rank_img[0], TRUE);
	}
	else if (i < 12)
	{
		DrawGraph(573, 258, rank_img[1], TRUE);
	}
	else
	{
		DrawGraph(595, 242, rank_img[2], TRUE);
	}
	

	// クリアした最大レベルを表示
	if (i < 10)
	{
		DrawGraph(428, NUM_Y, num_img[0], TRUE);
		DrawGraph(490, NUM_Y, num_img[i % 10], TRUE);
	}
	else
	{
		DrawGraph(422, NUM_Y, num_img[i / 10], TRUE);
		DrawGraph(482, NUM_Y, num_img[i % 10], TRUE);
	}

	// 最終的なコンボの表示
	if (j < 10)
	{
		DrawGraph(898, NUM_Y, num_img[0], TRUE);
		DrawGraph(960, NUM_Y, num_img[j % 10], TRUE);
	}
	else if (j < 100)
	{
		DrawGraph(898, NUM_Y, num_img[j / 10], TRUE);
		DrawGraph(960, NUM_Y, num_img[j % 10], TRUE);
	}
	else
	{
		DrawGraph(856, NUM_Y, num_img[j / 100], TRUE);
		DrawGraph(913, NUM_Y, num_img[(j - j / 100 * 100) / 10], TRUE);
		DrawGraph(980, NUM_Y, num_img[j % 10], TRUE);
	}
}

void ResultScene::Finalize()
{
	// 画像データの削除
	DeleteGraph(back_img[0]);
	DeleteGraph(back_img[1]);

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(num_img[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(rank_img[i]);
	}
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