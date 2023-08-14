#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <sstream>
#include <queue>

using namespace std;

// define class of graphVertice
class Vertex {
public:
	int id;
	std::vector<int> neighbors;  //store adjacent Vertex as int
	Vertex(int _id);
};

//set vertex
Vertex::Vertex(int _id) {
	id = _id;
}

//define graph
class Graph {
public:
	std::vector<Vertex> vertices;   //search Vertex by index(int)
	void addVertex(int id);
	void addEdge(int from, int to);
	std::vector<int> getAdjacent(int id);
	std::vector<std::vector<int>> unweightedEdges();
};

//add vertex into graph
void Graph::addVertex(int id) {
	vertices.emplace_back(id);
}

//add edge into graph
void Graph::addEdge(int from, int to) {
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].id == from) {
			vertices[i].neighbors.push_back(to);
		}
	}	
}

//output all neighbors of this vertex
std::vector<int> Graph::getAdjacent(int id) {
	return vertices[id].neighbors;
}

//output all edges of graph, do not add weight. for example: {{0,0,1},{0,1,2},{0,2,3}......}
std::vector<std::vector<int>> Graph::unweightedEdges() {
	std::vector<std::vector<int>> edges;
	for (int i = 0; i < vertices.size(); i++) {
		int from = vertices[i].id;

		for (int j = 0; j < vertices[i].neighbors.size(); j++) {
			int to = vertices[i].neighbors[j];
			
			int weight = 0;  // Just take up a position first and will replace with the actual weight out of this function

			bool foundElement = false;
			for (const auto& vec : edges) {
				if ((from == vec[1] && to == vec[2]) || (from == vec[2] && to == vec[1])) {
					foundElement = true;
				}
			}
			if (foundElement) {		//if from and to in same set
				continue;
			}
			else {
				std::vector<int> edge = { weight, from, to };
				edges.push_back(edge);
			}
			
		}
	}
	return edges;
}

// convert country string to digital matrix
std::vector<std::vector<int>> strToList(std::string country) {
	std::vector<std::vector<int>> list;
	std::istringstream ins(country);
	std::string row;
	while (std::getline(ins, row, ',')) {
		std::vector<int> list_part;
		for (char n : row) {
			list_part.push_back(n - '0');
		}
		list.push_back(list_part);
	}
	return list;
}

//set graph, add vertices and edges
Graph createGraph(string country, std::vector<int> country_set) {
	std::vector<std::vector<int>> country_list = strToList(country);
	Graph graph;
	int country_num = country_set.size();
	for (int i = 0; i < country_num; i++) {
		graph.addVertex(country_set[i]);
	}
	for (int m = 0; m < country_num; m++) {
		for (int n = 0; n < country_num; n++) {
			if (country_list[country_set[m]][country_set[n]] == 1) {
				graph.addEdge(country_set[m], country_set[n]);
			}
		}
	}
	return graph;
}

// calculate all sets of connected countries
std::vector<std::vector<int>> countrySets(string country) {
	std::vector<std::vector<int>> country_list = strToList(country);
	int country_num = country_list.size();
	std::vector<std::vector<int>> country_sets;
	std::vector<int> unvisited_country;
	for (int i = 0; i < country_num; i++) {
		unvisited_country.push_back(i);
	}
	Graph graph = createGraph(country, unvisited_country);

	while (!unvisited_country.empty()) {
		int first = unvisited_country[0];
		unvisited_country.erase(unvisited_country.begin());
		std::vector<int> queue;
		queue.push_back(first);
		std::vector<int> connect_country;
		while (!queue.empty()) {
			int element = queue[0];
			queue.erase(queue.begin());
			connect_country.push_back(element);

			std::vector<int> neighbors = graph.getAdjacent(element);
			for (auto i = neighbors.begin(); i != neighbors.end();) {
				int id = *i;
				if (std::find(unvisited_country.begin(), unvisited_country.end(), id) != unvisited_country.end()) {
					queue.push_back(id);
					unvisited_country.erase(std::find(unvisited_country.begin(), unvisited_country.end(), id));
					i = neighbors.erase(i);
				}
				else {
					++i;
				}
			}
		}
		country_sets.push_back(connect_country);
	}
	return country_sets;
}

// convert cost string to digital matrix
std::vector<std::vector<int>> toCostList(std::string cost) {
	std::vector<std::vector<int>> list;
	std::istringstream ins(cost);
	std::string row;
	while (std::getline(ins, row, ',')) {
		std::vector<int> list_part;
		for (char n : row) {
			int temp = n - 'A';
			if (temp <= 25) {
				list_part.push_back(temp);
			}
			else {
				list_part.push_back(temp-6);
			}
		}
		list.push_back(list_part);
	}
	return list;
}

//insert two elements of edge to sets, if them have be connected, add the cost
void insetElement(std::vector<int>& edge, std::vector<std::vector<int>>& sets, int& money) {
	int element1_exist = -1;
	int element2_exist = -1;
	int element1 = edge[1];
	int element2 = edge[2];
	for (int i = 0; i < sets.size(); i++) {
		std::vector<int> vec = sets[i];
		for (int j = 0; j < vec.size(); j++) {
			if (element1 == vec[j]) {
				element1_exist = i;
			}
			if (element2 == vec[j]) {
				element2_exist = i;
			}
		}
	}
	if (element1_exist == -1 && element2_exist == -1) {
		std::vector<int> temp = { element1,element2 };
		sets.push_back(temp);
	}
	else if (element1_exist == -1) {
		sets[element2_exist].push_back(element1);
	}
	else if (element2_exist == -1) {
		sets[element1_exist].push_back(element2);
	}
	else if (element1_exist == element2_exist) {
		money = money + edge[0];
	}
	else {
		sets[element1_exist].insert(sets[element1_exist].end(), sets[element2_exist].begin(), sets[element2_exist].end());
		sets.erase(sets.begin() + element2_exist);
	}
}

//compare the first element of vector, AKA weight, from large to small
bool compareLargeToSmall(const std::vector<int>& v1, const std::vector<int>& v2) {
	return v1[0] > v2[0]; 
}

//compare the first element of vector, AKA weight, from small to large
bool compareSmallToLarge(const std::vector<int>& v1, const std::vector<int>& v2) {
	return v1[0] < v2[0];
}

//calculate least cost of each set of countries: keep all weighted edges unless forming a cycle
int destroyPartCost(std::vector<int> country_set, std::vector<std::vector<int>> cost, string country) {
	Graph graph = createGraph(country, country_set);
	std::vector<std::vector<int>> edges = graph.unweightedEdges();
	for (int i = 0; i < edges.size(); i++) {
		std::vector<int> temp = edges[i];
		edges[i][0] = cost[temp[1]][temp[2]];
	}
	std::sort(edges.begin(), edges.end(), compareLargeToSmall);
	int money = 0;
	std::vector<std::vector<int>> sets;
	for (int i = 0; i < edges.size(); i++) {
		std::vector<int> edge = edges[i];
		insetElement(edge, sets, money);

	}
	return money;
}

//calculate total cost of destroy, and output
int destroyTotalCost(string country, string destory) {
	std::vector<std::vector<int>> country_sets = countrySets(country);
	std::vector<std::vector<int>> cost = toCostList(destory);
	int total_cost = 0;
	for (int i = 0; i < country_sets.size(); i++) {
		std::vector<int> set = country_sets[i];
		total_cost = total_cost + destroyPartCost(set, cost, country);
	}
	return total_cost;
}

//output total cost for building
int buildTotalCost(string country, string build) {
	std::vector<std::vector<int>> country_sets = countrySets(country);
	std::vector<std::vector<int>> cost = toCostList(build);   
	std::vector<std::vector<int>> sorted_edges;                       //for example: {{1,2,3}......}
	for (int i = 0; i < cost.size()-1; i++) {
		std::vector<int> temp = {};
		for (int j = i + 1; j < cost.size(); j++) {
			temp = { cost[i][j], i, j };
			sorted_edges.push_back(temp);
		}
	}
	std::sort(sorted_edges.begin(), sorted_edges.end(), compareSmallToLarge);
	int total_cost = 0;
	//traverse cost matrix, from smallest weight edge to largest weight edge
	while (country_sets.size() > 1) {
		std::vector<int> edge = sorted_edges.front();
		sorted_edges.erase(sorted_edges.begin());
		int element1_exist = -1;
		int element2_exist = -1;
		int element1 = edge[1];
		int element2 = edge[2];
		for (int i = 0; i < country_sets.size(); i++) {
			for (int n : country_sets[i]) {
				if (n == element1) {
					element1_exist = i;
				}
				if (n == element2) {
					element2_exist = i;
				}
			}
		}
		if (element1_exist == element2_exist) {
			continue;
		}
		else {
			country_sets[element1_exist].insert(country_sets[element1_exist].end(), country_sets[element2_exist].begin(), country_sets[element2_exist].end());
			country_sets.erase(country_sets.begin() + element2_exist);
			total_cost = total_cost + edge[0];
		}
	}
	return total_cost;
}

int main() {
	string country, build, destroy;
	cin >> country >> build >> destroy;
	int destroy_cost = destroyTotalCost(country, destroy);
	int build_cost = buildTotalCost(country, build);
	int total_cost = destroy_cost + build_cost;
	cout << total_cost;
}
