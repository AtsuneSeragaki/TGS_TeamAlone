﻿#pragma once

#include "SceneBase.h"

class InputRankingScene : public SceneBase
{
private:
	int back_img;    // 背景画像 

public:
	InputRankingScene();
	virtual ~InputRankingScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};