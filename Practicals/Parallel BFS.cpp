#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void parallel_bfs(vector<vector<int> > & graph , int start_node){
	int n = graph.size();
	vector<bool> visited(n,false);
	
	vector<int> frontier;
	frontier.push_back(start_node);
	visited[start_node] = true;
	
	while(!frontier.empty()){
		vector<int> frontier_next;
		
		#pragma omp parallel
		{
			vector<int> local_next;
			
			#pragma omp for nowait
			for(int i = 0; i < frontier.size() ;i++){
				int u = frontier[i];
				cout<<"\nVisited : "<<u<<" by thread : "<<omp_get_thread_num();
				
				for(int idx = 0; idx < graph[u].size(); idx++) {
    				int v = graph[u][idx];
    				if (!visited[v]) {
        				#pragma omp critical
        				{
           					if (!visited[v]) {
                				visited[v] = true;
                				local_next.push_back(v); 
            				}
        				}
    				}
				}
			}
			
			# pragma omp critical
			frontier_next.insert(frontier_next.end(),local_next.begin(),local_next.end());
		}
		frontier = frontier_next;
	} 
}

int main(){
	vector<vector<int> > graph(6); 

	graph[0].push_back(1);
	graph[0].push_back(2);
	
	graph[1].push_back(0);
	graph[1].push_back(3);
	graph[1].push_back(4);
	
	graph[2].push_back(0);
	graph[2].push_back(4);
	
	graph[3].push_back(1);
	graph[3].push_back(5);
	
	graph[4].push_back(1);
	graph[4].push_back(2);
	graph[4].push_back(5);
	
	graph[5].push_back(3);
	graph[5].push_back(4);
	
	cout<<"Parallel BFS starting from node 0 : ";
	parallel_bfs(graph,0);
	
	return 0;
}
