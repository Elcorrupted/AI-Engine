#include "Graph.h"
#include "VMath.h"

using namespace MATH;

Graph::Graph(int numNodes, int nodesInColumn, std::vector<Tile*> tileList_){
	//Add all the nodes in the tileList into a list for use by the graph
	for (auto tile : tileList_) {
		sceneNodes.push_back(tile->GetNode());
	}

	int nodesInRow = numNodes / nodesInColumn;
	std::vector<float> zeroConn(numNodes, 0.0f);

	//For zeroing out all the connections
	nodeConnections.resize(numNodes);
	for (int k = 0; k < numNodes; k++) {
		nodeConnections[k].resize(numNodes);
		nodeConnections[k] = zeroConn;
	}

	//For each i the loop should only go through twice max. 
	//Once for a connection to the node on the right, another for underneath.
	for (int i = 0; i < numNodes - 1; i++) {
		for (int j = 0; j < 2 - 1; j++) {
			if ((i + 1) % nodesInRow != 0 && i + nodesInRow < numNodes) {
				//ChangeWeight changes weight for nodeConnection[i][i+1] and nodeConnection[i+1][i]
				//If you only want weight in one direction use DirectionalWeightChange
				ChangeWeight(i, i + 1, 1.0f);
				ChangeWeight(i, i + nodesInRow, 1.0f);
			}
			else if (i + nodesInRow >= numNodes) {
				ChangeWeight(i, i + 1, 1.0f);
			}
			else if ((i + 1) % nodesInRow == 0) {
				ChangeWeight(i, i + nodesInRow, 1.0f);
			}
		}
	}
}

Graph::~Graph(){}

struct PriorityComparison {
	bool operator() (NodePriority& lhs, NodePriority& rhs) {
		return lhs.priority > rhs.priority;
	}
};

std::vector<Node> Graph::A_StarPath(Node start, Node goal) {
	std::priority_queue<NodePriority, std::deque<NodePriority>, PriorityComparison> frontier;

	NodePriority* currentNodePriority;
	currentNodePriority = new NodePriority(&start, 0.0f);
	frontier.push(*currentNodePriority);

	//For holding the extracted optimal path
	std::vector<Node> path;
	//Contains the optimal path (needs extraction)
	std::vector<Node> cameFrom;
	cameFrom.resize(sceneNodes.size());

	std::map<int, float> costSoFar;
	costSoFar[start.GetLabel()] = 0;

	while (!frontier.empty()) {
		Node current = *frontier.top().node;


		//Removing the searched node from the frontier
		frontier.pop();
		float newCost;

		/*if (current == trap)
		{
			printf("Trap reached\n");
		}*/

		if (current == goal) {
			printf("Found goal\n");

			//Extracts the optimal path from the cameFrom vector. cameFrom[goal.label()] holds the node that is before it in the path.
			//Retraces from the goal.label() position in the vector back to the start.label() position in the vector.
			int i = goal.GetLabel();
			path.push_back(goal);
			while (cameFrom[i].GetLabel() != start.GetLabel()) {
				//For tracking the path that the mouse wants to take
				path.insert(path.begin(), cameFrom[i]);
				i = cameFrom[i].GetLabel();
			}
			//Inserts the start node into the solution path
			path.insert(path.begin(), cameFrom[i]);
			
			//Smooths out the solution path, so the AI doesn't stop at every node only at corners/goal.
			return SmoothPath(path);
		}

		//Loops through each Node in the array returned by GetNeighbours 
		for (auto next : Graph::GetNeighbours(current)) {
			newCost = costSoFar[current.GetLabel()] + nodeConnections[current.GetLabel()][next.GetLabel()];
			if (costSoFar[next.GetLabel()] == 0.0f || newCost < costSoFar[next.GetLabel()]) {
				costSoFar[next.GetLabel()] = newCost;
				float priority = newCost + Heuristic(next, goal);
				//Needed to use the sceneNodes to get the label to add to the priority queue because the "next" variable address is used for every item in the list returned from GetNeighbours
				//Therefore it all nodes added to the priority queue would have the most recent accessed node.
				frontier.push(NodePriority(&sceneNodes[next.GetLabel()], priority));
				cameFrom[next.GetLabel()] = current;
			}
		}
	}
	printf("Could not find the goal\n");
	return cameFrom;
}

//Smooths path out
std::vector<Node> Graph::SmoothPath(std::vector<Node> inputPath) {
	if (inputPath.size() <= 2) {
		return inputPath;
	}

	//Holds the output path. Give it the first node in the inputPath.
	//Node trapNode = FindNode(trap->getPos());
	//inputPath[1] = trapNode;
	std::vector<Node> outputPath;
	outputPath.push_back(inputPath[0]);
	//outputPath.push_back(inputPath[1]);

	//Used for tracking which nodes are being tested. Starts with the first node and the second node in the path solution
	int toPt = 2;
	int fromPt = 0;

	//Starts at two spaces away from start and checks to see if the node pos.x or pos.y is the same as the starts pos.x or pos.y
	while (toPt < inputPath.size()) {
		/*if ((inputPath[fromPt].GetPos().x + 1.0f - trapNode.GetPos().x) <= 0.5f)
		{
			printf("trap reached\n");
		}*/
		//Check to see if moving in a straight line along x-axis
		if (inputPath[fromPt].GetPos().x == inputPath[toPt].GetPos().x) {
			toPt++;
		}
		//Check to see if moving in a straight line along y-axis
		else if (inputPath[fromPt].GetPos().y == inputPath[toPt].GetPos().y) {
			toPt++;
		}
		//Not moving in straight line so move the test node to the corner node
		else {
			outputPath.push_back(inputPath[toPt - 1]);
			fromPt = toPt - 1;
			toPt++;
		}
	}
	outputPath.push_back(inputPath[toPt - 1]);
	return outputPath;
}

float Graph::Heuristic(Node node, Node goal_) {
	//D is the smallest weight for a connection. Currently 1.0f
	float D = 1.0f;

	float dx = abs(node.GetPos().x - goal_.GetPos().x);
	float dy = abs(node.GetPos().y - goal_.GetPos().y);

	return D * (dx + dy);
}

//Used to find a node in the sceneNodes variable using the label passed in
Node Graph::FindNode(int label_) {
	for (Node node : sceneNodes) {
		if (node.GetLabel() == label_)
		return node;
	}
	printf("Could not find a node that has the same label\n");
	return 0;
}

//Go through Tile list and find tile.node with the closest pos to the given pos
//Primarily used for finding a node closest to the character(mouse) and the goal(cheese)
Node Graph::FindNode(Vec3 pos_) {
	float shortDist = FLT_MAX;
	float testDist = 0;

	Node closestNode;

	for (Node node : sceneNodes) {
		if (node == sceneNodes.front()) {
			shortDist = abs(node.GetPos().x - pos_.x) + abs(node.GetPos().y - pos_.y);
			closestNode = node;
		}
		else
		{
			testDist = abs(node.GetPos().x - pos_.x) + abs(node.GetPos().y - pos_.y);
			if (testDist < shortDist) {
				shortDist = testDist;
				closestNode = node;
			}
		}
	}
	return closestNode;
}

//Returns all nodes that are neighbours with the passed in node
std::list<Node> Graph::GetNeighbours(Node node_) {
	std::list<Node> result = {};
	std::vector<float> toNodes = nodeConnections[node_.GetLabel()];
	for (int j = 0; j < toNodes.size(); j++) {
		if (nodeConnections[node_.GetLabel()][j] > 0.0f) {
			result.push_back(FindNode(j));
		}
	}
	return result;
}

//Used to sever all connections to the (wall) node (makes weight really high, so later you can still find neighbours)
void Graph::RemoveConnection(Node* node_) {
	for (auto &next : GetNeighbours(node_->GetLabel())) {
		ChangeWeight(node_->GetLabel(), next.GetLabel(), FLT_MAX);
	}
	node_->SetWall(true);
}

//Used to change/add a connection between two nodes both ways
void Graph::ChangeWeight(int currentNode, int toNode, float weight) {
	nodeConnections[currentNode][toNode] = weight;
	nodeConnections[toNode][currentNode] = weight;
}

//Same as change weight, but only from currentNode to the toNode
void Graph::DirectionalWeightChange(int currentNode, int toNode, float weight) {
	nodeConnections[currentNode][toNode] = weight;
}