#pragma once

#include "SceneBase.h"

class HelpScene : public SceneBase
{
private:
	int back_img[6];      // 背景画像 
	int button_img[4][6]; // ボタン画像
	int cnt;              // カウント用
	bool cnt_flg;         // カウントするかしないかフラグ
	int anim;             // ボタンの動き用
	int se;               // SE用
	int bgm;              // BGM用
	int ui_anim;          // UIボタンの動き用
	int back_cnt;         // 背景の動き用

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

	// 背景のスクロール処理
	void BackScrool();
};