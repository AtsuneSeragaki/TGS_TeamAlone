#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"

#define THEME_MAX 15

class GameMainScene : public SceneBase
{
private:
	int back_img;     // �w�i�摜
	int theme_img[4]; // ����摜
	int bgm;
	int se;
	float time;       // ��������
	int time_cnt;     // 1�b���炷�^�C�~���O���J�E���g
	int theme[THEME_MAX];  // ���� 
	bool theme_flg;   // ������o�����o���Ȃ����t���O
	int theme_num;    // ����̐�
	Player player;

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void SetTheme(void);  // �����ݒ肷��
};