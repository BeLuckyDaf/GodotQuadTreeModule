#ifndef QUADTREE_H
#define QUADTREE_H
#include "quadtreenode.h"
#include "core/reference.h"
#include "core/math/rect2.h"
#include "core/math/vector2.h"

class QuadTree: public Reference
{
	GDCLASS(QuadTree, Reference);

private:
	QuadTreeNode* root;

protected:
	static void _bind_methods();

public:
	void insert_rect(const Rect2& bounds, const int value);
	int state_at_point(const Vector2& point);
	QuadTreeNode* get_root();
	void set_root(Object* root);

	void init_tree(const Rect2& bounds);
	QuadTree();
	~QuadTree();
};

#endif	// QUADTREE_H