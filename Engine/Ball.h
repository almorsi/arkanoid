#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Rectangle.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& center_pos, const Vec2& vel_val);
	void draw(Graphics& gfx)const;
	void update(float dt);
	bool is_collide_with_walls(const am::Rectangle& walls);
	void rebound_x();
	void rebound_y();
	am::Rectangle get_rectangle() const;
private:
	static constexpr float radius = 7.0f;//don't change this number because spriteCodex depend on it
	Vec2 pos;//the position of the center
	Vec2 vel;
};