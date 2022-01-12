#include <stdio.h>
#include <stdlib.h>	
#include <conio.h>	

#define X 1
#define O 2

char picture(int mode) {		
	switch (mode) {		
	case 0:
		return '.';	
		break;
	case X:
		return 'X';	
		break;
	case O:
		return 'O';	
		break;
	case 9:
		return '+';	
		break;
	default :
		return '.';
		break;
	}
}

int hor(int panel[][15], int y, int x, int object) {
	int connect = 0;
	for (int i = x - 4; i <= x + 4; i++) {
		if (panel[y][i] == object) {
			connect++;
			if (connect == 5) break;
		}
		else    connect = 0;
	}
	if (connect >= 5) return 1;
	else			  return 0;
}

int ver(int panel[][15], int y, int x, int object) {	//檢查y軸方向上是否連成五子
	int connect = 0;
	for (int i = y - 4; i <= y + 4; i++) {
		if (panel[i][x] == object) {
			connect++;
			if (connect == 5) break;
		}
		else    connect = 0;
	}
	if (connect >= 5) return 1;
	else			  return 0;
}

int slope(int panel[][15], int y, int x, int object) {	//檢查函數y=-x的影象所在直線方向上是否連成五子
	int connect = 0;
	for (int i = y - 4, j = x - 4; i <= y + 4; i++, j++) {
		if (panel[i][j] == object) {
			connect++;
			if (connect == 5) break;
		}
		else    connect = 0;
	}
	if (connect >= 5) return 1;
	else			  return 0;
}

int inverse_slope(int panel[][15], int y, int x, int object) {	//檢查函數y=x的影象所在直線方向上是否連成五子
	int connect = 0;
	for (int i = y + 4, j = x - 4; i >= y - 4; i--, j++) {
		if (panel[i][j] == object) {
			connect++;
			if (connect == 5) break;
		}
		else    connect = 0;
	}
	if (connect >= 5) return 1;
	else			  return 0;
}


typedef struct {
	int(*horizon)	   (int [][15], int, int, int);
	int(*vertucal)	   (int [][15], int, int, int);
	int(*slope)		   (int [][15], int, int, int);
	int(*inverse_slope)(int [][15], int, int, int);
}check_t;

check_t check = {
	hor,
	ver,
	slope,
	inverse_slope
};

int main(void) {
	int key = 0;
	
	int pixel[15][15] =
	{ 
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,9,0,0,0,0,0,0,0,9,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,9,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,9,0,0,0,0,0,0,0,9,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} 
	};

	int direction[] = { 7,7 };
	int turn = O;
	int winner = 0;		

	while (1) {
		
		system("cls");
		
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (i == direction[0] && j == direction[1]) printf("[ %c ]", picture(pixel[i][j]));
				else										printf("  %c  ", picture(pixel[i][j]));
			}
			printf("\n\n");
		}

		if (winner != 0) {
			printf("%c 玩家獲勝！\n", picture(winner));
			break;
		}

		key = getch();

		switch (key) {
		case 'w': case'W':
			direction[0] = (direction[0] == 0) ? 14 : direction[0] - 1;
			break;
		case 'a': case 'A':
			direction[1] = (direction[1] == 0) ? 14 : direction[1] - 1;
			break;
		case 's': case 'S':
			direction[0] = (direction[0] == 14) ? 0 : direction[0] + 1;
			break;
		case 'd': case 'D':
			direction[1] = (direction[1] == 14) ? 0 : direction[1] + 1;
			break;
		case 32:
			if (pixel[direction[0]][direction[1]] != X && pixel[direction[0]][direction[1]] != O) {
				pixel[direction[0]][direction[1]] = turn;
				if (   check.horizon      (pixel, direction[0], direction[1], turn)
					|| check.vertucal     (pixel, direction[0], direction[1], turn)
					|| check.slope        (pixel, direction[0], direction[1], turn)
					|| check.inverse_slope(pixel, direction[0], direction[1], turn)) {
					winner = turn;
					break;
				}
				if (turn == X) turn = O;
				else turn = X;
			}
			else {
				printf("這裡已經有棋子了！\n");
				system("pause");
			}
			break;
		case 'l': case 'L':
			printf("遊戲結束\n");
			return 0;
			break;
		default:
			printf("無效按鍵！\n");
			system("pause");
			break;
		}
	}

	
	system("pause");

	return 0;
}