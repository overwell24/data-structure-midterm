#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 5	//배열의 크기
#define MAX 1000	//최대 좌표

void random(int* x, int* y, int size);	//난수 입력
void printXY(FILE* f, int* x, int* y, int size);	//좌표 출력

int main(void) {
	FILE* fp = fopen("01.txt", "a+");

	int i;
	int X[SIZE];	//x좌표
	int Y[SIZE];	//y좌표

	X[0] = 0;	//시작점 고정
	Y[0] = 0;	//시작점 고정

	random(X, Y, SIZE);
	printXY(fp, X, Y, SIZE);

	fclose(fp);
	system("notepad.exe 01.txt");

	return 0;
}

void random(int* x, int* y, int size)
{
	int i;

	srand((unsigned)time(NULL));	//현재 시간 기준으로 난수 표 사용	
	for (i = 1; i < size; i++)
	{
		x[i] = rand() % MAX;			//난수 표에서 배열로 입력
		y[i] = rand() % MAX;
	}
}

void printXY(FILE* fp, int* x, int* y, int size) {
	int i;
	
	for (i = 0; i < SIZE; i++) {
		fprintf(stdout, "%d\t %d\n", x[i], y[i]);
		fprintf(fp, "%d\t %d\n", x[i], y[i]);
	}
}