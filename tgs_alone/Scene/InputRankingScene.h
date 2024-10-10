#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

#define PI    3.1415926535897932384626433832795f

class InputRankingScene : public SceneBase
{
private:
	int img[7];       // 背景画像
	int star_img;     // 星画像
	int tran_img;     // トランジション画像
	int font_img[27]; // フォント画像（黒）
	int font_img2[27]; // フォント画像大きめ
	int font_img3[27]; // フォント画像（カラー）
	int button[4];    
	int font;         // フォントデータ
	int se[2];        // 効果音データ
	int bgm;          // BGMデータ
	int level;        // プレイヤーの最終的なレベル数
	int combo;        // プレイヤーの最終的なコンボ数
	char name[6];     // プレイヤーが入力した名前
	int name_num;     // 入力した名前の数
	int cursor_x;     // カーソルのX座標
	int cursor_y;     // カーソルのY座標
	bool no_name;     // 名前が入力されてない場合はtrue 
	int star_cnt;     // 星の回転用
	bool input_end;   // 名前入力終了フラグ
	bool tran_flg;    // 画面遷移 false:しない true:する
	int transition;   // トランジションの値保存用
	int cnt;          // 文字点滅用カウント
	int cnt2;         // フレームカウント
	int lcnt;         // LeftAnim()で使うカウント
	int rcnt;         // RightAnim()で使うカウント
	int plus_lx;      // 左の矢印のX座標に足す数
	int plus_rx;      // 右の矢印のX座標に足す数
	bool lmove;
	bool rmove;

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

	// 操作説明のボタンのアニメーション
	void OpeAnim();

	// Xボタンが押された時の矢印アニメーション
	void LeftAnim();

	// Bボタンが押された時の矢印アニメーション
	void RightAnim();
};