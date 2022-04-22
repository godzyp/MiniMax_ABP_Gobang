#pragma once
#include "chessboard.h"
#include "evaluate.h"
int alphaBeta(int player, int alpha, int beta, int depth, int turn, int val);
int to_move_x; //下一步落子位置的x坐标
int to_move_y; //下一步落子位置的y坐标
int search_depth = 5; //算法层数为5层
/////////////////////////////////////////////////////////////////////////
pair<int, int> searchMove(int player) //算法搜索函数主体
{	alphaBeta(player, INT_MIN, INT_MAX, search_depth, player, 0); //执行alpha-beta剪枝算法
	return make_pair(to_move_x, to_move_y); //返回下一步的落子位置
}
int alphaBeta(int player, int alpha, int beta, int depth, int turn, int val) 
{	// turn:0 MAX 指玩家层 1 MIN指AI层
	//alpha初始值为无穷小；beta初始值为无穷大
	int score = 0;
	int max_i = 0;
	int max_j = 0;
	if (turn == player)
	{	int* moves_x = new int[20];
		int* moves_y = new int[20];
		int* values = new int[20];
		int N = INT_MIN;//alpha<= N <=beta,N初始值为无穷小
		int len = createMoves(moves_x, moves_y, values, turn);//使用着法生成器生成合法最佳前20步
		for (int k = 0; k < len; k++) 
		{	int i = moves_x[k];
			int j = moves_y[k];
			if (depth > 1) //若未递归到最底层则递归计算
			{	makeMove(i, j, turn); //落子并计算分值
				score = alphaBeta(player, alpha, beta, depth - 1, 1 - turn, val + values[k]);
				unMakeMove(i, j); //递归结束后撤回落子方便后续遍历
			} else score = val; //到最底层则继承当前分值
			if (score > N) //记录最大分值时的落子位置
			{	N = score;
				if (depth == search_depth) 
				{	to_move_x = i;
					to_move_y = j;
				}
			}
			if (score > alpha) //alpha选取最小值
				alpha = score;
			if (alpha >= beta) //若alpha值大于beta值时进行剪枝，后续不必计算
			{	delete[] moves_x;
				delete[] moves_y;
				delete[] values;
				return alpha;
			}
		}
		delete[] moves_x; //全部遍历之后返回alpha值
		delete[] moves_y;
		delete[] values;
		return alpha;
	} else {
		int* moves_x = new int[20];
		int* moves_y = new int[20];
		int* values = new int[20];
		int len = createMoves(moves_x, moves_y, values, turn);
		for (int k = 0; k < len; k++) 
		{	int i = moves_x[k];
			int j = moves_y[k];
			if (depth > 1) 
			{	makeMove(i, j, turn);
				score = alphaBeta(player, alpha, beta, depth - 1, 1 - turn, val - values[k]);
				unMakeMove(i, j);
			} else score = val;
			if (score < beta) //beta选取最大值
				beta = score;
			if (alpha >= beta) //若alpha值大于beta值时进行剪枝，后续不必计算
			{	delete[] moves_x;
				delete[] moves_y;
				delete[] values;
				return beta;
			}
		}
		delete[] moves_x; //全部遍历之后返回beta值
		delete[] moves_y;
		delete[] values;
		return beta;
	}
}
/////////////////////////////////////////////////////////////////////////