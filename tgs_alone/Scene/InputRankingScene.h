#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class InputRankingScene : public SceneBase
{
private:
	int img[7];     // 画像データ用
	int star_img;   // 星画像
	int tran_img;         // トランジション画像
	int font;       // フォントデータ
	int se[3];      // 効果音
	int bgm;        // BGM
	int level;      // プレイヤーの最終的なレベル数
	int combo;      // プレイヤーの最終的なコンボ数
	char name[6];  // プレイヤーが入力した名前
	int name_num;   // 入力した名前の数
	int cursor_x;   // カーソルのX座標
	int cursor_y;   // カーソルのY座標
	bool no_name;   // 名前が入力されてない場合はtrue 
	int star_cnt;   // 星の回転用
	bool input_end; // 名前入力終了フラグ
	bool tran_flg;        // 画面遷移 false:しない true:する
	int transition;     // トランジションの値保存用
	RankingData* ranking; // ランキング情報

public:

	// コンストラクタ
	InputRankingScene();

	// デストラクタ
	virtual ~InputRankingScene();

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

	// 名前入力処理
	bool InputName();

	// 星の回転処理
	void StarAnim();

	// 画面切り替えアニメーション
	void Transition();
};