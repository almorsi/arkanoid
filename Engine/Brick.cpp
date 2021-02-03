#include "Brick.h"

Brick::Brick(const am::Rectangle& rectangle, const Color& color)
	:
	rect(rectangle),
	col(color), 
	center(rect.left + rect.right/2.0f, rect.top + rect.bottom/2.0f)
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
	// there a bug here
	if (!destroyed && rect.is_overlapping_with(ball.get_rectangle()))
	{
		ball.rebound_y();
		destroyed = true;
		return true;
	}
	return false;
}
