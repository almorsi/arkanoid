#pragma once
#include "Colors.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Ball.h"
#include "Rectangle.h"

class Paddel
{
public:
	Paddel() = default;
	Paddel(const Vec2& center, float half_width, float half_height);
	void draw(Graphics& gfx) const;
	void update(const Keyboard& kbd, float dt);
	bool is_collide_with_ball(Ball& ball) const;
	void is_collide_with_walls(const am::Rectangle& walls);
	am::Rectangle get_rectangle() const;
private:
	Color col = Colors::Blue;
	Vec2 pos;//from center
	float half_width;
	float half_height;
	static constexpr float x_vel = 600.0f ;// move only in the x direction
	static constexpr float wing_width = 20;
	Color wing_col = Colors::Gray;

};