#include "quadtree.h"
#include "core/os/memory.h"

QuadTree::QuadTree() 
{
	root = NULL;
}

QuadTree::~QuadTree() 
{
	if (root) memdelete(root);
}

void QuadTree::init_tree(const Rect2& bounds)
{
	root = memnew(QuadTreeNode);
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

QuadTreeNode* QuadTree::get_root()
{
	return root;
}

void QuadTree::set_root(Object* root)
{
	if (this->root && this->root != root) memdelete(this->root);
	this->root = static_cast<QuadTreeNode*>(root);
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