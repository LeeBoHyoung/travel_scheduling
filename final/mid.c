#include "final.h"

extern route_p travel_route[1000];

//Call the following functions at GUI level.


void init_map(site_p* site_Graph, hotel_p root){
	//Initialize a map that contains sites, trans, hotels.
	make_graph(site_Graph, root);
}

int get_period_of_route(site_p* site_Graph, route_p target_route_p){
	//Get period of the route ignoring hotel.
	int temp_period=0, j;
	if(target_route_p!=NULL){
		//Analyze this route linked list.
		temp_period=0;
		while(target_route_p!=NULL){
			//Take hotel into account later.
			j=index_vertex(site_Graph, target_route_p->name);
			temp_period+=(target_route_p->trans_info.travel_time) + (site_Graph[j]->stay_time);
			target_route_p=target_route_p->link;
		}
		return temp_period;
	}
	else
		return -1;
}
int get_cost_of_route(site_p* site_Graph, route_p target_route_p){
	//Get cost of the route ignoring hotel.
	int temp_cost=0, j;
	if(target_route_p!=NULL){
		//Analyze this route linked list.
		temp_cost=0;
		while(target_route_p!=NULL){
			//Take hotel into account later.
			j=index_vertex(site_Graph, target_route_p->name);
			temp_cost+=(target_route_p->trans_info.cost) + (site_Graph[j]->cost);
			target_route_p=target_route_p->link;
		}
		return temp_cost;
	}
	else
		return -1;
}

int get_dist_of_route(site_p* site_Graph, route_p target_route_p){
	//Get distance of the route ignoring hotel.
	int temp_dist=0, j;
	if(target_route_p!=NULL){
		//Analyze this route linked list.
		temp_dist=0;
		while(target_route_p!=NULL){
			//Take hotel into account later.
			j=index_vertex(site_Graph, target_route_p->name);
			temp_dist+=target_route_p->trans_info.dist;
			target_route_p=target_route_p->link;
		}
		return temp_dist;
	}
	else
		return -1;
}

void find_route(site_p* site_Graph, char* start, char* dest, int period, int budget){
	//Find routes from start to dest, considering period and budget.
	int visited[100]={0};
	int i=0, j;
	int temp_period, temp_budget, temp_dist;
	route_p temp_route_p;
	site_p temp_site_p;

	DFS_route(site_Graph, start, dest, visited);
	while(1){
		//Drop route that does not meet budget and period.
		if(travel_route[i]!=NULL){
			//Analyze this route linked list.
			temp_route_p=travel_route[i];
			temp_period=get_period_of_route(site_Graph, temp_route_p);
			temp_budget=get_cost_of_route(site_Graph, temp_route_p);
			temp_dist=get_dist_of_route(site_Graph, temp_route_p);
			if((temp_budget<=budget) && ((double)temp_period >= 0.6*period) && (temp_period <= period)){
				//Proper route.
			}
			else{
				//Improper route. Delete it.
				travel_route[i]=NULL;
				j=i;
				while(travel_route[j+1]!=NULL){
					travel_route[j]=travel_route[j+1];
					j++;
				}
			}
		}
		else
			break;
		i++;
	}
	//Now all the routes are valid.
}

int get_cheapest_route_index(site_p* site_Graph){
	//Call this function after calling 'find_route' function.
	//If this function returns -1, then something is wrong.
	int index=-1, temp_cost, cheapest_cost=0;
	
	for(int i=0;travel_route[i]!=NULL;i++){
		temp_cost=get_cost_of_route(site_Graph, travel_route[i]);
		if(temp_cost<cheapest_cost){
			//This route is the cheapest so far.
			cheapest_cost=temp_cost;
			index=i;
		}
	}
	return index;
}
int get_shortest_dist_route_index(site_p* site_Graph){
	//Call this function after calling 'find_route' function.
	//If this function returns -1, then something is wrong.
	int index=-1, temp_dist, cheapest_dist=0;
	
	for(int i=0;travel_route[i]!=NULL;i++){
		temp_dist=get_dist_of_route(site_Graph, travel_route[i]);
		if(temp_dist<cheapest_dist){
			//This route is the cheapest so far.
			cheapest_dist=temp_dist;
			index=i;
		}
	}
	return index;
}
int get_shortest_period_route_index(site_p* site_Graph){
	//Call this function after calling 'find_route' function.
	//If this function returns -1, then something is wrong.
	int index=-1, temp_period, cheapest_period=0;
	
	for(int i=0;travel_route[i]!=NULL;i++){
		temp_period=get_period_of_route(site_Graph, travel_route[i]);
		if(temp_period<cheapest_period){
			//This route is the cheapest so far.
			cheapest_period=temp_period;
			index=i;
		}
	}
	return index;
}

void print_route(site_p* site_Graph, route_p target_route_p){
	//Print a route.
	//If givien 'target_route_p' is NULL, this function prints nothing.
	route_p temp_route_p=target_route_p;
	site_p temp_site;
	while(temp_route_p!=NULL){
		temp_site=site_Graph[index_vertex(site_Graph, temp_route_p->name)];
		if(temp_route_p->trans_info.dist != 0){
			printf("Transportation:\n");
			printf("%3s Cost: %d\n", " ", temp_route_p->trans_info.cost);
			printf("%3s Distance: %d\n", " ", temp_route_p->trans_info.dist);
			printf("%3s Travel Time: %d\n", " ",temp_route_p->trans_info.travel_time);
			printf("\n");
		}
		printf("%s:\n", temp_site->name);
		printf("%3s Cost: %d\n", " ", temp_site->cost);
		printf("%3s Stay Time: %d\n", " ", temp_site->stay_time);
		printf("\n");
		temp_route_p=temp_route_p->link;
	}
}

void print_hotel(hotel_p target_hotel_p){
	//Print infomation of 'target_hotel_p'.
	printf("%s Cost: %d\n", target_hotel_p->name, target_hotel_p->cost);
}
void print_avail_hotels(hotel_p temp_hotel_p, int cost){
	//Prints every hotel in cheaper than 'cost'.
	//When you call this function in UI level, better set the 1st argument to site_p->head.

	if(temp_hotel_p != NULL){
		print_avail_hotels(temp_hotel_p->left, cost);
		if(temp_hotel_p->cost <= cost)
			print_hotel(temp_hotel_p);
		if(temp_hotel_p->cost < cost)
			print_avail_hotels(temp_hotel_p->right, cost);
	}
}

void make_reservation(reserve_p* T, char* id, int dist, int cost, int period, route_p route_){
	//Make reservation given infomation.
	Reserve_INSERT(T, id, dist, cost, period, route_);
}

/*
int delete_reservation(site_p* site_Graph, char* id){
	//Delete reservation given id.
	//Id is unique key, there cannot be multiple reservation with a id.
	//Return 1 if successful
	//Otherwise return 0. (eg. No reservation with the id)
	//Need a flag to know success or not!!!
	
}*/