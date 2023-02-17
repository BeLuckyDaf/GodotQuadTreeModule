#include "register_types.h"
#include "core/object/class_db.h"
#include "quadtree.h"
#include "quadtreenode.h"

void initialize_quadtree_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
    }
	ClassDB::register_class<QuadTree>();
	ClassDB::register_class<QuadTreeNode>();
}

void uninitialize_quadtree_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
    }
}
