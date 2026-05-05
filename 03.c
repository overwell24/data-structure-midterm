#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "InsertWaypoint.h"
#include "InsertPath.h"

void ReadWaypoint(linkedWaypoint_h* L, FILE* fp);	//파일 읽어서 Waypoint 입력
double Calculate(int x1, int x2, int y1, int y2);	//점과 점 사이 거리 계산
void Insert(linkedWaypoint_h* L1, linkedPath_h* L2); //거리 및 배터리 소모 연결리스트 저장

int main(void) {
	linkedWaypoint_h* L1;
	linkedPath_h* L2;
	L1 = createWaypoint_h();
	L2 = createPath_h();

	FILE* fp2 = fopen("02.txt", "r");
	FILE* fp3 = fopen("03.txt", "a+");
	
	ReadWaypoint(L1, fp2);	//파일 읽어서 Waypoint입력
	fclose(fp2);

	Insert(L1, L2);	//거리 및 배터리 소모 연결리스트 저장
	freeWaypoint_h(L1);	//Waypoint free

	printPath(L2, fp3);	//거리 및 배터리 소모량 출력
	freePath_h(L2);	//Path free

	fclose(fp3);
	system("notepad.exe 03.txt");

	return 0;
}

void ReadWaypoint(linkedWaypoint_h* L, FILE* fp) {	//파일 읽어서 좌표 입력
	int x, y, i = 0;
	char c;

	while (!feof(fp)) {	//fp1이 끝나지 않는 동안 반복
		fscanf(fp, " %c %d %d", &c, &x, &y);	//파일 입력
		insertWaypoint(L, c, x, y);
		i++;
		if (i >= SIZE) break; // i가 배열 크기를 넘어가면 즉시 중단
	}
}

double Calculate(int x1, int x2, int y1, int y2) {	//점과 점 사이 거리 계산
	return sqrt((x2-x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	//sqrt는 math.h에 있는 루트함수
}

void Insert(linkedWaypoint_h* L1, linkedPath_h* L2) {	//거리 및 배터리 소모 연결리스트 저장
	Waypoint* p;
	double d, k;
	char section[3];

	p = L1->head;

	while (p != NULL && p->link != NULL) {
		section[0] = p->Name;
		section[1] = p->link->Name;
		section[2] = '\0';

		d = Calculate(p->X, p->link->X, p->Y, p->link->Y);
		if (d <= 100)
			k = 1.5;
		else
			k = 1.7;

		insertPath(L2, section, d, k, d * k);

		p = p->link;
	}
}