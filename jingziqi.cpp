/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

void hyouji(int a[4][4]) {
	int i, j;
	//棋盘元素：
	char s[4] = "ox-";
	
	for (i = 0; i < 4; i = i + 1) {
		for (j = 0; j < 4; j = j + 1) {
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

//4x4的矩阵中 3x3的棋盘 第0行和第0列是棋盘坐标
void initialize(int map[4][4]){
	int i, j;
	//棋盘坐标:
	map[0][1] = 0;
	map[0][2] = 1;
	map[0][3] = 2;
	map[1][0] = 0;
	map[2][0] = 1;
	map[3][0] = 2;
	//初始化棋盘（全都是-）
	for (i = 1; i < 4; i = i + 1) {
		for (j = 1; j < 4; j = j + 1) {
			map[i][j] = 2;
		}
	}
}

//判断胜利条件
int judge(int map[4][4]) {
	for (int i = 1; i < 4; i++) {
		if (map[i][1] == map[i][2] && map[i][2] == map[i][3] && map[i][1] != 2) {
			return map[i][1];
		}
	}
	for (int j = 1; j < 4; j++) {
		if (map[1][j] == map[2][j] && map[2][j] == map[3][j] && map[1][j] != 2) {
			return map[1][j];
		}
	}
	if (map[1][1] == map[2][2] && map[2][2] == map[3][3] && map[1][1] != 2) {
		return map[1][1];
	}
	else if (map[1][3] == map[2][2] && map[2][2] == map[3][1] && map[1][3] != 2) {
		return map[1][3];
	}

}
int main(void) {
	int i, j, turn_count=0, x, y, min = 0, max = 2;
	int map[4][4];
	srand((unsigned int)time(NULL));//生成随机数种子

	initialize(map);
	hyouji(map);

	
	
	while (1) {
		printf("(row)y:"); scanf_s("%d", &i);
		printf("(col)x:"); scanf_s("%d", &j);


		while (i > 2 || j > 2 || map[i + 1][j + 1] != 2)
			//判断坐标输入错误（输入的坐标能否下棋子）
		{
			printf("error! please input a integer from [0,2]\n");
			printf("y:"); scanf_s("%d", &i);
			printf("x:"); scanf_s("%d", &j);
		}
		y = 1 + i; x = 1 + j;//把输入的坐标转换成棋盘坐标
		map[y][x] = 0;//棋盘上把-改成玩家的棋子
		turn_count++;
		
		//刷新棋盘：
		system("cls");
		hyouji(map);

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
		while (1) {
			//生成坐标：
			y = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
			x = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
			if (map[y][x] == 2) {
				map[y][x] = 1;
				turn_count++;
				break;
			}
		}
		
		//判断电脑胜利
		if (judge(map) == 1) {
			printf("You lose... T_T\n");
			break;
		}

		//刷新棋盘：
		system("cls");
		hyouji(map);

		
		
		

	}
	return(0);
}