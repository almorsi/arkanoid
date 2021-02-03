#pragma once
#include "Rectangle.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Vec2.h"
class Brick
{
public:
	Brick() = default;
	Brick(const am::Rectangle& rectangle, const Color& color);
	void draw(Graphics& gfx) const;
	bool is_collide_with_ball(Ball& ball);
private:
	static constexpr float padding = 1.0f;
	am::Rectangle rect;
	Color col;
	Vec2 center;
	bool destroyed = false;
};