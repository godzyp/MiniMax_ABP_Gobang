#pragma once
#include "chessboard.h"
#include <algorithm>
/////////////////////////////////////////////////////////////////////////
int getLine(int x, int y, int i, int j)//��ȡ����λ��
{	// i:���� j:���x,y��˳��ֵ����x,yΪ0�� x,y:��ǰ��
	switch (i) 
	{	case 1://��ǰ���� �� ����
			x = x + j;
			break;
		case 2://��ǰ���� ���� ����
			x = x + j;
			y = y + j;
			break;
		case 3://��ǰ���� �� ����
			y = y + j;
			break;
		case 4://��ǰ���� ���� ����
			x = x - j;
			y = y + j;
			break;
		case 5://��ǰ���� �� ����
			x = x - j;
			break;
		case 6://��ǰ���� ���� ����
			x = x - j;
			y = y - j;
			break;
		case 7://��ǰ���� �� ����
			y = y - j;
			break;
		case 8://��ǰ���� ���� ����
			x = x + j;
			y = y - j;
	}
	if (!inboard(x, y)) //����������̷���-1
		return -1;
	return chessBoard[x][y];//���ص�ǰλ�õ������Ƿ������� ������Ϊ1������Ϊ0
}
/////////////////////////////////////////////////////////////////////////
int evaluate_one(int x, int y, int me, int player)//��ֵ�㷨���������ӹ�ֵ
{	int value = 0;//�ܷ�ֵ
	int numoftwo = 0;//���Ӹ���
	for (int i = 1; i <= 8; i++) // 8����������Ѱ��������ʽ��������
	{	//*����ǰ��λ��  0����������λ��
		// ���� 01111* ��ֵ300000 
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, -4) == player
			&& getLine(x, y, i, -5) == 0) 
		{	value += 300000;
			if (me != player)//��Ϊ�����-500
				value -= 500; 
			continue;
		}
		// ����A 21111* ��ֵ250000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, -4) == player
			&& (getLine(x, y, i, -5) == 3 - player || getLine(x, y, i, -5) == -1)) 
		{	value += 250000;
			if (me != player) //��Ϊ�����-500
				value -= 500;
			continue;
		}
		// ����B 111*1 ��ֵ200000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, 1) == player) 
		{	value += 200000;
			if (me != player)//��Ϊ�����-500
				value -= 500;
			continue;
		}
		// ����C 11*11 ��ֵ200000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, 1) == player && getLine(x, y, i, 2) == player) 
		{	value += 200000;
			if (me != player)//��Ϊ�����-500
				value -= 500;
			continue;
		}
		// ���� ��3λ�� 111*0 ��ֵ1000
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player) 
		{	if (getLine(x, y, i, 1) == 0) 
			{	value += 1000;
				if (getLine(x, y, i, -4) == 0) //��������ֵ4000
				{	value += 4000;
					if (me != player)//��Ϊ�����-500
						value -= 500;
				}
			}
			continue;
		}
		// ���� Զ3λ�� 1110* ��ֵ500
		if (getLine(x, y, i, -1) == 0 && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) == player && getLine(x, y, i, -4) == player) 
		{	value += 500;
			continue;
		}
		// ���� 11*1 ��������ֱ��Ӧ��ֵ500 1000 4000
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
		//����ĸ��� 
		if (getLine(x, y, i, -1) == player && getLine(x, y, i, -2) == player
			&& getLine(x, y, i, -3) != 3 - player && getLine(x, y, i, 1) != 3 - player)
		{	numoftwo++;
		}
		//����ɢ��(��������) ÿ�����ӷ�ֵ5
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
	if (numoftwo >= 2)// �������������ֵ3000
	{	value += 3000;
		if (me != player)
			value -= 500;//��Ϊ�����-500
	}
	return value;
}
int evaluate(int x, int y, int player)//���غ��ӺͰ��ӵ��ܼ�ֵ����
{	return evaluate_one(x, y, player, black) + evaluate_one(x, y, player, white);
}
/////////////////////////////////////////////////////////////////////////
int tmp_values[15 * 15];
bool cmp(int a, int b)//sort��������
{
	return tmp_values[a] > tmp_values[b];
}
int createMoves(int* moves_x, int* moves_y, int* values, int player) //�ŷ�������
{	//�����������̿�λ�õķ�ֵ����������������������moves��values��
	int tmp_moves_x[15 * 15];
	int tmp_moves_y[15 * 15];
	int idx[15 * 15];
	int len = 0;
	for (int i = 1; i < 16; i++) 
	{	for (int j = 1; j < 16; j++) 
		{	if (!inboard(i, j) || !inBound(i, j) || chessBoard[i][j])//�������̱߽���Ѿ�������������
				continue;
			tmp_moves_x[len] = i;
			tmp_moves_y[len] = j;
			tmp_values[len] = evaluate(i, j, player);//��ÿһ������м�ֵ����
			idx[len] = len;
			len++;
		}
	}
	sort(idx, idx + len, cmp);//��������
	if (len > 20)//��С��Χ��20���ڵĺϷ��߷�
		len = 20;
	for (int i = 0; i < len; i++) //���Ϸ��߷������߷���
	{	moves_x[i] = tmp_moves_x[idx[i]];
		moves_y[i] = tmp_moves_y[idx[i]];
		values[i] = tmp_values[idx[i]];
	}
	return len;//���غϷ��߷����ĳ���
}
/////////////////////////////////////////////////////////////////////////