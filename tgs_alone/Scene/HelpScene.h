#pragma once

#include "SceneBase.h"

#define BUTTON_X 420  // ボタンのX座標
#define BUTTON_Y 340  // ボタンのY座標

#define PI    3.1415926535897932384626433832795f

class HelpScene : public SceneBase
{
private:
	int back_img[7];      // 背景画像 
	int button_img[4][6]; // ボタン画像
	int star_img;         // 星画像
	int tran_img;         // トランジション画像
	int cbutton_img[8];   // コントローラーのボタンの変化用画像
	int se;               // 効果音
	int bgm;              // BGM用
	int bcnt;             // ボタンアニメーションカウント用
	bool cnt_flg;         // ボタンアニメーションのカウントをするかしないかフラグ
	int anim;             // ボタンの動き用
	int star_cnt;         // 星の回転用
	bool tran_flg;        // 画面遷移 false:しない true:する
	int transition;       // トランジションの値保存用
	int cnt;              // フレームカウント
	int cbutton_num;      // コントローラーのボタンの変化用

public:
	static bool game_start;

	// コンストラクタ
	HelpScene();	

	// デストラクタ
	virtual ~HelpScene();

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

	// ボタンのアニメーション処理
	void ButtonAnim();

	// 星の回転処理
	void StarAnim();

	// 画面切り替えアニメーション
	void Transition();

	// 操作説明のボタンのアニメーション
	void OpeAnim();
};