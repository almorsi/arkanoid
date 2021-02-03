#pragma once
#include "Vec2.h"
namespace am
{
	class Rectangle
	{
	public:
		Rectangle() = default;
		Rectangle(float right, float left, float top, float bottom);
		Rectangle(const Vec2& top_left, const Vec2& bottom_right);
		Rectangle(const Vec2& top_left, float width, float height);
		bool is_overlapping_with(const Rectangle& rect);
		static am::Rectangle init_from_center(const Vec2& center, float half_width, float half_height);
		am::Rectangle get_expanded(float offset) const;
	public:
		float right, left, top, bottom;
	};
}