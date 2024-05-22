#pragma once

#include "SceneBase.h"

#define NUM_Y 405

class ResultScene : public SceneBase
{
private:
	int back_img;    // 背景画像 
	int num_img[10];

public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};