#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "safeReturnPath.h"

SafeReturnPath* initPath(void) {
    SafeReturnPath* safeReturnPath = (SafeReturnPath*)malloc(sizeof(SafeReturnPath));
    safeReturnPath->top = NULL;
    return safeReturnPath;
}

void freePath(SafeReturnPath* safeReturnPath) {
    while (safeReturnPath->top) pop(safeReturnPath);
    free(safeReturnPath);
}

int isEmpty(SafeReturnPath* safeReturnPath) {
    return safeReturnPath->top == NULL;
}

void push(SafeReturnPath* safeReturnPath, element point) {
    SafeReturnPoint* temp = (SafeReturnPoint*)malloc(sizeof(SafeReturnPoint));
    temp->point = point;
    temp->link = safeReturnPath->top;
    safeReturnPath->top = temp;
}

element pop(SafeReturnPath* safeReturnPath) {
    if (isEmpty(safeReturnPath)) return 0;
    SafeReturnPoint* temp = safeReturnPath->top;
    element point = temp->point;
    safeReturnPath->top = temp->link;
    free(temp);
    return point;
}

element peek(SafeReturnPath* safeReturnPath) {
    if (isEmpty(safeReturnPath)) return 0;
    return safeReturnPath->top->point;
}