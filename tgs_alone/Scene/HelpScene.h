#pragma once

#include "SceneBase.h"

#define BUTTON_X 420  // ボタンのX座標
#define BUTTON_Y 340  // ボタンのY座標

class HelpScene : public SceneBase
{
private:
	int back_img[6];      // 背景画像 
	int button_img[4][6]; // ボタン画像
	int star_img;         // 星画像
	int se;               // 効果音
	int bgm;              // BGM用
	int cnt;              // ボタンアニメーションカウント用
	bool cnt_flg;         // ボタンアニメーションのカウントをするかしないかフラグ
	int anim;             // ボタンの動き用
	int star_cnt;         // 星の回転用

public:

	// インストラクタ
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
};