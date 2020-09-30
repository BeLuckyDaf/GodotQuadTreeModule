#include "quadtree.h"

static QuadTree::create_tree(const Rect2i& bounds)
{
	QuadTree* tree = new QuadTree();
	tree->root = QuadTreeNode::create_node(NULL, bounds, 0);
	return tree;
}

QuadTree::QuadTree() 
{
}

void QuadTree::insert_rect(const Rect2i& bounds, const int value)
{
	root->insert_rect(bounds, value);
}

int QuadTree::state_at_point(const Vector2i& point) const
{
	return root->state_at_point(point);
}

void QuadTree::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("create_tree", "bounds"), &QuadTree::create_tree);
	ClassDB::bind_method(D_METHOD("insert_rect", "bounds", "value"), &QuadTree::insert_rect);
	ClassDB::bind_method(D_METHOD("state_at_point", "point"), &QuadTree::state_at_point);
}