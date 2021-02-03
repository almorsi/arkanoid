#include "Rectangle.h"

am::Rectangle::Rectangle(float right_val, float left_val, float top_val, float bottom_val)
    :
    right(right_val),
    left(left_val),
    top(top_val),
    bottom(bottom_val)
{
}

am::Rectangle::Rectangle(const Vec2& top_left, const Vec2& bottom_right)
    :
    Rectangle(bottom_right.x, top_left.x, top_left.y, bottom_right.y)
{
}

am::Rectangle::Rectangle(const Vec2& top_left, float width, float height)
    :
    Rectangle(top_left, Vec2(top_left.x + width, top_left.y + height))
{
}

bool am::Rectangle::is_overlapping_with(const Rectangle& rect)
{
    return (right >= rect.left)
        &&(left <= rect.right)
        &&(top <= rect.bottom)
        &&(bottom >= rect.top);
}

am::Rectangle am::Rectangle::init_from_center(const Vec2& center, float half_width, float half_height)
{
    return am::Rectangle(Vec2(center.x-half_width, center.y-half_height), 2*half_width, 2*half_height);
}

am::Rectangle am::Rectangle::get_expanded(float offset) const
{
    return am::Rectangle(right + offset, left - offset, top - offset, bottom + offset);
}
