#pragma once
#include <string.h>
#include <string>
#include <stack>
using namespace std;
#define blank 0		//�հ׵�
#define black 1		//�ڷ�
#define white 2		//�׷�	
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)//���������Ƿ��������� �������򷵻�1�����򷵻�0
int chessBoard[16][16];//�������� ��ģΪ16*16
stack<pair<int, int>> steps;//�洢˫��һ�����˶��ٲ���
/////////////////////////////////////////////////////////////////////////
bool inBound(int x, int y)//�ж���Χ�Ƿ������� �����򷵻�1�����򷵻�0
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
bool makeMove(int x, int y, int player)//ִ�����Ӳ���
{	if (inboard(x, y))//λ������������Ϊ��
	{	if (chessBoard[x][y])
			return false;
		chessBoard[x][y] = player;
		steps.push(make_pair(x, y));//ÿ��һ����ջ����
		return true;
	}
	return false;
}
bool unMakeMove(int x, int y)//�������Ӳ���
{	if (!chessBoard[x][y])
		return false;
	chessBoard[x][y] = 0;//����������λ���ÿ�
	steps.pop();//ÿ����һ����ջ����
	return true;
}
/////////////////////////////////////////////////////////////////////////
void print() //���̴�ӡ
{	for (int i = 0; i < 16; i++)
	{	if (i == 0)//������
		{	printf("  ");
			for (int j = 1; j < 16; j++)
				printf("%-2d", j);
			printf("\n");
			continue;
		}
		for (int j = 0; j < 16; j++)
		{	if (j == 0)//������
			{	printf("%2d", i);
				continue;
			}
			if (chessBoard[i][j] == 1) //���ִ����
				printf("��");
			else if (chessBoard[i][j] == 2) //����ִ����
				printf("��");
			else//���̱߿�Ͳ���
			{	if (i == 1 && j == 1)
					printf("�X ");
				else if (i == 1 && j == 15)
					printf("�[");
				else if (i == 15 && j == 1)
					printf("�^ ");
				else if (i == 15 && j == 15)
					printf("�a");
				else if (i == 1 && j != 15 && j != 1)
					printf("�� ");
				else if (i == 15 && j != 15 && j != 1)
					printf("�� ");
				else if (j == 1 && i != 15 && i != 1)
					printf("�� ");
				else if (j == 15 && i != 15 && i != 1)
					printf("��");
				else
					printf("�� ");
			}
		}
		printf("\n");
	}
}
/////////////////////////////////////////////////////////////////////////
bool checkHorizontal(int x_, int y_, int player)//�������ˮƽ�����Ƿ�5���� ���򷵻�1�����򷵻�0
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
bool checkVertical(int x_, int y_, int player)//������̴�ֱ�����Ƿ�5���� ���򷵻�1�����򷵻�0
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
	if (count >= 5)//��5���������ŵ�����
		return true;
	return false;
}
bool checkDiagonal(int x_, int y_, int player)//������̶ԽǷ����Ƿ�5���� ���򷵻�1�����򷵻�0
{	int count = 1;
	int x = x_;
	int y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x - 1, y - 1) && chessBoard[x - 1][y - 1] == player)//����
		{	count += 1;
			x--;
			y--;
		} else break;
	}
	x = x_;
	y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x + 1, y + 1) && chessBoard[x + 1][y + 1] == player)//����
		{	count += 1;
			x++;
			y++;
		} else break;
	}
	if (count >= 5)//��5���������ŵ�����
		return true;
	x = x_;
	y = y_;
	count = 1;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x - 1, y + 1) && chessBoard[x - 1][y + 1] == player)//����
		{	count += 1;
			x--;
			y++;
		} else break;
	}
	x = x_;
	y = y_;
	for (int i = 1; i < 5; i++)
	{	if (inboard(x + 1, y - 1) && chessBoard[x + 1][y - 1] == player)//����
		{	count += 1;
			x++;
			y--;
		} else break;
	}
	if (count >= 5)//��5���������ŵ�����
		return true;
	return false;
}
bool gameover(int x, int y, int player)//�ж��Ƿ���Ϸ����
{	return checkHorizontal(x, y, player) || checkVertical(x, y, player) || checkDiagonal(x, y, player);
}
/////////////////////////////////////////////////////////////////////////