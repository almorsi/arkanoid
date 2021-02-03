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
