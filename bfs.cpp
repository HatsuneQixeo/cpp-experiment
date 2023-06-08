#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Graph representation using an adjacency list
class Graph
{
private:
	int						V; // Number of vertices
	vector<vector<int> >	adj; // Adjacency list

public:
	Graph(int V)
	:	V(V),
		adj(V)
	{}

	// Function to add an edge between two vertices
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}

	// BFS pathfinding algorithm
	vector<int>	bfs(const int start, const int goal)
	{
		vector<bool>	visited(V, false); // Track visited nodes
		vector<int>		parent(V, -1); // Track parent nodes
		queue<int>		q; // Queue for BFS

		// Enqueue the starting node
		q.push(start);
		visited[start] = true;
		while (!q.empty())
		{
			const int	current = q.front();
			q.pop();

			// Check if the goal node is reached
			if (current == goal)
				break;
			// Process the current node or perform any necessary operations
			cout << "Visiting node: " << current << endl;
			// Enqueue neighboring nodes
			for (int neighbor : adj[current])
			{
				if (!visited[neighbor])
				{
					q.push(neighbor);
					visited[neighbor] = true;
					parent[neighbor] = current;
				}
			}
		}

		// Reconstruct the path from the goal node to the start node
		vector<int> path;
		if (parent[goal] != -1) {
			int node = goal;
			while (node != -1) {
				path.push_back(node);
				node = parent[node];
			}

			// Reverse the path to get it from start to goal
			reverse(path.begin(), path.end());
		}
		return path;
	}
};

int main()
{
	// Create a graph with 6 nodes
	Graph graph(6);

	// Add edges between nodes
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 3);
	graph.addEdge(1, 4);
	graph.addEdge(2, 4);
	graph.addEdge(3, 5);
	graph.addEdge(4, 5);

	// Perform BFS pathfinding from node 0 to node 5
	vector<int> path = graph.bfs(0, 5);

	// Print the path
	cout << "Path: ";
	for (int node : path) {
		cout << node << " ";
	}
	cout << endl;

	return 0;
}
