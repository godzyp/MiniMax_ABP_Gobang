#include "chessboard.h"
#include "movesearch.h"
#include <iostream>
using namespace std;
int main()
{	cout << "*************五子棋博弈系统*************" << endl;
	cout << " 玩家为黑棋先手" << endl;
	cout << " 输入: x y  表示落子点(x=行；y=列)" << endl;
	cout << " 输入: 0 0  表示退出游戏" << endl << endl;
	print();
	int x, y;
	while (true) 
	{	cout << endl;
		cin >> x >> y;//玩家输入落子位置x和y
		if (x == 0 && y == 0)
		{	cout << "***************游戏结束***************" << endl;
			break;
		}
		if (!makeMove(x, y, black))//玩家落子位置若已存在棋子则撤回
		{	cout << "落子有误." << endl;
			continue;
		}
		if (steps.size() >= 255)//落子数超过棋盘最大规模算平局
		{	print();
			cout << "平局." << endl;
		}
		if (gameover(x, y, black))//玩家落子后存在5连子则电脑胜
		{	print();
			cout << "玩家胜利." << endl;
			break;
		}
		cout << "电脑回合..." << endl;
		auto choice = searchMove(white);//使用alpha-beta算法计算落子选择
		makeMove(choice.first, choice.second, white);//电脑落子
		system("cls");//电脑落子后清屏
		if (gameover(choice.first, choice.second, white)) //电脑落子后存在5连子则电脑胜
		{	print();
			cout << "电脑胜利." << endl;
			break;
		}
		if (steps.size() >= 255) //落子数超过棋盘最大规模算平局
		{	print();
			cout << "平局." << endl;
		}
		print();
		cout << " 输入: x y  表示落子点." << endl;
		cout << " 输入: 0 0  表示退出游戏." << endl;
	}
	return 0;
}

