#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int back_img;     // 背景画像 
	int menu_img[8];  // メニュー画像
	int star_img;     // 星画像
	int se[2];        // 効果音
	int bgm;          // BGM
	int star_cnt;     // 星の描画時間用
	int star_blend;   // 星の透明度

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