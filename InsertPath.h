// 단순 연결 리스트의 노드 구조를 구조체로 정의
typedef struct Path {
	char Section[3];
	double Meter;
	double K;
	double Consumption;
	struct Path* link;
} Path;

// 리스트의 시작을 나타내는 head 노드를 구조체로 정의
typedef struct {
	Path* head;
} linkedPath_h;

linkedPath_h* createPath_h(void);
void freePath_h(linkedPath_h* L);
void printPath(linkedPath_h* L, FILE* fp);
void insertPath(linkedPath_h* L, char* s, double m, double k, double c);