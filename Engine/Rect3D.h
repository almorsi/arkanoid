#pragma once
#include "Graphics.h"
#include "Rectangle.h"
#include "Vec2.h"
#include "Colors.h"
class Rect3D
{
public:
	Rect3D() = default;
	Rect3D(const am::Rectangle rectangle, Color color);
	void draw(Graphics& gfx) const;
private:
	am::Rectangle rect;
	static constexpr float triangle_side = 10.0f;
	static constexpr float shade_scale_right = 0.4f;
	static constexpr float shade_scale_bottom = 0.5f;
	static constexpr float shade_scale_upper = 0.15f;
	static constexpr float shade_scale_left = 0.02f;
	Vec2 top_left;
	float width;
	float height;
	Color col;
private:
	void draw_right_trapeziod(Graphics& gfx) const;
	void draw_left_trapeziod(Graphics& gfx) const;
	void draw_upper_trapeziod(Graphics& gfx) const;
	void draw_bottom_trapeziod(Graphics& gfx) const;
	void draw_triangle_UL(const Vec2& starting_point, Color c, Graphics& gfx) const;
	void draw_triangle_BL(const Vec2& starting_point, Color c, Graphics& gfx) const;
	void draw_triangle_UR(const Vec2& starting_point, Color c, Graphics& gfx) const;
	void draw_triangle_BR(const Vec2& starting_point, Color c, Graphics& gfx) const;
};