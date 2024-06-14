#pragma once

#include "SceneBase.h"

#define NUM_Y 405

class ResultScene : public SceneBase
{
private:
	int back_img[2];    // 背景画像 
	int num_img[10]; // 数字画像
	int rank_img[3];    // ランク画像
	int rank[3];
	char name[5][15];
	int level[5];
	int combo[5];
	int se;
	int bgm;

public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};