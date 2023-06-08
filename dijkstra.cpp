#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

// Graph representation using an adjacency list
class Graph {
public:
	typedef pair<int, int>	Edge;
	typedef vector<Edge>	Connections;
private:
	int V; // Number of vertices
	vector<Connections> adj; // Adjacency list

public:
	Graph(const int V) : V(V), adj(V) {}

	// Function to add an edge between two vertices with a given weight
	void addEdge(const int v, const int w, const int weight)
	{
		adj[v].push_back(make_pair(w, weight));
		adj[w].push_back(make_pair(v, weight));
	}

	// Dijkstra's algorithm to find the most efficient way to connect to multiple nodes
	vector<int> dijkstra(const int start, vector<int> targets)
	{
		vector<int>		dist(this->V, numeric_limits<int>::max()); // Shortest distances from start to all nodes
		vector<int>		prev(this->V, -1); // Previous node in the shortest path
		priority_queue<Edge, Connections, greater<Edge> >	pq; // Priority queue for Dijkstra's algorithm

		dist[start] = 0;
		pq.push(make_pair(0, start));
		while (!pq.empty())
		{
			const int	u = pq.top().second;
			pq.pop();

			// Skip already visited nodes
			if (dist[u] == numeric_limits<int>::max())
				continue;

			// Check if the current node is one of the targets
			const auto	it = find(targets.begin(), targets.end(), u);
			if (it != targets.end()) {
				// Remove the target from the list of targets
				targets.erase(it);
				if (targets.empty()) {
					// All targets have been reached, stop the algorithm
					break;
				}
			}

			for (const auto& neighbor : adj[u])
			{
				const int	v = neighbor.first;
				const int	weight = neighbor.second;

				if (dist[u] + weight < dist[v])
				{
					dist[v] = dist[u] + weight;
					prev[v] = u;
					pq.push(make_pair(dist[v], v));
				}
			}
		}
		return prev;
	}

	// Reconstruct the path from start to target
	vector<int> reconstructPath(int start, int target, const vector<int>& prev)
	{
		vector<int>	path;
		int			node = target;

		while (node != -1)
		{
			path.push_back(node);
			node = prev[node];
		}
		if (path.back() != start)
			return (std::vector<int>());
		reverse(path.begin(), path.end());
		return (path);
	}
};

int main()
{
	// Create a graph with 6 nodes
	Graph	graph(9);

	// Add edges between nodes with weights
	graph.addEdge(0, 1, 1);
	graph.addEdge(0, 2, 1);
	graph.addEdge(1, 3, 1);
	graph.addEdge(1, 4, 1);
	graph.addEdge(2, 4, 1);
	graph.addEdge(3, 5, 1);
	graph.addEdge(4, 5, 1);

	// Set the start node and target nodes
	const int	start = 0;
	vector<int>	targets;
	
	targets.push_back(3);
	targets.push_back(5);
	targets.push_back(2);
	targets.push_back(4);

	// Perform Dijkstra's algorithm
	vector<int>	prev = graph.dijkstra(start, targets);

	// Reconstruct the paths to the target nodes
	for (int target : targets)
	{
		vector<int>	path = graph.reconstructPath(start, target, prev);

		// Print the path
		cout << "Path to target " << target << ": ";
		for (int node : path)
			cout << node << " ";
		cout << endl;
	}
}
