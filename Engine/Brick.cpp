#include "Brick.h"

Brick::Brick(const am::Rectangle& rectangle, const Color& color)
	:
	rect(rectangle),
	col(color), 
	half_width((rect.right- rect.left)/2.0f),
	half_height((rect.bottom-rect.top)/2.0f),
	center(rect.left + half_width, rect.top + half_height)
{
}

void Brick::draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.draw_rectangle(rect.get_expanded(padding), col);
	}
}

bool Brick::is_collide_with_ball(Ball& ball)
{
	// ________________  
	// |	2  |	1  |
	// |_ _ _ _|_ _ _ _|  DIVIDE THE RECTANGLE INTO FOUR RECTAGNLES TO SOLVE THE PHYSICS BUG
	// |	3  |	4  |
	// |______ |_______|
	if (!destroyed)
	{
		using am::Rectangle;
		const Rectangle rect_1 = Rectangle(Vec2(center.x, center.y - half_height), Vec2(center.x + half_width, center.y));
		const Rectangle rect_2 = Rectangle(Vec2(center.x - half_width, center.y - half_height), Vec2(center.x, center.y));
		const Rectangle rect_3 = Rectangle(Vec2(center.x - half_width, center.y), Vec2(center.x , center.y + half_height));
		const Rectangle rect_4 = Rectangle(Vec2(center.x, center.y), Vec2(center.x + half_width, center.y + half_height));
		Vec2 vel = ball.get_velocity();
		if (ball.get_rectangle().is_overlapping_with(rect_1))
		{
			if (vel.x < 0)
				ball.rebound_x();
			if (vel.y > 0)
				ball.rebound_y();
			destroyed = true;
			return true;
		}
		else if (ball.get_rectangle().is_overlapping_with(rect_2))
		{
			if (vel.x > 0)
				ball.rebound_x();
			if (vel.y > 0)
				ball.rebound_y();
			destroyed = true;
			return true;
		}
		else if (ball.get_rectangle().is_overlapping_with(rect_3))
		{
			if (vel.x > 0)
				ball.rebound_x();
			if (vel.y < 0)
				ball.rebound_y();
			destroyed = true;
			return true;
		}
		else if (ball.get_rectangle().is_overlapping_with(rect_4))
		{
			if (vel.x < 0)
				ball.rebound_x();
			if (vel.y < 0)
				ball.rebound_y();
			destroyed = true;
			return true;
		}
	}
	return false;
}
