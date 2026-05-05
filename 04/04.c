#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "drone.h"

void ReadWaypoint(Waypoint_h* wph, FILE* fp);	//파일 읽어서 Waypoint 입력
void simulate(Drone* drone);

void ReadWaypoint(Waypoint_h* wph, FILE* fp) {	//파일 읽어서 Waypoint 입력
    char line[256];
    char section[10];
    char kStr[10];
    double distance, k, batteryCost;
    int isFirst = 1;

    fgets(line, sizeof(line), fp);  // 헤더 스킵

    while (fscanf(fp, " %s \t %lf \t %s \t %lf", section, &distance, kStr, &batteryCost) == 4) {
        if (section[0] == 'T')  // Total 행 스킵
            continue;
        if (kStr[0] == '-')     // k가 '-'인 경우 배터리소모/거리로 계산
            k = (distance > 0.0) ? batteryCost / distance : 0.0;
        else
            k = atof(kStr); // 문자열 숫자로 변환

        if (isFirst) {
            insertWaypoint(wph, section[0], "", 0.0, 0.0, 0.0);  // 원점
            isFirst = 0;
        }
        insertWaypoint(wph, section[1], section, distance, batteryCost, k);
    }
}
void simulate(Drone* drone) {
    FILE* fp = fopen("04.txt", "w");
    
    fprintf(fp, "%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t\t%-10s\t\t%s\n","구간", "거리", "k", "배터리소모", "누적소모", "상태", "이벤트", "안전회귀경로");  // 파일 헤더 출력

    push(drone->safeReturnPath, drone->wph->head->point);  // 시작 지점 초기화
    Waypoint* waypoint = drone->wph->head->next;

    while (waypoint != NULL) {
        double nextCumulatedUsage = drone->cumulatedUsage + waypoint->batteryCost;
        double nextRemainingBattery = INITIAL_BATTERY - nextCumulatedUsage;  // 경로 진행시 남을 배터리 잔량

        if (nextRemainingBattery < BATTERY_THRESHOLD) {  // 배터리 임계치 조건문
           
            // 총 안전회귀 경로 문자열 만들기
            char pathStr[256] = "";
            char tmp[8];
            sprintf(tmp, "%c->", waypoint->point);
            strcat(pathStr, tmp);

            SafeReturnPoint* safeReturnPoint = drone->safeReturnPath->top;
            while (safeReturnPoint) {
                sprintf(tmp, "%c", safeReturnPoint->point);
                strcat(pathStr, tmp);
                if (safeReturnPoint->link) strcat(pathStr, "->");
                safeReturnPoint = safeReturnPoint->link;
            }
            // FAILURE 행 출력
            fprintf(fp, "%-10s\t%-10.1f\t%-10.1f\t%-10.1f\t%-10.1f\t%-10s\t\t%-10s\t\t%s\n", waypoint->section, waypoint->distance, waypoint->k, waypoint->batteryCost, nextCumulatedUsage, "FAILURE", "미션실패", pathStr);
            break;
        }

        // 드론 이동 후 상태 업데이트 
        drone->cumulatedUsage = nextCumulatedUsage;
        waypoint->cumulatedUsage = drone->cumulatedUsage;
        push(drone->safeReturnPath, waypoint->point);

        // NORMAL 행 출력
        fprintf(fp, "%-10s\t%-10.1f\t%-10.1f\t%-10.1f\t%-10.1f\t%-10s\t\t%-10s\t\t%s\n",waypoint->section, waypoint->distance, waypoint->k, waypoint->batteryCost, drone->cumulatedUsage, "NOMAL", "-", "-");

        waypoint = waypoint->next;
    }

   
    while (drone->safeReturnPath->top && drone->safeReturnPath->top->link) {
        // 비행 성공했던 마지막 point
        element curPoint = pop(drone->safeReturnPath);
        //비행 성공했던 point의 전 출발지
        element nextPoint = peek(drone->safeReturnPath);

        // 마지막 성공했던 waypoint 가져오기 
        Waypoint* wp = findWaypoint(drone->wph, curPoint);
        // (회귀) 붙이기
        strcat(wp->section, "(회귀)");
        // 경로 만들기
        char pathStr[10];
        sprintf(pathStr, "%c->%c", curPoint, nextPoint);

        //  RECOVERY 행  출력
        fprintf(fp, "%-10s\t%-10s\t%-10s\t%-10s\t%-10.1f\t%-10s\t%-10s\t\t%s\n",wp->section, "-", "-", "-",wp ? wp->cumulatedUsage : 0.0,"RECOVERY", "역추적", pathStr);
    }

    fclose(fp);
}

int main(void) {
    Drone* drone = initDrone();

    FILE* fp2 = fopen("03.txt", "r");	//파일 읽어서 Waypoint입력
    ReadWaypoint(drone->wph, fp2);
    fclose(fp2);

    simulate(drone);

    freeDrone(drone);

    system("notepad.exe 04.txt");
    return 0;
}