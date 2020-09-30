#include "quadtreenode.h"

static QuadTreeNode* QuadTreeNode::create_node(const QuadTreeNode* parent, const Rect2i& bounds, const int state)
{
    QuadTreeNode* node = new QuadTreeNode();
    node->parent = parent;
    node->bounds = bounds;
    node->state = state;
    return node;
}

QuadTreeNode::QuadTreeNode() 
{
    state = 0;
}

void QuadTreeNode::split()
{
    child_nw = create_node(this, Rect2i(
        bounds.position.x,
        bounds.position.y,
        bounds.size.width/2,
        bounds.size.height/2),
        state);
    child_ne = create_node(this, Rect2i(
        bounds.position.x + bounds.size.x/2,
        bounds.position.y,
        bounds.size.width/2,
        bounds.size.height/2),
        state);
    child_sw = create_node(this, Rect2i(
        bounds.position.x,
        bounds.position.y + bounds.size.y/2,
        bounds.size.width/2,
        bounds.size.height/2),
        state);
    child_se = create_node(this, Rect2i(
        bounds.position.x + bounds.size.x/2,
        bounds.position.y + bounds.size.y/2,
        bounds.size.width/2,
        bounds.size.height/2),
        state);
    state = -1;
}

void QuadTreeNode::close(const int state)
{
    delete child_nw;
    delete child_ne;
    delete child_sw;
    delete child_se;
    child_nw = NULL;
    child_ne = NULL;
    child_sw = NULL;
    child_se = NULL;
    this->state = state;
}

void QuadTreeNode::insert_rect(const Rect2i& target, const int value)
{
    if (target.encloses(bounds))
    {
        close(value);
    }
    else if (bounds.intersects(target))
    {
        if (state != -1) split();

        child_nw->insert_rect(target, value);
        child_ne->insert_rect(target, value);
        child_sw->insert_rect(target, value);
        child_se->insert_rect(target, value);
        if (child_ne->state != -1 &&
            child_ne->state == child_nw->state &&
            child_ne->state == child_sw->state &&
            child_ne->state == child_se->state)
        {
            close(child_ne->state);
        }
    }
}

int QuadTreeNode::state_at_point(const Vector2i& point)
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

void QuadTreeNode::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_node", "parent", "bounds", "state"), &QuadTreeNode::create_node);
	ClassDB::bind_method(D_METHOD("split"), &QuadTreeNode::split);
    ClassDB::bind_method(D_METHOD("close", "state"), &QuadTreeNode::close);
	ClassDB::bind_method(D_METHOD("insert_rect", "target", "value"), &QuadTreeNode::insert_rect);
    ClassDB::bind_method(D_METHOD("state_at_point", "point"), &QuadTreeNode::state_at_point);
}