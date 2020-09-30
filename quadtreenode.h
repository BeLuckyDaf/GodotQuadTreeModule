#ifndef QUADTREENODE_H
#define QUADTREENODE_H
#include "core/reference.h"
#include "core/math/rect2.h"
#include "core/math/vector2.h"

class QuadTreeNode: public Reference
{
	GDCLASS(QuadTreeNode, Reference);

private:
	// variables

	// functions

protected:
		static void _bind_methods();

public:
	Rect2i bounds;
	int state;

	QuadTreeNode* parent;
	QuadTreeNode* child_nw;
	QuadTreeNode* child_ne;
	QuadTreeNode* child_sw;
	QuadTreeNode* child_se;

	void split();
	void close(const int state);
	void insert_rect(const Rect2i& target, const int value);
	int state_at_point(const Vector2i& point);
	
	QuadTreeNode* create_node(const QuadTreeNode* parent, const Rect2i& bounds, const int state);
	QuadTreeNode();
};

#endif	// QUADTREENODE_H