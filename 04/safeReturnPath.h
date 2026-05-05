#pragma once
#define _CRT_SECURE_NO_WARNINGS
typedef char element;

typedef struct SafeReturnPoint {
    element point;
    struct SafeReturnPoint* link;
} SafeReturnPoint;

typedef struct {
    SafeReturnPoint* top;
} SafeReturnPath;

SafeReturnPath* initPath(void);
void    freePath(SafeReturnPath* safeReturnPath);
int     isEmpty(SafeReturnPath* safeReturnPath);
void    push(SafeReturnPath* safeReturnPath, element point);
element pop(SafeReturnPath* safeReturnPath);
element peek(SafeReturnPath* safeReturnPath);