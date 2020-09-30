#ifndef QUADTREENODE_H
#define QUADTREENODE_H
#include "core/reference.h"
#include "core/math/rect2.h"
#include "core/math/vector2.h"

class QuadTreeNode: public Reference
{
	GDCLASS(QuadTreeNode, Reference);

private:

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

	QuadTreeNode* get_nw();
	QuadTreeNode* get_ne();
	QuadTreeNode* get_sw();
	QuadTreeNode* get_se();

	void split();
	void close(const int state);
	void insert_rect(const Rect2& target, const int value);
	int state_at_point(const Vector2& point);
	int get_state();
	Rect2 get_bounds();
	void set_state(const int state);
	void set_bounds(const Rect2& bounds);

	void init_node(const Rect2& bounds, const int state);
	QuadTreeNode();
	~QuadTreeNode();
};

#endif	// QUADTREENODE_H