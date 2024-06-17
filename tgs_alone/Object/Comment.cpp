#include "Comment.h"
#include "Player.h"
#include "Theme.h"
#include "DxLib.h"

Comment::Comment():disp_flg(false),com_num(0),p_num(0),t_num(0),cnt(0)
{
}

Comment::~Comment()
{
}

void Comment::Initialize()
{
	disp_flg = 0;
	t_num = 0;
	p_num = 0;
	cnt = 0;
	com_num = -1;
}

void Comment::Update()
{
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

	DrawFormatString(600, 245, 0xff0000, "%d", p_num);

	if (disp_flg == true)
	{
		switch (com_num)
		{
		case 0:
			DrawString(400, 245, "Genius!", 0x000000);
			break;

		case 1:
			DrawString(400, 245, "Excellent!", 0x000000);
			break;

		case 2:
			DrawString(400, 245, "Great!", 0x000000);
			break;

		case 3:
			DrawString(400, 245, "Nice!", 0x000000);
			break;

		case 4:
			DrawString(400, 245, "You can do it!", 0x000000);
			break;
			
		default:
			break;
		}
	}
}

void Comment::Finalize()
{
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