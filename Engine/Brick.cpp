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
		gfx.draw_rectangle(rect.get_expanded(-padding), col);
	}
}

bool Brick::is_collide_with_ball(Ball& ball)
{
	if (!destroyed && ball.get_rectangle().is_overlapping_with(rect))
	{
		ball.reset_vel_after_pad_collision(Vec2(ball.get_pos() - center).GetNormalized());
		destroyed = true;
		return true;
	}
	return false;
}
