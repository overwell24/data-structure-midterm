#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "waypoint.h"
#include "safeReturnPath.h"

#define INITIAL_BATTERY    1000.0
#define BATTERY_THRESHOLD  500.0       

typedef struct {
    double           cumulatedUsage;
    char             status[20];
    char             event[20];
    Waypoint_h* wph;
    SafeReturnPath* safeReturnPath;
} Drone;

Drone* initDrone(void);
void   freeDrone(Drone* d);