#pragma once

#include "SceneBase.h"

class RankingScene : public SceneBase
{
private:
	int back_img;    // 背景画像 

public:
	RankingScene();
	virtual ~RankingScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};