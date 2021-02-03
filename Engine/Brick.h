#pragma once
#include "Rectangle.h"
#include "Colors.h"
#include "Graphics.h"
class Brick
{
public:
	Brick() = default;
	Brick(const am::Rectangle& rectangle, const Color& color);
	void draw(Graphics& gfx) const;
private:
	static constexpr float padding = 1.0f;
	am::Rectangle rect;
	Color col;
	bool destroyed = false;
};