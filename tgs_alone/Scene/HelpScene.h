#pragma once

#include "SceneBase.h"

class HelpScene : public SceneBase
{
private:
	int back_img;    // 背景画像 
	int button_img[4][6]; // ボタン画像
	int cnt; // カウント用
	bool cnt_flg;
	int anim; // ボタンの動き用

public:
	HelpScene();
	virtual ~HelpScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};