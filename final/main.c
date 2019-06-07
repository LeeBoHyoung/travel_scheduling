//코드 테스트
#define _CRT_SECURE_NO_WARNINGS
#include "final.h"

route_p travel_route[1000];

int main() {
	//호텔 노드[가격]확인
	hotel_p root = NULL;
	hotel_p* h_T = &root;
	printf("호텔 노드[가격] 확인\n");
	root = make_hotel(h_T);
	inorder(h_T, root);
	printf("\n\n");


	//그래프 연결 상태
	site_p site_Graph[100] = { 0 };
	make_graph(site_Graph, root);
	site_p w;
	printf("그래프 연결 상태\n");
	for (int i = 0; i < 100; i++) {
		for (w = site_Graph[i]; w; w = w->edge_link) {
			printf("%s ", w->name);
		}
		printf("\n");
	}
	printf("\n\n");


	//DFS 경로 탐색
	int visit[100] = { 0 };
	printf("DFS 경로 탐색\n");
	DFS(site_Graph, site_Graph[0]->name, visit); //site-n[dist]
	printf("\n\n");

	//DFS_route
	memset(visit, 0, sizeof(int)*100);
	printf("site-1 출발 site-7 도착 경로\n");
	DFS_route(site_Graph, "site-1", "site-7", visit);
	for (int i = 0; travel_route[i] != NULL; i++) {
		route_p temp = travel_route[i];
		while (temp != NULL) {
			printf("%s[%d] ", temp->name, temp->trans_info.dist);
			temp = temp->link;
		}
		printf("\n");
	}
	printf("\n\n");


	
	//예약 노드 확인
	reserve_p r_root = NULL;
	reserve_p* r_T = &r_root;

	printf("예약자 노드 확인\n");
	r_create_nilnode(r_T);
	Reserve_INSERT(r_T, "lee", 1000, 300000, 3);
	Reserve_INSERT(r_T, "park", 2000, 450000, 2);
	Reserve_INSERT(r_T, "kim", 1500, 350000, 4);
	Reserve_INSERT(r_T, "song", 1200, 230000, 3);
	Reserve_INSERT(r_T, "seo", 1100, 200000, 3);
	r_inorder(r_T, r_root);
	printf("\n");
	Reserve_DELETE(r_T, "lee");
	r_inorder(r_T, r_root);
	system("pause");
}