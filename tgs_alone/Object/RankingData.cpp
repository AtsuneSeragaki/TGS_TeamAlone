#include "RankingData.h"
#include <stdio.h>
#include <string.h>

RankingData::RankingData()
{
	for (int i = 0; i < 5; i++)
	{
		score[i] = NULL;
		rank[i] = NULL;
		time[i] = NULL;

		for (int j = 0; j < 15; j++)
		{
			name[i][j] = '\0';
		}
	}
}

RankingData::~RankingData()
{
}

void RankingData::Initialize()
{
	// ランキングデータの読み込み
	FILE* fp = nullptr;

	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
	}

	// 対象ファイルから読み込む
	for (int i = 0; i < 4; i++)
	{
		fscanf_s(fp, "%2d,%.2f,%2d,%[^,],\n", &score[i], &time[i], &rank[i], name[i], 15);
	}

	// ファイルクローズ
	fclose(fp);

	// 末尾データの設定
	score[4] = 0;
	time[4] = 0.0f;
	rank[4] = 0;
	name[4][0] = '\0';
}

void RankingData::Finalize()
{

}

void RankingData::SetRankingData(int score, float time, const char* name)
{
	this->score[4] = score;
	this->time[4] = time;
	strcpy_s(this->name[4], name);

	SortData();
}

int RankingData::GetScore(int value) const
{
	return score[value];
}

float RankingData::GetTime(int value) const
{
	return time[value];
}

int RankingData::GetRank(int value) const
{
	return rank[value];
}

const char* RankingData::GetName(int value) const
{
	return name[value];
}

void RankingData::SortData()
{
	//// 選択法ソートを使用し、降順で入れ替える
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = i + 1; j < 5; j++)
	//	{
	//		if (score[i] <= score[j] && time[i] <= time[j])
	//		{
	//			int tmp = score[i];
	//			score[i] = score[j];
	//			score[j] = tmp;

	//			float tmp = time[i];
	//			time[i] = time[j];
	//			time[j] = tmp;

	//			char buf[15] = {};
	//			strcpy_s(buf, name[j]);
	//			strcpy_s(name[i], name[j]);
	//			strcpy_s(name[j], buf);
	//		}
	//		
	//	}
	//}

	//// 順位を整列させる
	//for(int i = 0; i < 4; i++)
}
