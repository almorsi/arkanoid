#include "Brick.h"

Brick::Brick(const am::Rectangle& rectangle, const Color& color)
	:
	rect(rectangle),
	col(color)
{
}

void Brick::draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.draw_rectangle(rect, col);
	}
}

bool Brick::is_collide_with_ball(Ball& ball)
{
	// there a bug here
	if (!destroyed && rect.is_overlapping_with(ball.get_rectangle()))
	{
		ball.rebound_y();
		destroyed = true;
		return true;
	}
	return false;
}
