#include "Paddel.h"

Paddel::Paddel(const Vec2& center, float half_width_val, float half_height_val)
	:
	pos(center),
	half_width(half_width_val),
	half_height(half_height_val)
{
}

void Paddel::draw(Graphics& gfx) const
{
	am::Rectangle temp = get_rectangle();
	gfx.draw_rectangle(temp, wing_col);
	temp.left += wing_width;
	temp.right -= wing_width;
	gfx.draw_rectangle(temp, col);
}

void Paddel::update(const Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= x_vel * dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += x_vel * dt;
	}
}

bool Paddel::is_collide_with_ball(Ball& ball) const
{
	if (ball.get_rectangle().is_overlapping_with(get_rectangle()))
	{
		ball.reset_vel_after_pad_collision(Vec2(ball.get_pos()- pos).GetNormalized());
		return true;
	}
	return false;
}

void Paddel::is_collide_with_walls(const am::Rectangle& walls)
{
	const am::Rectangle temp = get_rectangle();
	if (temp.left <= walls.left)
	{
		pos.x += walls.left - temp.left;
	}
	else if (temp.right >= walls.right)
	{
		pos.x -= temp.right - walls.right;
	}
}

am::Rectangle Paddel::get_rectangle() const
{
	return am::Rectangle::init_from_center(pos, half_width, half_height);
}
