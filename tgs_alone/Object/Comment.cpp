#include "Comment.h"
#include "Player.h"
#include "Theme.h"
#include "DxLib.h"

Comment::Comment():disp_flg(false),com_num(0),p_num(0),t_num(0),cnt(0),font(0),font2(0),char_cnt(0)
{
	for (int i = 0; i < 7; i++)
	{
		char_img[i] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		com_img[i] = 0;
	}
}

Comment::~Comment()
{
}

void Comment::Initialize()
{
	char_img[0] = LoadGraph("Resource/images/main/comment/char1.png");
	char_img[1] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[2] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[3] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[4] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[5] = LoadGraph("Resource/images/main/comment/char6.png");
	char_img[6] = LoadGraph("Resource/images/main/comment/char7.png");
	
	com_img[0] = LoadGraph("Resource/images/main/comment/comment1.png");
	com_img[1] = LoadGraph("Resource/images/main/comment/comment2.png");
	com_img[2] = LoadGraph("Resource/images/main/comment/comment3.png");
	com_img[3] = LoadGraph("Resource/images/main/comment/comment4.png");
	com_img[4] = LoadGraph("Resource/images/main/comment/comment5.png");

	font = CreateFontToHandle("Segoe UI", 40, 7, DX_FONTTYPE_ANTIALIASING);
	font2 = CreateFontToHandle("Segoe UI", 30, 7, DX_FONTTYPE_ANTIALIASING);

	disp_flg = 0;
	t_num = 0;
	p_num = 0;
	cnt = 0;
	com_num = -1;
	char_cnt = 0;
}

void Comment::Update()
{
	char_cnt++;
	
	if (char_cnt > 300)
	{
		char_cnt = 0;
	}
	
	if (disp_flg == true)
	{
		cnt++;

		if (cnt > 60)
		{
			cnt = 0;
			disp_flg = false;
		}
	}
}

void Comment::Draw()
{
	SetFontSize(40);

	// DrawFormatString(600, 245, 0xff0000, "%d", p_num);

	//DrawGraph(46, 530, img[6], TRUE);

	
	
	//if (char_cnt < 21)
	//{
	//	DrawGraph(46, 530, char_img[1], TRUE);
	//}
	//else if (char_cnt < 41)
	//{
	//	DrawGraph(37, 535, char_img[2], TRUE);
	//}
	//else if (char_cnt < 61)
	//{
	//	DrawGraph(15, 530, char_img[3], TRUE);
	//}
	//else if (char_cnt < 81)
	//{
	//	DrawGraph(0, 545, char_img[4], TRUE);
	//}
	//else if (char_cnt < 101)
	//{
	//	DrawGraph(-25, 575, char_img[5], TRUE);
	//}
	//else if (char_cnt < 121)
	//{
	//	DrawGraph(-35, 590, char_img[6], TRUE);
	//}
	//else if (char_cnt < 141)
	//{
	//	DrawGraph(-25, 575, char_img[5], TRUE);
	//}
	//else if (char_cnt < 161)
	//{
	//	DrawGraph(0, 545, char_img[4], TRUE);
	//}
	//else if (char_cnt < 181)
	//{
	//	DrawGraph(15, 530, char_img[3], TRUE);
	//}
	//else if (char_cnt < 201)
	//{
	//	DrawGraph(37, 535, char_img[2], TRUE);
	//}
	//else if (char_cnt < 221)
	//{
	//	DrawGraph(46, 530, char_img[1], TRUE);
	//}
	//else
	//{
	//	DrawGraph(46, 530, char_img[1], TRUE);
	//}

	DrawGraph(55, 570, char_img[0], TRUE);
	

	if (disp_flg == true)
	{
		switch (com_num)
		{
		case 0:
			DrawGraph(30, 520, com_img[3], TRUE);
			DrawStringToHandle(85, 540, "Genius!", 0x000000,font);
			break;

		case 1:
			DrawGraph(30, 520, com_img[0], TRUE);
			DrawStringToHandle(65, 540, "Excellent!", 0x000000, font);
			break;

		case 2:
			DrawGraph(30, 520, com_img[2], TRUE);
			DrawStringToHandle(100, 540, "Great!", 0x000000, font);
			break;

		case 3:
			DrawGraph(30, 520, com_img[1], TRUE);
			DrawStringToHandle(115, 542, "Nice!", 0x000000, font);
			break;

		case 4:
			DrawGraph(30, 520, com_img[4], TRUE);
			DrawStringToHandle(60, 545, "You can do it!", 0x000000, font2);
			break;
			
		default:
			break;
		}
	}
}

void Comment::Finalize()
{
	DeleteFontToHandle(font);
	DeleteFontToHandle(font2);

}

void Comment::SetComNum()
{
	switch (t_num)
	{
	case 3:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 3)
		{
			com_num = 2;
		}
		else
		{
			com_num = 4;
		}

	case 4:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 3)
		{
			com_num = 2;
		}
		else
		{
			com_num = 4;
		}

	case 5:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 2)
		{
			com_num = 2;
		}
		else if (p_num < 5)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 6:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 6)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 7:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 7)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 8:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 6)
		{
			com_num = 2;
		}
		else if (p_num < 8)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 9:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 7)
		{
			com_num = 2;
		}
		else if (p_num < 9)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 10:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 5)
		{
			com_num = 1;
		}
		else if (p_num < 8)
		{
			com_num = 2;
		}
		else if (p_num < 10)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 11:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 4)
		{
			com_num = 1;
		}
		else if (p_num < 9)
		{
			com_num = 2;
		}
		else if (p_num < 11)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 12:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 6)
		{
			com_num = 2;
		}
		else if (p_num < 12)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 13:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 6)
		{
			com_num = 2;
		}
		else if (p_num < 12)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 14:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 14)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 15:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 15)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 16:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 16)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 17:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 17)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 18:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 2)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 18)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 19:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 2)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 19)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 20:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 2)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 20)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	default:
		break;
	}
	
}