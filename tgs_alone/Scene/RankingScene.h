#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingScene : public SceneBase
{
private:
	int back_img;    // 背景画像 
	RankingData* ranking;
	int font;
	int se[2];
	int bgm;

public:
	RankingScene();
	virtual ~RankingScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};