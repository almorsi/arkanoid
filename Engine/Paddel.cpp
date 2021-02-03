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
	// ________________  
	// |	2  |	1  |
	// |_ _ _ _|_ _ _ _|  DIVIDE THE RECTANGLE INTO FOUR RECTAGNLES TO SOLVE THE PHYSICS BUG
	// |	3  |	4  |
	// |______ |_______|
		using am::Rectangle;
		const Rectangle rect_1 = Rectangle(Vec2(pos.x, pos.y - half_height), Vec2(pos.x + half_width, pos.y));
		const Rectangle rect_2 = Rectangle(Vec2(pos.x - half_width, pos.y - half_height), Vec2(pos.x, pos.y));
		const Rectangle rect_3 = Rectangle(Vec2(pos.x - half_width, pos.y), Vec2(pos.x, pos.y + half_height));
		const Rectangle rect_4 = Rectangle(Vec2(pos.x, pos.y), Vec2(pos.x + half_width, pos.y + half_height));
		Vec2 vel = ball.get_velocity();
		if (ball.get_rectangle().is_overlapping_with(rect_1))
		{
			if (vel.x < 0)
				ball.rebound_x();
			if (vel.y > 0)
				ball.rebound_y();
			return true;
		}
		else if (ball.get_rectangle().is_overlapping_with(rect_2))
		{
			if (vel.x > 0)
				ball.rebound_x();
			if (vel.y > 0)
				ball.rebound_y();
			return true;
		}
		else if (ball.get_rectangle().is_overlapping_with(rect_3))
		{
			if (vel.x > 0)
				ball.rebound_x();
			if (vel.y < 0)
				ball.rebound_y();
			return true;
		}
		else if (ball.get_rectangle().is_overlapping_with(rect_4))
		{
			if (vel.x < 0)
				ball.rebound_x();
			if (vel.y < 0)
				ball.rebound_y();
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
