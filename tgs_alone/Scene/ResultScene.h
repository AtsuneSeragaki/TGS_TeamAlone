#pragma once

#include "SceneBase.h"

#define NUM_Y 430
#define RANK_X 730
#define RANK_Y 235

class ResultScene : public SceneBase
{
private:
	int back_img[2];   // 背景画像 
	int num_img[10];   // 数字画像
	int rank_img[9];   // ランク画像
	int star_img;      // 星画像
	int tran_img;         // トランジション画像
	int se;            // 効果音
	int bgm;           // BGM
	int rank[3];       // ランクデータ
	char name[5][15];  // 名前データ
	int level[5];      // レベルデータ
	int combo[5];      // コンボデータ
	int star_cnt;      // 星の回転用
	bool tran_flg;        // 画面遷移 false:しない true:する
	float transition;     // トランジションの値保存用

public:

	static bool result;      // リザルトに遷移	 false:しない true:する

	// コンストラクタ
	ResultScene();

	// デストラクタ
	virtual ~ResultScene();

	// 初期化処理
	virtual void Initialize() override;

	// 更新処理
	virtual eSceneType Update() override;

	// 描画処理
	virtual void Draw() const override;

	// 終了時処理
	virtual void Finalize() override;

	// 現在のシーンを取得
	virtual eSceneType GetNowScene() const override;

	// 星の回転処理
	void StarAnim();

	// トランジション処理
	void Transition();
};