#pragma once
#define _CRT_SECURE_NO_WARNINGS

typedef struct Waypoint {
    char    point;
    char    section[15];
    double  distance;
    double  batteryCost;
    double  k;
    double  cumulatedUsage;
    struct Waypoint* next;
} Waypoint;

typedef struct {
    Waypoint* head;
} Waypoint_h;

Waypoint_h* initWaypoint_h(void);
void freeWaypoint_h(Waypoint_h* wph);
void insertWaypoint(Waypoint_h* wph, char point, const char* section, double distance, double batteryCost, double k);
Waypoint* findWaypoint(Waypoint_h* wph, char point);