#ifndef GRAPH_H
#define GRAPH_H

#include "NodePriority.h"
#include "Connection.h"
#include <deque>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include "Tile.h"
#include "Mouse.h"
#include "Trap.h"

/*enum Category {
	closed, open, unvisited
};

struct NodeInfo {
	Node node;
	Connection connection[4];
	Category category = unvisited;
};*/

class Graph {
private:
	//Smooths out the path for A_StarPath
	std::vector<Node> SmoothPath(std::vector<Node> inputPath);
	//Used to create an estimated distance from the current node to the goal for use in the A_StarPath
	float Heuristic(Node node, Node goal);
	//Returns an array containing all neighbouring nodes
	std::list<Node> GetNeighbours(Node currentNode);

	//Creates a 2d matrix of floats using vectors for holding the weights between nodes. 
	//nodes[x][y] is the weight going from x to y. nodes[y][x] is the weight going from y to x
	std::vector<std::vector<float>> nodeConnections;

	//Holds a list of the all the nodes that existed in the scene upon creation of the graph
	std::vector<Node> sceneNodes;

public:
	//On creation will need the amount of nodes to add for both rows and columns
	//those will be used for the nodes vector and add a weight of 1 to every node
	//the removeconnection/changeweight will be used to change connections
	Graph(int numNodes, int nodesInColumn, std::vector<Tile*> tileList_);
	~Graph();

	//Finding shortest path from start node to goal node
	std::vector<Node> A_StarPath(Node start, Node goal);

	//To find out what node is attached to the given label
	Node FindNode(int label_);
	//To find out what node is closest to given position
	Node FindNode(Vec3 pos_);

	//For removing/adding/changing weight of connections for/between specific nodes
	void RemoveConnection(Node *node_);
	void ChangeWeight(int currentNode, int toNode, float weight);
	void DirectionalWeightChange(int currentNode, int toNode, float weight);
};
#endif // !GRAPH_H