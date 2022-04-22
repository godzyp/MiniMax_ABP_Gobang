#pragma once
#include "chessboard.h"
#include <algorithm>
/////////////////////////////////////////////////////////////////////////
int getLine(int x, int y, int i, int j)//获取棋子位置
{	// i:方向 j:相对x,y的顺序值（以x,y为0） x,y:当前点
	switch (i) 
	{	case 1://当前棋子 下 方向
			x = x + j;
			break;
		case 2://当前棋子 右下 方向
			x = x + j;
			y = y + j;
			break;
		case 3://当前棋子 右 方向
			y = y + j;
			break;
		case 4://当前棋子 右上 方向
			x = x - j;
			y = y + j;
			break;
		case 5://当前棋子 上 方向
			x = x - j;
			break;
		case 6://当前棋子 左上 方向
			x = x - j;
			y = y - j;
			break;
		case 7://当前棋子 左 方向
			y = y - j;
			break;
		case 8://当前棋子 左下 方向
			x = x + j;
			y = y - j;
	}
	if (!inboard(x, y)) //如果超出棋盘返回-1
		return -1;
	return chessBoard[x][y];//返回当前位置的棋盘是否有棋子 若有则为1，否则为0
}
/////////////////////////////////////////////////////////////////////////
int evaluate_one(int x, int y, int me, int player)//估值算法，返回落子估值
{	int value = 0;//总分值
	int numoftwo = 0;//二子个数
	for (int i = 1; i <= 8; i++) // 8个方向依次寻找棋子招式进行评分
	{	//*代表当前空位置  0代表其他空位置
		// 活四 01111* 分值300000 
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, -4) == player
			&& getLine(x, y, i, -5) == 0) 
		{	value += 300000;
			if (me != player)//若为玩家则-500
				value -= 500; 
			continue;
		}
		// 死四A 21111* 分值250000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, -4) == player
			&& (getLine(x, y, i, -5) == 3 - player || getLine(x, y, i, -5) == -1)) 
		{	value += 250000;
			if (me != player) //若为玩家则-500
				value -= 500;
			continue;
		}
		// 死四B 111*1 分值200000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, 1) == player) 
		{	value += 200000;
			if (me != player)//若为玩家则-500
				value -= 500;
			continue;
		}
		// 死四C 11*11 分值200000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, 1) == player && getLine(x, y, i, 2) == player) 
		{	value += 200000;
			if (me != player)//若为玩家则-500
				value -= 500;
			continue;
		}
		// 活三 近3位置 111*0 分值1000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player) 
		{	if (getLine(x, y, i, 1) == 0) 
			{	value += 1000;
				if (getLine(x, y, i, -4) == 0) //跳活三分值4000
				{	value += 4000;
					if (me != player)//若为玩家则-500
						value -= 500;
				}
			}
			continue;
		}
		// 活三 远3位置 1110* 分值500
		if (getLine(x, y, i, -1) == 0 && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, -4) == player) 
		{	value += 500;
			continue;
		}
		// 死三 11*1 三种情况分别对应分值500 1000 4000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, 1) == player)
		{	value += 500;
			if (getLine(x, y, i, -3) == 0 && getLine(x, y, i, 2) == 0) 
			{	value += 4000;
				continue;
			}
			if ((getLine(x, y, i, -3) == 3 - player || getLine(x, y, i, -3) == -1) 
				&& (getLine(x, y, i, 2) == 3 - player || getLine(x, y, i, 2) == -1)) 
			{ continue;
			} else {
				value += 1000;
				continue;
			}
		}
		//活二的个数 
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) != 3 - player && getLine(x, y, i, 1) != 3 - player)
		{	numoftwo++;
		}
		//其余散棋(单个棋子) 每个棋子分值5
		int numOfplayer = 0;
		for (int k = -4; k <= 0; k++) 
		{	int temp = 0;
			for (int l = 0; l <= 4; l++) 
			{	if (getLine(x, y, i, k + l) == player) 
					temp++;
				else
					if (getLine(x, y, i, k + l) == 3 - player
						|| getLine(x, y, i, k + l) == -1) 
					{	temp = 0;
						break;
					}
			}
			numOfplayer += temp;
		}
		value += numOfplayer * 5;
	}
	if (numoftwo >= 2)// 超过两个活二分值3000
	{	value += 3000;
		if (me != player)
			value -= 500;//若为玩家则-500
	}
	return value;
}
int evaluate(int x, int y, int player)//返回黑子和白子的总价值评估
{	return evaluate_one(x, y, player, black) + evaluate_one(x, y, player, white);
}
/////////////////////////////////////////////////////////////////////////
int tmp_values[15 * 15];
bool cmp(int a, int b)//sort降序排列
{
	return tmp_values[a] > tmp_values[b];
}
int createMoves(int* moves_x, int* moves_y, int* values, int player) //着法生成器
{	//计算所有棋盘空位置的分值评估结果，并降序排序存入moves和values中
	int tmp_moves_x[15 * 15];
	int tmp_moves_y[15 * 15];
	int idx[15 * 15];
	int len = 0;
	for (int i = 1; i < 16; i++) 
	{	for (int j = 1; j < 16; j++) 
		{	if (!inboard(i, j) || !inBound(i, j) || chessBoard[i][j])//超出棋盘边界或已经有棋子则跳过
				continue;
			tmp_moves_x[len] = i;
			tmp_moves_y[len] = j;
			tmp_values[len] = evaluate(i, j, player);//对每一步棋进行价值评估
			idx[len] = len;
			len++;
		}
	}
	sort(idx, idx + len, cmp);//降序排列
	if (len > 20)//缩小范围到20步内的合法走法
		len = 20;
	for (int i = 0; i < len; i++) //将合法走法存入走法集
	{	moves_x[i] = tmp_moves_x[idx[i]];
		moves_y[i] = tmp_moves_y[idx[i]];
		values[i] = tmp_values[idx[i]];
	}
	return len;//返回合法走法集的长度
}
/////////////////////////////////////////////////////////////////////////