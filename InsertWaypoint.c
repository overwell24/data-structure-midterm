#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "InsertLinkedList.h"
// 공백 연결 리스트를 생성하는 연산
linkedList_h* createLinkedList_h(void) {
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;		// 공백 리스트이므로 NULL로 설정
	return L;
}

// 연결 리스트의 전체 메모리를 해제하는 연산
void freeLinkedList_h(linkedList_h* L) {
	Waypoint* p;
	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->link;
		free(p);
		p = NULL;
	}
}

// 연결 리스트를 순서대로 출력하는 연산
void printList(linkedList_h* L, FILE* fp) {
	Waypoint* p;
	p = L->head;
	while (p != NULL) {
		fprintf(stdout, "%c\t %d\t %d", p->Name, p->X, p->Y);
		fprintf(fp, "%c\t %d\t %d", p->Name, p->X, p->Y);
		p = p->link;
		if (p != NULL) {
			fprintf(stdout, "\n");
			fprintf(fp, "\n");
		}
	}
}

// 마지막 노드로 삽입하는 연산 
void insertLastNode(linkedList_h* L, char c, int x, int y) {
	Waypoint* newNode;
	Waypoint* temp;
	newNode = (Waypoint*)malloc(sizeof(Waypoint));
	//strcpy(newNode->Name, c);
	newNode->Name = c;
	newNode->X = x;
	newNode->Y = y;
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