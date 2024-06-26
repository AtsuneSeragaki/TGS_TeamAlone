﻿ #include "RankingData.h"
#include <stdio.h>
#include <string.h>

RankingData::RankingData()
{
	for (int i = 0; i < RANKING_DATA; i++)
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

RankingData::~RankingData()
{
}

void RankingData::Initialize()
{
	// ランキングデータの読み込み
	FILE* fp = nullptr;

	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.txt", "r");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.txtが開けませんでした\n");
	}

	// 対象ファイルから読み込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fscanf_s(fp, "%d %s %d %d", &rank[i],name[i],10, &level[i], &combo[i]);
	}

	// ファイルクローズ
	fclose(fp);
}

void RankingData::Finalize()
{

}

void RankingData::SetRankingData(int level, int combo, const char* name)
{
	this->level[2] = level;
	this->combo[2] = combo;
	strcpy_s(this->name[2], name);

	SortData();
}

int RankingData::GetLevel(int value) const
{
	return level[value];
}

int RankingData::GetCombo(int value) const
{
	return combo[value];
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
	// 選択法ソートを使用し、降順で入れ替える
	for (int i = 0; i < RANKING_DATA - 1; i++)
	{
		for (int j = i + 1; j < RANKING_DATA; j++)
		{
			if (level[i] < level[j])
			{
				int tmp = level[i];
				level[i] = level[j];
				level[j] = tmp;

				int tmp2 = combo[i];
				combo[i] = combo[j];
				combo[j] = tmp2;

				char buf[10] = {};
				strcpy_s(buf, name[i]);
				strcpy_s(name[i], name[j]);
				strcpy_s(name[j], buf);
			}
			else if (level[i] == level[j] && combo[i] < combo[j])
			{
				int tmp = level[i];
				level[i] = level[j];
				level[j] = tmp;

				int tmp2 = combo[i];
				combo[i] = combo[j];
				combo[j] = tmp2;

				char buf[10] = {};
				strcpy_s(buf, name[i]);
				strcpy_s(name[i], name[j]);
				strcpy_s(name[j], buf);
			}
		}
	}

	// 順位を整列させる
	for (int i = 0; i < RANKING_DATA; i++)
	{
		rank[i] = 1;
	}
	for (int i = 0; i < RANKING_DATA - 1; i++)
	{
		for (int j = i + 1; j < RANKING_DATA; j++)
		{
			if (level[i] > level[j])
			{
				rank[j]++;
			}
			else if (level[i] == level[j] && combo[i] > combo[j])
			{
				rank[j]++;
			}
		}
	}

	// ランキングデータの書き込み
	FILE* fp = nullptr;

	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.txt", "w");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.txtが開けませんでした\n");
	}

	// 対象ファイルに書き込み
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fprintf(fp, "%d %s %d %d\n", rank[i], name[i],level[i], combo[i]);
	}

	// ファイルクローズ
	fclose(fp);
}
