#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

const int INF = 9999;

void dijkstra_parallel(vector<vector<int> > & graph ,int src ,int n){ 
	vector <int> dist (n, INF);
	vector <bool> visited (n, false);
	
	dist[src] = 0;
	
	for(int count = 0; count < n ; count++){
		int u = -1;
		int min_dist = INF;
		
		for(int i = 0 ; i < n ; i++){
			if(!visited[i] && dist[i] < min_dist){
				min_dist = dist[i];
				u = i;
			}
		}
		
		if(u == -1) break;
		
		visited[u] = true;
		
		#pragma omp parallel for 
		for(int v = 0; v < n; v++){
			if(!visited[v] && graph[u][v] && dist[u]!=INF){
				if(dist[u] + graph[u][v] < dist[v]){
					dist[v] = dist[u] + graph[u][v];
				}
			}
		}
	}
	
	#pragma omp parallel for
	for(int i = 0; i < n; i++){
		cout<<"Distance from source "<<src<<" to vertex "<<i<<" : "<<dist[i]<<endl;
	}
}

int main() {
	int n;
	cout<<"Enter the number of vertices : ";cin>>n;
    vector<vector<int> > graph(n, vector<int>(n));
    
    cout<<"Enter the weights in a single line seperated by space "<<endl;
    for(int i=0;i<n;i++){
    	cout<<"Enter the wieght of edges connected to vertex "<<i<<" : ";
    	for(int j=0;j<n;j++){
    		cin>>graph[i][j];
		}
		cout<<endl;
	}
	
	int src;
	cout<<"Enter source : ";cin>>src;
    
    dijkstra_parallel(graph ,src ,n);
    
    return 0;
}
