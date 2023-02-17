#include "quadtreenode.h"
#include "core/os/memory.h"
#include "core/object/class_db.h"
#include "core/string/print_string.h"
#include "editor/editor_log.h"

void QuadTreeNode::init_node(const Rect2& bounds, const int state)
{
	this->bounds = Rect2i(bounds);
	this->state = state;
}

QuadTreeNode::QuadTreeNode() 
{
	state = 0;
}

QuadTreeNode::~QuadTreeNode() {}

void QuadTreeNode::split()
{
	if (!child_nw.is_valid()) {
		child_nw.instantiate();
	}
	if (!child_ne.is_valid()) {
		child_ne.instantiate();
	}
	if (!child_sw.is_valid()) {
		child_sw.instantiate();
	}
	if (!child_se.is_valid()) {
		child_se.instantiate();
	}

	child_nw->parent = this;
	child_ne->parent = this;
	child_sw->parent = this;
	child_se->parent = this;

	child_nw->init_node(Rect2(
		bounds.position.x,
		bounds.position.y,
		bounds.size.width/2,
		bounds.size.height/2),
		state);
	child_ne->init_node(Rect2(
		bounds.position.x + bounds.size.x/2,
		bounds.position.y,
		bounds.size.width/2,
		bounds.size.height/2),
		state);
	child_sw->init_node(Rect2(
		bounds.position.x,
		bounds.position.y + bounds.size.y/2,
		bounds.size.width/2,
		bounds.size.height/2),
		state);
	child_se->init_node(Rect2(
		bounds.position.x + bounds.size.x/2,
		bounds.position.y + bounds.size.y/2,
		bounds.size.width/2,
		bounds.size.height/2),
		state);
	state = -1;
}

void QuadTreeNode::close(const int state)
{
	this->state = state;
	if (child_ne.is_valid()) {
		child_ne->close(state);
		child_ne.unref();
	}
	if (child_nw.is_valid()) {
		child_nw->close(state);
		child_nw.unref();
	}
	if (child_se.is_valid()) {
		child_se->close(state);
		child_se.unref();
	}
	if (child_sw.is_valid()) {
		child_sw->close(state);
		child_sw.unref();
	}
}

void QuadTreeNode::insert_rect(const Rect2& target, const int value)
{
	Rect2i target_i = Rect2i(target);
	if (target_i.encloses(bounds))
	{
		close(value);
	}
	else if (target.intersects(bounds))
	{
		if (state != -1) split();
		child_nw->insert_rect(target_i, value);
		child_ne->insert_rect(target_i, value);
		child_sw->insert_rect(target_i, value);
		child_se->insert_rect(target_i, value);
		if (child_ne->state != -1 &&
			child_ne->state == child_nw->state &&
			child_ne->state == child_sw->state &&
			child_ne->state == child_se->state)
		{
			close(child_ne->state);
		}
	}
}

int QuadTreeNode::state_at_point(const Vector2& point)
{
	if (state != -1)
	{
		return state;
	}
	else if (child_nw->bounds.has_point(point))
	{
		return child_nw->state_at_point(point);
	}
	else if (child_ne->bounds.has_point(point))
	{
		return child_ne->state_at_point(point);
	}
	else if (child_sw->bounds.has_point(point))
	{
		return child_sw->state_at_point(point);
	}
	else if (child_se->bounds.has_point(point))
	{
		return child_se->state_at_point(point);
	}
	return -1;
}

int QuadTreeNode::get_state()
{
	return state;
}

void QuadTreeNode::set_state(const int state)
{
	this->state = state; 
}

Rect2 QuadTreeNode::get_bounds()
{
	return Rect2(bounds);
}

void QuadTreeNode::set_bounds(const Rect2& bounds)
{
	this->bounds = bounds; 
}

Ref<QuadTreeNode> QuadTreeNode::get_nw()
{
	return child_nw;
}

Ref<QuadTreeNode> QuadTreeNode::get_ne()
{
	return child_ne;
}

Ref<QuadTreeNode> QuadTreeNode::get_sw()
{
	return child_sw;
}

Ref<QuadTreeNode> QuadTreeNode::get_se()
{
	return child_se;
}

void QuadTreeNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("init_node", "bounds", "state"), &QuadTreeNode::init_node);
	ClassDB::bind_method(D_METHOD("split"), &QuadTreeNode::split);
	ClassDB::bind_method(D_METHOD("close", "state"), &QuadTreeNode::close);
	ClassDB::bind_method(D_METHOD("insert_rect", "target", "value"), &QuadTreeNode::insert_rect);
	ClassDB::bind_method(D_METHOD("state_at_point", "point"), &QuadTreeNode::state_at_point);
	ClassDB::bind_method(D_METHOD("get_state"), &QuadTreeNode::get_state);
	ClassDB::bind_method(D_METHOD("get_bounds"), &QuadTreeNode::get_bounds);
	ClassDB::bind_method(D_METHOD("set_state", "state"), &QuadTreeNode::set_state);
	ClassDB::bind_method(D_METHOD("set_bounds", "bounds"), &QuadTreeNode::set_bounds);
	ClassDB::bind_method(D_METHOD("get_nw"), &QuadTreeNode::get_nw);
	ClassDB::bind_method(D_METHOD("get_ne"), &QuadTreeNode::get_ne);
	ClassDB::bind_method(D_METHOD("get_sw"), &QuadTreeNode::get_sw);
	ClassDB::bind_method(D_METHOD("get_se"), &QuadTreeNode::get_se);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "state", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE), "set_state", "get_state");
	ADD_PROPERTY(PropertyInfo(Variant::RECT2, "bounds", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE), "set_bounds", "get_bounds");
}