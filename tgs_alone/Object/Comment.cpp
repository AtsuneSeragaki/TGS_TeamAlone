#include "Comment.h"
#include "Player.h"
#include "Theme.h"
#include "DxLib.h"

Comment::Comment():disp_flg(false),com_num(0),p_num(0),t_num(0)
{
}

Comment::~Comment()
{
}

void Comment::Initialize()
{
}

void Comment::Update()
{
	if (disp_flg == true)
	{
		SetComNum();
	}
}

void Comment::Draw()
{
	SetFontSize(30);
}

void Comment::Finalize()
{
}

void Comment::SetComNum()
{
	if (t_num < 4)
	{

	}
	if (t_num < 5)
	{
		if (p_num == t_num)
		{
			com_num = 4;
		}
		else if (p_num == t_num - 2)
		{
			com_num = 3;
		}
	}
	if (t_num < 6)
	{
		if (p_num == t_num)
		{
			com_num = 4;
		}
		else if (p_num == t_num - 2)
		{
			com_num = 3;
		}
	}
}