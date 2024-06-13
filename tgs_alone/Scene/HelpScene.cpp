#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
#include "DxLib.h"

HelpScene::HelpScene():cnt(0),anim(0),cnt_flg(false)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			button_img[i][j] = 0;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		back_img[i] = 0;
	}
}

HelpScene::~HelpScene()
{
}

void HelpScene::Initialize()
{
	back_img[0] = LoadGraph("Resource/images/help/help.png");
	back_img[1] = LoadGraph("Resource/images/help/help1.png");
	back_img[2] = LoadGraph("Resource/images/help/helpm.png");
	back_img[3] = LoadGraph("Resource/images/help/star2.png");
	back_img[4] = LoadGraph("Resource/images/help/line.png");
	back_img[5] = LoadGraph("Resource/images/help/ui.png");

	button_img[0][0] = LoadGraph("Resource/images/main/button/Abotton0.png");
	button_img[0][1] = LoadGraph("Resource/images/main/button/Abotton5.png");
	button_img[0][2] = LoadGraph("Resource/images/main/button/Abotton6.png");
	button_img[0][3] = LoadGraph("Resource/images/main/button/Abotton7.png");
	button_img[0][4] = LoadGraph("Resource/images/main/button/Abotton8.png");
	button_img[0][5] = LoadGraph("Resource/images/main/button/Abotton.png");

	button_img[1][0] = LoadGraph("Resource/images/main/button/Bbotton0.png");
	button_img[1][1] = LoadGraph("Resource/images/main/button/Bbotton5.png");
	button_img[1][2] = LoadGraph("Resource/images/main/button/Bbotton6.png");
	button_img[1][3] = LoadGraph("Resource/images/main/button/Bbotton7.png");
	button_img[1][4] = LoadGraph("Resource/images/main/button/Bbotton8.png");
	button_img[1][5] = LoadGraph("Resource/images/main/button/Bbotton.png");

	button_img[2][0] = LoadGraph("Resource/images/main/button/Ybotton0.png");
	button_img[2][1] = LoadGraph("Resource/images/main/button/Ybotton5.png");
	button_img[2][2] = LoadGraph("Resource/images/main/button/Ybotton6.png");
	button_img[2][3] = LoadGraph("Resource/images/main/button/Ybotton7.png");
	button_img[2][4] = LoadGraph("Resource/images/main/button/Ybotton8.png");
	button_img[2][5] = LoadGraph("Resource/images/main/button/Ybotton.png");

	button_img[3][0] = LoadGraph("Resource/images/main/button/Xbotton0.png");
	button_img[3][1] = LoadGraph("Resource/images/main/button/Xbotton5.png");
	button_img[3][2] = LoadGraph("Resource/images/main/button/Xbotton6.png");
	button_img[3][3] = LoadGraph("Resource/images/main/button/Xbotton7.png");
	button_img[3][4] = LoadGraph("Resource/images/main/button/Xbotton8.png");
	button_img[3][5] = LoadGraph("Resource/images/main/button/Xbotton.png");

	cnt = 0;
	cnt_flg = false;
	anim = 1;
}

eSceneType HelpScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		TitleScene::menu_cursor = 0;
		return eSceneType::E_MAIN;
	}

	if (cnt_flg == true)
	{
		cnt++;

		if (cnt > 140)
		{
			cnt = 0;
			anim++;
			cnt_flg = false;
		}
	}
	else if (anim > 0)
	{
		anim++;

		if (anim > 100)
		{
			anim = 0;
			cnt_flg = true;
		}
	}

	return GetNowScene();
}

void HelpScene::Draw() const
{
	DrawGraph(0, 0, back_img[0], TRUE);

	DrawGraph(0, 0, back_img[3], TRUE);
	DrawGraph(0, 0, back_img[4], TRUE);

	DrawGraph(0, 0, back_img[1], TRUE);
	DrawGraph(0, 0, back_img[2], TRUE);
	DrawGraph(0, 0, back_img[5], TRUE);

	


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	for (int i = 0; i < 4; i++)
	{
		DrawGraph(430 + i * 120, 350, button_img[i][5], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (anim >= 1 && anim < 3)
	{
		DrawGraph(430 - 4 * 28, 350 - 4 * 23, button_img[0][4], TRUE);
	}
	else if (anim >= 3 && anim < 5)
	{
		DrawGraph(430 - 3 * 28, 350 - 3 * 23, button_img[0][3], TRUE);
	}
	else if (anim >= 5 && anim < 7)
	{
		DrawGraph(430 - 2 * 28, 350 - 2 * 23, button_img[0][2], TRUE);
	}
	else if (anim >= 7 && anim < 9)
	{
		DrawGraph(430 - 28, 350 - 23, button_img[0][1], TRUE);
	}
	else if (anim >= 9 && anim < 15)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
	}
	else if(anim >= 15 && anim < 17)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph((430 - 4 * 28) + 120, 350 - 4 * 23, button_img[1][4], TRUE);
	}
	else if (anim >= 17 && anim < 19)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph((430 - 3 * 28) + 120, 350 - 3 * 23, button_img[1][3], TRUE);
	}
	else if (anim >= 19 && anim < 21)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph((430 - 2 * 28) + 120, 350 - 2 * 23, button_img[1][2], TRUE);
	}
	else if (anim >= 21 && anim < 23)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph((430 - 28) + 120, 350 - 23, button_img[1][1], TRUE);
	}
	else if (anim >= 23 && anim < 29)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
	}
	else if (anim >= 29 && anim < 31)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph((430 - 4 * 28) + 240, 350 - 4 * 23, button_img[2][4], TRUE);
	}
	else if (anim >= 31 && anim < 33)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph((430 - 3 * 28) + 240, 350 - 3 * 23, button_img[2][3], TRUE);
	}
	else if (anim >= 33 && anim < 35)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph((430 - 2 * 28) + 240, 350 - 2 * 23, button_img[2][2], TRUE);
	}
	else if (anim >= 35 && anim < 37)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph((430 - 28) + 240, 350 - 23, button_img[2][1], TRUE);
	}
	else if (anim >= 37 && anim < 43)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph(430 + 240, 350, button_img[2][0], TRUE);
	}
	else if (anim >= 43 && anim < 45)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph(430 + 240, 350, button_img[2][0], TRUE);
		DrawGraph((430 - 4 * 28) + 360, 350 - 4 * 23, button_img[3][4], TRUE);
	}
	else if (anim >= 45 && anim < 47)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph(430 + 240, 350, button_img[2][0], TRUE);
		DrawGraph((430 - 3 * 28) + 360, 350 - 3 * 23, button_img[3][3], TRUE);
	}
	else if (anim >= 47 && anim < 49)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph(430 + 240, 350, button_img[2][0], TRUE);
		DrawGraph((430 - 2 * 28) + 360, 350 - 2 * 23, button_img[3][2], TRUE);
	}
	else if (anim >= 49 && anim < 51)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph(430 + 240, 350, button_img[2][0], TRUE);
		DrawGraph((430 - 28) + 360, 350 - 23, button_img[3][1], TRUE);
	}
	else if (anim >= 51 && anim < 100)
	{
		DrawGraph(430, 350, button_img[0][0], TRUE);
		DrawGraph(430 + 120, 350, button_img[1][0], TRUE);
		DrawGraph(430 + 240, 350, button_img[2][0], TRUE);
		DrawGraph(430 + 360, 350, button_img[3][0], TRUE);
	}

}

void HelpScene::Finalize()
{
	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(back_img[i]);
	}


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			DeleteGraph(button_img[i][j]);
		}
	}
}

eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}