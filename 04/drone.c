#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "drone.h"

Drone* initDrone(void) {
    Drone* drone = (Drone*)malloc(sizeof(Drone));
    drone->cumulatedUsage = 0.0;    // 예제 만족을 위해 넣은 변수 
    strcpy(drone->status, "NORMAL");
    strcpy(drone->event, "-");
    drone->wph = initWaypoint_h();
    drone->safeReturnPath = initPath();
    return drone;
}

void freeDrone(Drone* drone) {
    freeWaypoint_h(drone->wph);
    freePath(drone->safeReturnPath);
    free(drone);
}