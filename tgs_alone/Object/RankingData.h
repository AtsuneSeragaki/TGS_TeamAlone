#pragma once

#define RANKING_DATA 3

class RankingData
{
private:
	int level[RANKING_DATA];     // レベル
	int rank[RANKING_DATA];      // ランク
	int combo[RANKING_DATA];     // コンボ
	char name[RANKING_DATA][10]; // 名前

public:

	// コンストラクタ
	RankingData();

	// デストラクタ
	~RankingData();

	// 初期処理
	void Initialize();

	// 終了処理
	void Finalize();    

	// ランキングデータの設定
	void SetRankingData(int level, int combo, const char* name);

	// スコア取得処理
	int GetLevel(int value) const;

	// コンボ取得処理
	int GetCombo(int value) const;

	// スコア取得処理
	int GetRank(int value) const;

	// 名前取得処理
	const char* GetName(int value) const;

	// データ入れ替え処理
	void SortData();
};