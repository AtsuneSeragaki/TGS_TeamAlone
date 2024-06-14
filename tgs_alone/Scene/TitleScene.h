#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int back_img;     // 背景画像 
	int menu_img[8];  // メニュー画像
	int se[2];
	int bgm;

public:
	static int menu_cursor;  // カーソルがどこにあるか 

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};