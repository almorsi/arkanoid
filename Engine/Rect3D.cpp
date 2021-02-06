#include "Rect3D.h"

Rect3D::Rect3D(const am::Rectangle rectangle, Color color)
	:
	rect(rectangle),
	top_left(Vec2(rect.left, rect.top)),
	width((rect.right-rect.left)),
	height((rect.bottom- rect.top)), 
	col(color)
{
}

void Rect3D::draw(Graphics& gfx) const
{
	draw_upper_trapeziod(gfx);
	draw_left_trapeziod(gfx);
	draw_right_trapeziod(gfx);
	draw_bottom_trapeziod(gfx);
	gfx.draw_rectangle(am::Rectangle(top_left + Vec2(triangle_side+1, triangle_side+1),width-2.0f*triangle_side-1, height-2.0f*triangle_side-1),col);
}

void Rect3D::draw_right_trapeziod(Graphics& gfx) const
{
	float fac = 1 - shade_scale_right;
	Color new_col = {unsigned char(fac * int(col.GetR())), unsigned char(fac * int(col.GetB())), unsigned char(fac* int(col.GetG()))};
	draw_triangle_BR(top_left + Vec2(width, triangle_side ), new_col, gfx);
	gfx.draw_rectangle( am::Rectangle( 
		(top_left + Vec2(width - triangle_side + 1, triangle_side) ), triangle_side,height-2.0f*triangle_side ), new_col );
	draw_triangle_UR(top_left + Vec2(width, height - triangle_side), new_col, gfx);
}

void Rect3D::draw_left_trapeziod(Graphics& gfx) const
{
	Color new_col = { unsigned char(col.GetR() +  unsigned char(shade_scale_left * (255 - int(col.GetR())))),
		unsigned char(col.GetB() + unsigned char(shade_scale_left * (255 - int(col.GetB())))),
		unsigned char(col.GetG() + unsigned char(shade_scale_left * (255 - int(col.GetG()))))};
	draw_triangle_BL(top_left + Vec2(0.0f, triangle_side), new_col, gfx);
	gfx.draw_rectangle(am::Rectangle (top_left + Vec2(0.0f, triangle_side + 1 ) , triangle_side, height - 2.0f * triangle_side), new_col);
	draw_triangle_UL(top_left + Vec2(0.0f, height - triangle_side), new_col, gfx);

}

void Rect3D::draw_upper_trapeziod(Graphics& gfx) const
{
	Color new_col = { unsigned char(col.GetR() + unsigned char(shade_scale_upper * (255 - int(col.GetR())))),
	unsigned char(col.GetB() + unsigned char(shade_scale_upper * (255 - int(col.GetB())))),
	unsigned char(col.GetG() + unsigned char(shade_scale_upper * (255 - int(col.GetG())))) };
	draw_triangle_UR(top_left + Vec2(triangle_side, 0.0f), new_col, gfx);
	gfx.draw_rectangle(am::Rectangle(top_left + Vec2(triangle_side+1,0.0f),width- 2.0f*triangle_side, triangle_side),new_col);
	draw_triangle_UL(top_left + Vec2(width-triangle_side, 0.0f), new_col, gfx);
}

void Rect3D::draw_bottom_trapeziod(Graphics& gfx) const
{
	float fac = 1 - shade_scale_bottom;
	Color new_col = { unsigned char(fac * int(col.GetR())), unsigned char(fac * int(col.GetB())), unsigned char(fac * int(col.GetG())) };
	draw_triangle_BR(top_left + Vec2(triangle_side, height), new_col, gfx);
	gfx.draw_rectangle(am::Rectangle(
		top_left + Vec2(triangle_side+1, height-triangle_side+1),width-2.0f*triangle_side, triangle_side), new_col);
	draw_triangle_BL(top_left + Vec2(width-triangle_side, height), new_col, gfx);

}

void Rect3D::draw_triangle_UL(const Vec2& starting_point, Color c, Graphics& gfx) const
{
	int x_s = int(starting_point.x);
	int y_s = int(starting_point.y);
	for (int i = y_s; i < y_s + int(triangle_side); i++)
	{
		int cond = x_s + int(triangle_side) - (i - y_s);
		for (int j = x_s; j < cond; j++)
			gfx.PutPixel(j, i, c);
	}
}

void Rect3D::draw_triangle_BL(const Vec2& starting_point, Color c, Graphics& gfx) const
{
	int x_s = int(starting_point.x);
	int y_s = int(starting_point.y);
	for (int i = y_s; i > y_s - int(triangle_side); i--)
	{
		int cond = x_s + int(triangle_side) - (y_s - i);
		for (int j = x_s; j < cond; j++)
			gfx.PutPixel(j, i, c);
	}
}

void Rect3D::draw_triangle_UR(const Vec2& starting_point, Color c, Graphics& gfx) const
{
	int x_s = int(starting_point.x);
	int y_s = int(starting_point.y);
	for (int i = y_s; i < y_s + int(triangle_side); i++)
	{
		int cond = x_s - int(triangle_side) + (i - y_s);
		for (int j = x_s; j > cond; j--)
			gfx.PutPixel(j, i, c);
	}
}

void Rect3D::draw_triangle_BR(const Vec2& starting_point, Color c, Graphics& gfx) const
{
	int x_s = int(starting_point.x);
	int y_s = int(starting_point.y);
	for (int i = y_s; i > y_s - int(triangle_side); i--)
	{
		int cond = x_s - int(triangle_side) + (y_s - i);
		for (int j = x_s; j > cond; j--)
			gfx.PutPixel(j, i, c);
	}
}
