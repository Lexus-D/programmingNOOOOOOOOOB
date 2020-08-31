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
	//����Ԫ�أ�
	char s[4] = "ox-";
	
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (i == 0 || j == 0) {
				if (i == 0 && j == 0) {
					printf(" ");//���ϽǵĿո�
				}
				else {
					printf("%d", a[i][j]);//��ӡ��������
				}
			}
			else {
				printf("%c", s[a[i][j]]);//��ӡ����
			}
		}
		printf("\n");
	}
}

//���ԣ�
void Tester(int map[4][4]) {
	printf("���̺�Ĳ�����\n");
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

//��ʼ�����̣�ȫ����-��
void initialize(int map[4][4]){
	//4x4�ľ����� 3x3������ ��0�к͵�0������������
	int i, j;
	//��������:
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

//�ж�ʤ������
int judge(int map[4][4]) {
	//�ж���
	for (int i = 1; i < 4; i++) {
		if (map[i][1] == map[i][2] && map[i][2] == map[i][3] && map[i][1] != 2) {
			return map[i][1];
		}
	}
	//�ж���
	for (int j = 1; j < 4; j++) {
		if (map[1][j] == map[2][j] && map[2][j] == map[3][j] && map[1][j] != 2) {
			return map[1][j];

		}
	}
	//�ж϶Խ���
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
	srand((unsigned int)time(NULL));//�������������
	initialize(map);
	PrintChessboard(map);

	while (1) {
		//��һغ�
		printf("(row)y:"); scanf_s("%d", &a);
		printf("(col)x:"); scanf_s("%d", &b);

		while (a > 2 || b > 2 || map[a + 1][b + 1] != 2)
			//�ж����������������������ܷ������ӣ�
		{
			printf("error! already used position\n");
			printf("(row)y:"); scanf_s("%d", &a);
			printf("(col)x:"); scanf_s("%d", &b);
		}
		y = 1 + a; x = 1 + b;//�����������ת������������
		map[y][x] = 0;//�����ϰ�-�ĳ���ҵ�����
		turn_count++;
		
		//ˢ�����̣�
		system("cls");
		PrintChessboard(map);
		
		//���ԣ�
		//Tester(map);

		//��ʤ�������ж����ʤƽ��
		if (judge(map) == 0) {
			printf("You Win! XD\n");
			break;
		}
		else if (turn_count == 9) {
			printf("Draw.\n");
			break;
		}
	
		//���Իغ�
		Sleep(1000);//�õ���װ��˼��һ����
		while (1) {
			
			int fatal_i = 0, fatal_j = 0;//�����һ�����ӵ�λ�õ�����
			
			//���ԵĲ��ԣ�ĳ��ĳ��ĳ�Խ�����������ͬ��������һ���գ����Ծ͵����Ǹ���
			//�ж���
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
			//�ж���
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
			//�ж϶Խ���
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
			//����
			if (fatal_i == 0 && fatal_j == 0) {
				//����������꣺
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
		
		//ˢ�����̣�
		system("cls");
		PrintChessboard(map);
		
		//Tester(map);

		//�жϵ���ʤ��
		if (judge(map) == 1) {
			printf("You lose... T_T\n");
			break;
		}
	}
	system("pause");

	return 0;

}