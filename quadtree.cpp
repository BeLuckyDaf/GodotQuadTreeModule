#include "quadtree.h"
#include "core/os/memory.h"
#include "core/object/class_db.h"
#include "modules/quadtree/quadtreenode.h"

QuadTree::QuadTree() {}

QuadTree::~QuadTree() {}

void QuadTree::init_tree(const Rect2& bounds)
{
	root.instantiate();
	root->init_node(bounds, 0);
}

void QuadTree::insert_rect(const Rect2& bounds, const int value)
{
	root->insert_rect(bounds, value);
}

int QuadTree::state_at_point(const Vector2& point)
{
	return root->state_at_point(point);
}

Ref<QuadTreeNode> QuadTree::get_root()
{
	return root;
}

void QuadTree::set_root(Ref<QuadTreeNode> root)
{
	this->root = root;
}

void QuadTree::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("init_tree", "bounds"), &QuadTree::init_tree);
	ClassDB::bind_method(D_METHOD("insert_rect", "bounds", "value"), &QuadTree::insert_rect);
	ClassDB::bind_method(D_METHOD("state_at_point", "point"), &QuadTree::state_at_point);
	ClassDB::bind_method(D_METHOD("get_root"), &QuadTree::get_root);
	ClassDB::bind_method(D_METHOD("set_root", "root"), &QuadTree::set_root);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "root", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE), "set_root", "get_root");
}