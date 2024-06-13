#include "ResultScene.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

ResultScene::ResultScene():back_img{0}
{
	for (int i = 0; i < 10; i++)
	{
		num_img[i] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		rank_img[i] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		level[i] = NULL;
		rank[i] = NULL;
		combo[i] = NULL;

		for (int j = 0; j < 15; j++)
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

	// エラーチェック
	if (back_img[0] == -1)
	{
		throw("Resource/images/result.pngがありません");
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
	for (int i = 0; i < 4; i++)
	{
		fscanf_s(fp, "%d %s %d %d", &rank[i], name[i], 15, &level[i], &combo[i]);
	}

	// ファイルクローズ
	fclose(fp);

}

eSceneType ResultScene::Update()
{
	
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		if (level[3] < Theme::theme_num - 3)
		{
			return eSceneType::E_INPUT_RANKING;
		}
		else if (level[3] == Theme::theme_num - 3 && combo[3] < Player::combo)
		{
			return eSceneType::E_INPUT_RANKING;
		}
		else
		{
			return eSceneType::E_TITLE;
		}
	}
	
	return GetNowScene();
}

void ResultScene::Draw() const
{
#ifdef _DEBUG
	

#endif // _DEBUG

	int i = Theme::theme_num - 3;
	int j = Player::combo;

	// 背景画像表示
	if (level[3] < i)
	{
		DrawGraph(0, 0, back_img[1], TRUE);
	}
	else if (level[3] == i && combo[3] < j)
	{
		DrawGraph(0, 0, back_img[1], TRUE);
	}
	else
	{
		DrawGraph(0, 0, back_img[0], TRUE);
	}

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