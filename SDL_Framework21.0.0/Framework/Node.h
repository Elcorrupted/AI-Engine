#ifndef NODE_H
#define NODE_H

#include "VMath.h"

using namespace MATH;

class Node {
private:
	int label;
	Vec3 pos; 
	bool wall;

public:
	Node();
	Node(int label_);
	Node(int label_, Vec3 pos_);

	inline bool operator== (const Node &rhs) { return (label == rhs.label); }
	inline int GetLabel() { return label; }
	inline Vec3 GetPos() { return pos; }

	inline bool GetWall() { return wall; }
	inline void SetWall(bool wall_) { wall = wall_; }
};
#endif // !NODE_H

