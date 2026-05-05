#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "InsertPath.h"
// 공백 연결 리스트를 생성하는 연산
linkedPath_h* createPath_h(void) {
	linkedPath_h* L;
	L = (linkedPath_h*)malloc(sizeof(linkedPath_h));
	L->head = NULL;		// 공백 리스트이므로 NULL로 설정
	return L;
}

// 연결 리스트의 전체 메모리를 해제하는 연산
void freePath_h(linkedPath_h* L) {
	Path* p;
	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->link;
		free(p);
		p = NULL;
	}
}

// 연결 리스트를 순서대로 출력하는 연산
void printPath(linkedPath_h* L, FILE* fp) {
	Path* p;
	p = L->head;
	double Msum = 0, Bsum = 0;

	fprintf(stdout, "구간\t 거리(m)\t k\t 배터리 소모\n");
	fprintf(fp, "구간\t 거리(m)\t k\t 배터리 소모\n");
	while (p != NULL) {
		fprintf(stdout, "%s\t %.1lf\t\t %.1lf\t %.1lf\n", p->Section, p->Meter, p->K, p->Consumption);
		fprintf(fp, "%s\t %.1lf\t %.1lf\t %.1lf\n", p->Section, p->Meter, p->K, p->Consumption);
		Msum += p->Meter;
		Bsum += p->Consumption;
		p = p->link;
	}
	fprintf(stdout, "Total\t %.1lf\t\t -\t %.1lf\n", Msum, Bsum);
	fprintf(fp, "Total\t %.1lf\t -\t %.1lf\n", Msum, Bsum);
}


// 마지막 노드로 삽입하는 연산 
void insertPath(linkedPath_h* L, char* s, double m, double k, double c) {
	Path* newNode;
	Path* temp;
	newNode = (Path*)malloc(sizeof(Path));
	strcpy(newNode->Section, s);
	newNode->Meter = m;
	newNode->K = k;
	newNode->Consumption = c;
	newNode->link = NULL;
	if (L->head == NULL) {		// 현재 리스트가 공백인 경우					
		L->head = newNode;		// 새 노드를 리스트의 시작 노드로 연결
		return;
	}
	// 현재 리스트가 공백이 아닌 경우 	
	temp = L->head;
	while (temp->link != NULL) temp = temp->link;	// 현재 리스트의 마지막 노드를 찾음
	temp->link = newNode;							// 새 노드를 마지막 노드(temp)의 다음 노드로 연결 
}