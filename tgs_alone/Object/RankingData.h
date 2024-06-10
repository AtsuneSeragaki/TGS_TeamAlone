#pragma once

class RankingData
{
private:
	int level[5];
	int rank[5];
	int combo[5];
	char name[5][15];

public:
	RankingData();
	~RankingData();

	void Initialize();  // 初期処理
	void Finalize();    // 終了処理

	// ランキングデータの設定
	void SetRankingData(int level, int combo, const char* name);

	// スコア取得処理
	int GetLevel(int value) const;

	// タイム取得処理
	float GetCombo(int value) const;

	// スコア取得処理
	int GetRank(int value) const;

	// 名前取得処理
	const char* GetName(int value) const;

private:
	// データ入れ替え処理
	void SortData();
};