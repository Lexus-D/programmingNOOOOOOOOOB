#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

void PrintChessboard(int a[4][4]) {
	int i, j;
	//棋盘元素：
	char s[4] = "ox-";
	
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (i == 0 || j == 0) {
				if (i == 0 && j == 0) {
					printf(" ");//左上角的空格
				}
				else {
					printf("%d", a[i][j]);//打印棋盘坐标
				}
			}
			else {
				printf("%c", s[a[i][j]]);//打印棋子
			}
		}
		printf("\n");
	}
}

//调试：
void Tester(int map[4][4]) {
	printf("棋盘后的参数：\n");
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

//初始化棋盘（全都是-）
void initialize(int map[4][4]){
	//4x4的矩阵中 3x3的棋盘 第0行和第0列是棋盘坐标
	int i, j;
	//棋盘坐标:
	map[0][1] = 0;
	map[0][2] = 1;
	map[0][3] = 2;
	map[1][0] = 0;
	map[2][0] = 1;
	map[3][0] = 2;
	for (i = 1; i < 4; i++) {
		for (j = 1; j < 4; j++) {
			map[i][j] = 2;
		}
	}
}

//判断胜利条件
int judge(int map[4][4]) {
	//判断行
	for (int i = 1; i < 4; i++) {
		if (map[i][1] == map[i][2] && map[i][2] == map[i][3] && map[i][1] != 2) {
			return map[i][1];
		}
	}
	//判断列
	for (int j = 1; j < 4; j++) {
		if (map[1][j] == map[2][j] && map[2][j] == map[3][j] && map[1][j] != 2) {
			return map[1][j];

		}
	}
	//判断对角线
	if (map[1][1] == map[2][2] && map[2][2] == map[3][3] && map[1][1] != 2) {
		return map[1][1];
	}
	else if (map[1][3] == map[2][2] && map[2][2] == map[3][1] && map[1][3] != 2) {
		return map[1][3];
	}
	return 9;
}
int main(void) {
	int a, b, turn_count=0, x, y, min = 0, max = 2;
	int map[4][4];
	srand((unsigned int)time(NULL));//生成随机数种子
	initialize(map);
	PrintChessboard(map);

	while (1) {
		//玩家回合
		printf("(row)y:"); scanf_s("%d", &a);
		printf("(col)x:"); scanf_s("%d", &b);

		while (a > 2 || b > 2 || map[a + 1][b + 1] != 2)
			//判断坐标输入错误（输入的坐标能否下棋子）
		{
			printf("error! already used position\n");
			printf("(row)y:"); scanf_s("%d", &a);
			printf("(col)x:"); scanf_s("%d", &b);
		}
		y = 1 + a; x = 1 + b;//把输入的坐标转换成棋盘坐标
		map[y][x] = 0;//棋盘上把-改成玩家的棋子
		turn_count++;
		
		//刷新棋盘：
		system("cls");
		PrintChessboard(map);
		
		//调试：
		//Tester(map);

		//用胜利条件判断玩家胜平：
		if (judge(map) == 0) {
			printf("You Win! XD\n");
			break;
		}
		else if (turn_count == 9) {
			printf("Draw.\n");
			break;
		}
	
		//电脑回合
		Sleep(1000);//让电脑装作思考一秒钟
		while (1) {
			
			int fatal_i = 0, fatal_j = 0;//存放下一步落子的位置的坐标
			
			//电脑的策略：某行某列某对角线有两个相同的棋且有一个空，电脑就得下那个空
			//判断行
			for (int i = 1; i < 4; i++) {
				if (map[i][1] == map[i][2] && map[i][3] == 2 && map[i][1] != 2) {
					fatal_i = i;
					fatal_j = 3;
					break;
				}
				else if (map[i][2] == map[i][3] && map[i][1] == 2 && map[i][2] != 2) {
					fatal_i = i;
					fatal_j= 1;
					break;
				}
				else if (map[i][1] == map[i][3] && map[i][2] == 2 && map[i][1] != 2) {
					fatal_i = i;
					fatal_j = 2;
					break;
				}
			}
			//判断列
			for (int j = 1; j < 4; j++) {
				if (map[1][j] == map[2][j] && map[3][j] == 2 && map[1][j] != 2) {
					fatal_i = 3;
					fatal_j = j;
					break;
				}
				else if (map[2][j] == map[3][j] && map[1][j] == 2 && map[2][j] != 2) {
					fatal_i = 1; 
					fatal_j = j;
					break;
				}
				else if (map[1][j] == map[3][j] && map[2][j] == 2 && map[1][j] != 2) {
					fatal_i = 2;
					fatal_j = j;
					break;
				}
			}
			//判断对角线
			if (map[1][1] == map[2][2] && map[1][1] != 2 && map[3][3] == 2) {
				fatal_i = 3;
				fatal_j = 3;
			}
			else if (map[2][2] == map[3][3] && map[2][2] != 2 && map[1][1] == 2) {
				fatal_i = 1;
				fatal_j = 1;
			}
			else if ((map[1][1] == map[3][3] && map[1][1] != 2 && map[2][2] == 2) || (map[1][3] == map[3][1] && map[1][3] != 2 && map[2][2] == 2)) {
				fatal_i = 2;
				fatal_j = 2;
			}
			else if (map[1][3] == map[2][2] && map[1][3] != 2 && map[3][1] == 2) {
				fatal_i = 3;
				fatal_j = 1;
			}
			else if (map[2][2] == map[3][1] && map[3][1] != 2 && map[1][3] == 2) {
				fatal_i = 1;
				fatal_j = 3;
			}
			//落子
			if (fatal_i == 0 && fatal_j == 0) {
				//生成随机坐标：
				while (1) {
					y = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
					x = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
					if (map[y][x] == 2) {
						map[y][x] = 1;
						turn_count++;
						break;
					}
				}
				break;
			}
			else {
				map[fatal_i][fatal_j] = 1;
				turn_count++;
				break;
			}
		}
		
		//刷新棋盘：
		system("cls");
		PrintChessboard(map);
		
		//Tester(map);

		//判断电脑胜利
		if (judge(map) == 1) {
			printf("You lose... T_T\n");
			break;
		}
	}
	system("pause");

	return 0;

}