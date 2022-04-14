#include "Ranking.h"
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define DIM 5 //5*5����

enum Direction { Left = 75, Right = 75, Up = 72, Down = 80 };
static int DirKey[4] = { Left, Right, Up, Down };
static int map[DIM][DIM];
static int x, y;
static int nMove;
static clock_t tStart;

static void init()
{
	for (int i = 0; i < DIM * DIM - 1; i++)
		map[i / DIM][i % DIM] = i + 1;
	map[DIM - 1][DIM - 1] = 0;
	x = DIM - 1; y = DIM - 1;

	srand(time(NULL));
	tStart = clock();
	nMove = 0;

}

static void display()
{
	system("cls");
	printf("\tFifteen Puzzle\n\t");
	printf("--------------\n\t");
	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			if (map[r][c] > 0)
			{
				if (map[r][c] <= 5)
					printf("%6s", "|) _");
				else
					printf("%6s","| (_");


			}

			else
				printf(" ");

		}
		printf("\n\t");
	}
	printf("--------------\n\t");
	clock_t t1 = clock();
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	printf("\n\t�̵� Ƚ��:%6d\n\t �ҿ�ð�:%6.1f\n\n", nMove, d);
}
static bool move(int dir)
{
	if (dir == Right && x > 0)
	{
		map[y][x] = map[y][x - 1];
		map[y][--x] = 0;

	}
	else if (dir == Left && x < DIM - 1)
	{
		map[y][x] = map[y][x + 1];
		map[y][++x] = 0;
	}
	else if (dir == Up && y < DIM - 1)
	{
		map[y][x] = map[y + 1][x];
		map[++y][x] = 0;
	}
	else if (dir == Down && y > 0)
	{
		map[y][x] = map[y - 1][x];
		map[--y][x] = 0;
	}

	else return false;

	nMove++;
	return true;

}

static void shuffle(int nShuffle)
{
	for (int i = 0; i < nShuffle; i++)
	{
		int key = DirKey[rand() % 4];
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
	}
}

static bool isDone()
{
	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			if (map[r][c] != r * DIM + c + 1)
				return (r == DIM - 1) && (c == DIM - 1);
		}

	}
	return true;
}

static int getDirKey() { return getche() == 224 ? getche() : 0; }

static int mapTmp[DIM][DIM];
static int history[1000];
static int nHist = 0, _x, _y;

void backupInitMap(bool backup = true) {
	if (backup) {
		for (int i = 0; i < DIM; i++)
			for (int j = 0; j < DIM; j++)
				mapTmp[i][j] = map[i][j];
		_x = x;
		_y = y;
	}
	else {
		for (int i = 0; i < DIM; i++)
			for (int j = 0; j < DIM; j++)
				map[i][j] = mapTmp[i][j];
		x = _x;
		y = _y;
	}
}

int playFifteenPuzzle() {
	init();
	display();
	printf("\n ������ �����ּ���(����)...");
	getche();
	shuffle(20);

	backupInitMap();

	printf("\n ������ ���۵˴ϴ�...");
	getche();

	nMove = 0;
	nHist = 0;
	while (!isDone()) {
		history[nHist] = getDirKey();
		move(history[nHist]);
		display();
		nHist++;
	}

	printf("\n Replay...");
	getche();

	init();
	backupInitMap(false);
	display();
	printf("\n Ű�� �����ּ���...");
	getche();

	for (int i = 0; i < nHist; i++) {
		move(history[i]);
		display();
		Sleep(200);
	}

	return 1;
}



/*
int playFifteenPuzzle()
{
	init();
	display();
	printRanking();
	printf("\n ������ �����ּ���(����)...");
	getche();
	shuffle(100);
	printf("\n ������ ���۵˴ϴ�...");
	getche();

	nMove = 0;
	tStart = clock();
	while (!isDone())
	{
		move(getDirKey());
		display();
	}
	clock_t t1 = clock();
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	return addRanking(nMove, d);

}
*/