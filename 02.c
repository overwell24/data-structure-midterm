#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "InsertWaypoint.h"
#define SIZE 5	//배열의 크기

void ReadFile(FILE* fp, int* x, int* y);	//파일 읽어서 좌표 입력
void CalculateDistance(double* d, int* x, int* y);	//원점으로부터 거리 계산
void order(double* d, int* x, int* y);	//원점으로부터 거리를 오름차순으로 정렬

int main(void) {
	linkedWaypoint_h* L;
	L = createWaypoint_h();
	FILE* fp1 = fopen("01.txt", "r");
	FILE* fp2 = fopen("02.txt", "a+");

	int i;
	int X[SIZE];	//x좌표
	int Y[SIZE];	//y좌표
	double distance[SIZE];		//원점으로부터 거리
	char ASCII = 65;

	ReadFile(fp1, X, Y);
	fclose(fp1);

	CalculateDistance(distance, X, Y);

	order(distance, X, Y);	//원점으로부터 거리를 오름차순으로 정렬

	for (i = 0; i < SIZE; i++) {
		insertWaypoint(L, ASCII, X[i], Y[i]);
		ASCII++;
	}
	printWaypoint(L, fp2);
	freeWaypoint_h(L);
	
	fclose(fp2);
	system("notepad.exe 02.txt");

	return 0;
}

void ReadFile(FILE* fp, int* x, int* y) {	//파일 읽어서 좌표 입력
	int i = 0;

	while (!feof(fp)) {	//fp1이 끝나지 않는 동안 반복
		fscanf(fp, " %d %d", &x[i], &y[i]);	//파일 입력
		i++;
		if (i >= SIZE) break; // i가 배열 크기를 넘어가면 즉시 중단
	}
}

void CalculateDistance(double* d, int* x, int* y) {	//원점으로부터 거리 계산
	int i;
	
	for (i = 0; i < SIZE; i++) {
		d[i] = sqrt(x[i] * x[i] + y[i] * y[i]);	//원점으로 부터 거리 계산
	}	//sqrt는 math.h에 있는 루트함수
}

void order(double* d, int* x, int* y) {	//원점으로부터 거리를 오름차순으로 정렬
	int i, j;
	double temp;
	int tmp;
	
	for (i = 0; i < SIZE - 1; i++) {
		for (j = 0; j < SIZE - 1; j++) {
			if (d[j] > d[j + 1])
			{
				temp = d[j + 1];
				d[j + 1] = d[j];
				d[j] = temp;

				tmp = x[j + 1];
				x[j + 1] = x[j];
				x[j] = tmp;

				tmp = y[j + 1];
				y[j + 1] = y[j];
				y[j] = tmp;
			}
		}

	}
}