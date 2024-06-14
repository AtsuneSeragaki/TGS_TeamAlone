#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class InputRankingScene : public SceneBase
{
private:
	int back_img;    // 背景画像 
	int img[7];
	RankingData* ranking; // ランキング情報
	int level;
	int combo;
	char name[10];
	int name_num;
	int cursor_x;
	int cursor_y;
	bool no_name;
	int font;
	int se[3];
	int bgm;

public:
	InputRankingScene();
	virtual ~InputRankingScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// 名前入力処理
	bool InputName();
};