#include "register_types.h"
#include "core/class_db.h"
#include "quadtree.h"
#include "quadtreenode.h"

void register_quadtree_types() {

	ClassDB::register_class<QuadTree>();
	ClassDB::register_class<QuadTreeNode>();
}

void unregister_quadtree_types() {
}
