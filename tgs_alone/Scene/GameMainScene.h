#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"

class GameMainScene : public SceneBase
{
private:
	int back_img;    // ”wŒi‰æ‘œ 

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};