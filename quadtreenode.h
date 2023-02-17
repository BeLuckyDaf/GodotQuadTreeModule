#ifndef QUADTREENODE_H
#define QUADTREENODE_H
#include "core/object/ref_counted.h"
#include "core/math/rect2.h"
#include "core/math/vector2.h"

class QuadTreeNode: public RefCounted
{
	GDCLASS(QuadTreeNode, RefCounted);

private:

protected:
		static void _bind_methods();

public:
	Rect2i bounds;
	int state;

	QuadTreeNode* parent;
	Ref<QuadTreeNode> child_nw;
	Ref<QuadTreeNode> child_ne;
	Ref<QuadTreeNode> child_sw;
	Ref<QuadTreeNode> child_se;

	Ref<QuadTreeNode> get_nw();
	Ref<QuadTreeNode> get_ne();
	Ref<QuadTreeNode> get_sw();
	Ref<QuadTreeNode> get_se();

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