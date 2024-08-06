#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

#define PI    3.1415926535897932384626433832795f

class RankingScene : public SceneBase
{
private:
	int back_img;     // 背景画像 
	int star_img;     // 星画像
	int tran_img;     // トランジション画像
	int font_img[27]; // フォント画像
	int num_img[10];  // 数字画像
	int se[2];        // 効果音
	int bgm;          // BGM
	int font;         // フォント用
	int star_cnt;     // 星の回転用
	bool tran_flg;    // 画面遷移 false:しない true:する
	int transition;   // トランジションの値保存用

	RankingData* ranking; // ランキングデータのオブジェクト

public:

	static bool to_ranking; //ランキングに遷移 false:しない true:する 

	// コンストラクタ
	RankingScene();

	// デストラクタ
	virtual ~RankingScene();

	// 初期化処理
	virtual void Initialize() override;

	// 更新処理
	virtual eSceneType Update() override;

	// 描画処理
	virtual void Draw() const override;

	// 終了時処理
	virtual void Finalize() override;

	// 現在のシーン情報
	virtual eSceneType GetNowScene() const override;

	// 星の回転処理
	void StarAnim();

	// 画面切り替えアニメーション
	void Transition();
};