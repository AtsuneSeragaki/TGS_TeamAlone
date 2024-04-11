#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Time.h"
#include "../Object/Theme.h"

class GameMainScene : public SceneBase
{
private:
	int back_img;     // ”wŒi‰æ‘œ
	int bgm;
	int se;
	Player* player;   // ƒvƒŒƒCƒ„[
	Time* time;       // §ŒÀŠÔ
	Theme* theme;     // ‚¨‘è

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};