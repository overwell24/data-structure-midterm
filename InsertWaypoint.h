// 단순 연결 리스트의 노드 구조를 구조체로 정의
typedef struct Waypoint {
	char Name;
	int X;
	int Y;
	struct Waypoint* link;
} Waypoint;

// 리스트의 시작을 나타내는 head 노드를 구조체로 정의
typedef struct {
	Waypoint* head;
} linkedWaypoint_h;

linkedWaypoint_h* createWaypoint_h(void);
void freeWaypoint_h(linkedWaypoint_h* L);
void printList(linkedWaypoint_h* L, FILE* fp);
void insertWaypoint(linkedWaypoint_h* L, char c, int x, int y);