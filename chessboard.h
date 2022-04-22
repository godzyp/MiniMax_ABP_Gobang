#pragma once
#include <string.h>
#include <string>
#include <stack>
using namespace std;
#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方	
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)//检验棋子是否在棋盘上 若存在则返回1，否则返回0
int chessBoard[16][16];//定义棋盘 规模为16*16
stack<pair<int, int>> steps;//存储双方一共走了多少步棋
/////////////////////////////////////////////////////////////////////////
bool inBound(int x, int y)//判断周围是否有棋子 若有则返回1，否则返回0
{	for (int i = -2; i <= 2; i++) 
	{	for (int j = -2; j <= 2; j++) 
		{	if (i == 0 && j == 0) 
				continue;
			if (chessBoard[x + i][y + j] != 0)
				return true;
		}
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////
bool makeMove(int x, int y, int player)//执行落子操作
{	if (inboard(x, y))//位置在棋盘中且为空
	{	if (chessBoard[x][y])
			return false;
		chessBoard[x][y] = player;
		steps.push(make_pair(x, y));//每走一步入栈计数
		return true;
	}
	return false;
}
bool unMakeMove(int x, int y)//撤销落子操作
{	if (!chessBoard[x][y])
		return false;
	chessBoard[x][y] = 0;//将棋盘落子位置置空
	steps.pop();//每撤销一步出栈计数
	return true;
}
/////////////////////////////////////////////////////////////////////////
void print() //棋盘打印
{	for (int i = 0; i < 16; i++)
	{	if (i == 0)//棋盘列
		{	printf("  ");
			for (int j = 1; j < 16; j++)
				printf("%-2d", j);
			printf("\n");
			continue;
		}
		for (int j = 0; j < 16; j++)
		{	if (j == 0)//棋盘行
			{	printf("%2d", i);
				continue;
			}
			if (chessBoard[i][j] == 1) //玩家执黑子
				printf("○");
			else if (chessBoard[i][j] == 2) //电脑执白子
				printf("●");
			else//棋盘边框和布局
			{	if (i == 1 && j == 1)
					printf("╔ ");
				else if (i == 1 && j == 15)
					printf("╗");
				else if (i == 15 && j == 1)
					printf("╚ ");
				else if (i == 15 && j == 15)
					printf("╝");
				else if (i == 1 && j != 15 && j != 1)
					printf("┯ ");
				else if (i == 15 && j != 15 && j != 1)
					printf("┷ ");
				else if (j == 1 && i != 15 && i != 1)
					printf("┠ ");
				else if (j == 15 && i != 15 && i != 1)
					printf("┨");
				else
					printf("┼ ");
			}
		}
		printf("\n");
	}
}
/////////////////////////////////////////////////////////////////////////
bool checkHorizontal(int x_, int y_, int player)//检查棋盘水平方向是否5连子 有则返回1，否则返回0
{	int count = 1;
	int x = x_;
	int y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x - 1, y) && chessBoard[x - 1][y] == player)
		{
			count += 1;
			x--;
		}
		else
		{
			break;
		}
	}
	x = x_;
	y = y_;
	for (int i = 1; i < 5; i++)
	{
		if (inboard(x + 1, y) && chessBoard[x + 1][y] == player)
		{
			count += 1;
			x++;
		}
		else
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	return false;
}
bool checkVertical(int x_, int y_, int player)//检查棋盘垂直方向是否5连子 有则返回1，否则返回0
{
	int count = 1;
	int x = x_;
	int y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x, y - 1) && chessBoard[x][y - 1] == player)
		{	count += 1;
			y--;
		} else break;
	}
	x = x_;
	y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x, y + 1) && chessBoard[x][y + 1] == player)
		{	count += 1;
			y++;
		} else break;
	}
	if (count >= 5)//有5个以上连着的棋子
		return true;
	return false;
}
bool checkDiagonal(int x_, int y_, int player)//检查棋盘对角方向是否5连子 有则返回1，否则返回0
{	int count = 1;
	int x = x_;
	int y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x - 1, y - 1) && chessBoard[x - 1][y - 1] == player)//左上
		{	count += 1;
			x--;
			y--;
		} else break;
	}
	x = x_;
	y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x + 1, y + 1) && chessBoard[x + 1][y + 1] == player)//右下
		{	count += 1;
			x++;
			y++;
		} else break;
	}
	if (count >= 5)//有5个以上连着的棋子
		return true;
	x = x_;
	y = y_;
	count = 1;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x - 1, y + 1) && chessBoard[x - 1][y + 1] == player)//右上
		{	count += 1;
			x--;
			y++;
		} else break;
	}
	x = x_;
	y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x + 1, y - 1) && chessBoard[x + 1][y - 1] == player)//左下
		{	count += 1;
			x++;
			y--;
		} else break;
	}
	if (count >= 5)//有5个以上连着的棋子
		return true;
	return false;
}
bool gameover(int x, int y, int player)//判断是否游戏结束
{	return checkHorizontal(x, y, player) || checkVertical(x, y, player) || checkDiagonal(x, y, player);
}
/////////////////////////////////////////////////////////////////////////