#pragma once
#include "chessboard.h"
#include "evaluate.h"
int alphaBeta(int player, int alpha, int beta, int depth, int turn, int val);
int to_move_x; //��һ������λ�õ�x����
int to_move_y; //��һ������λ�õ�y����
int search_depth = 5; //�㷨����Ϊ5��
/////////////////////////////////////////////////////////////////////////
pair<int, int> searchMove(int player) //�㷨������������
{	alphaBeta(player, INT_MIN, INT_MAX, search_depth, player, 0); //ִ��alpha-beta��֦�㷨
	return make_pair(to_move_x, to_move_y); //������һ��������λ��
}
int alphaBeta(int player, int alpha, int beta, int depth, int turn, int val) 
{	// turn:0 MAX ָ��Ҳ� 1 MINָAI��
	//alpha��ʼֵΪ����С��beta��ʼֵΪ�����
	int score = 0;
	int max_i = 0;
	int max_j = 0;
	if (turn == player)
	{	int* moves_x = new int[20];
		int* moves_y = new int[20];
		int* values = new int[20];
		int N = INT_MIN;//alpha<= N <=beta,N��ʼֵΪ����С
		int len = createMoves(moves_x, moves_y, values, turn);//ʹ���ŷ����������ɺϷ����ǰ20��
		for (int k = 0; k < len; k++) 
		{	int i = moves_x[k];
			int j = moves_y[k];
			if (depth > 1) //��δ�ݹ鵽��ײ���ݹ����
			{	makeMove(i, j, turn); //���Ӳ������ֵ
				score = alphaBeta(player, alpha, beta, depth - 1, 1 - turn, val + values[k]);
				unMakeMove(i, j); //�ݹ�����󳷻����ӷ����������
			} else score = val; //����ײ���̳е�ǰ��ֵ
			if (score > N) //��¼����ֵʱ������λ��
			{	N = score;
				if (depth == search_depth) 
				{	to_move_x = i;
					to_move_y = j;
				}
			}
			if (score > alpha) //alphaѡȡ��Сֵ
				alpha = score;
			if (alpha >= beta) //��alphaֵ����betaֵʱ���м�֦���������ؼ���
			{	delete[] moves_x;
				delete[] moves_y;
				delete[] values;
				return alpha;
			}
		}
		delete[] moves_x; //ȫ������֮�󷵻�alphaֵ
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
			if (score < beta) //betaѡȡ���ֵ
				beta = score;
			if (alpha >= beta) //��alphaֵ����betaֵʱ���м�֦���������ؼ���
			{	delete[] moves_x;
				delete[] moves_y;
				delete[] values;
				return beta;
			}
		}
		delete[] moves_x; //ȫ������֮�󷵻�betaֵ
		delete[] moves_y;
		delete[] values;
		return beta;
	}
}
/////////////////////////////////////////////////////////////////////////