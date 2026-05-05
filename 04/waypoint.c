#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "waypoint.h"

Waypoint_h* initWaypoint_h(void) {
    Waypoint_h* wph = (Waypoint_h*)malloc(sizeof(Waypoint_h));
    wph->head = NULL;
    return wph;
}

void freeWaypoint_h(Waypoint_h* wph) {
    Waypoint* cur = wph->head;
    while (cur) {
        Waypoint* n = cur->next;
        free(cur);
        cur = n;
    }
    free(wph);
}

void insertWaypoint(Waypoint_h* wph, char point, const char* section,
    double distance, double batteryCost, double k) {
    Waypoint* newWaypoint = (Waypoint*)malloc(sizeof(Waypoint));
    newWaypoint->point = point;
    strcpy(newWaypoint->section, section);
    newWaypoint->distance = distance;
    newWaypoint->batteryCost = batteryCost;
    newWaypoint->k = k;
    newWaypoint->cumulatedUsage = 0.0;
    newWaypoint->next = NULL;

    if (!wph->head) {
        wph->head = newWaypoint;
    }
    else {
        Waypoint* temp = wph->head;
        while (temp->next) temp = temp->next;
        temp->next = newWaypoint;
    }
}

// 해당 point를 가진 waypoint 노드를 반환 하는 함수
Waypoint* findWaypoint(Waypoint_h* wph, char point) {
    Waypoint* p = wph->head;

    while (p != NULL) {
        if (p->point == point)  return p;
        p = p->next;
    }

    return NULL;
}