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

	// functions

protected:
	static void _bind_methods();

public:
	void insert_rect(const Rect2i& bounds, const int value);
	int state_at_point(const Vector2i& point) const;

	static QuadTree* create_tree(const Rect2i& bounds);
	QuadTree();
};

#endif	// QUADTREE_H