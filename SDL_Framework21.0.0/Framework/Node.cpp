#include "Node.h"

Node::Node() {
	label = 0;
	pos = Vec3();
	wall = false;
}

Node::Node(int label_) {
	label = label_;
	pos = Vec3();
	wall = false;
}

Node::Node(int label_, Vec3 pos_) {
	label = label_;
	pos = pos_;
	wall = false;
}
