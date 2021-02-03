#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& center_pos, const Vec2& vel_val)
	:
	pos(center_pos),
	vel(vel_val)
{
}

void Ball::draw(Graphics& gfx)const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::update(float dt)
{
	pos += vel * dt;
}

bool Ball::is_collide_with_walls(const am::Rectangle& walls)
{
	bool is_collide = false;
	const am::Rectangle rect = get_rectangle();
	if (rect.left <= walls.left)
	{
		pos.x += walls.left - rect.left;
		rebound_x();
		is_collide = true;
	}
	else if (rect.right >= walls.right)
	{
		pos.x -= rect.right - walls.right;
		rebound_x();
		is_collide = true;
	}

	if (rect.top <= walls.top)
	{
		pos.y += walls.top - rect.top;
		rebound_y();
		is_collide = true;
	}
	else if (rect.bottom >= walls.bottom)
	{
		pos.y -= rect.bottom - walls.bottom;
		rebound_y();
		is_collide = true;
	}
	return is_collide;
}

void Ball::rebound_x()
{
	vel.x = -vel.x;
}

void Ball::rebound_y()
{
	vel.y = -vel.y;
}

am::Rectangle Ball::get_rectangle() const
{
	return am::Rectangle::init_from_center(pos,radius, radius);
}