/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
//test
Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(Vec2(0.0f, 0.0f), Vec2(float(Graphics::ScreenWidth), float(Graphics::ScreenHeight))),
	ball(Vec2(100.0f, 200.0f), Vec2(350.0f, 350.0f)),
	pad(Vec2(500, 500), 50, 15),
	hit_pad(L"Sounds\\arkpad.wav"),
	hit_brick(L"Sounds\\arkbrick.wav"),
	game_over(L"Sounds\\game_over.wav")
{
	const Vec2 top_left = { brick_width, brick_height };

	for (int y = 0; y < n_rows; y++)
	{
		const Color c = bricks_color[y%5];//5 is the number of colors in the arry bricks_color
		for (int x = 0; x < n_column; x++)
		{
			bricks[y * n_column + x] = Brick(
				am::Rectangle(Vec2(top_left.x + x * brick_width, top_left.y + y * brick_height), brick_width, brick_height), c);
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!is_game_over)
	{
		const float dt = ft.Mark();
		ball.update(dt);
		pad.update(wnd.kbd, dt);
		pad.is_collide_with_walls(walls);

		if (pad.is_collide_with_ball(ball))
			hit_pad.Play();
		if (ball.is_collide_with_ground(walls))
		{
			is_game_over = true;
			game_over.Play();
		}
		if (ball.is_collide_with_walls(walls) && !is_game_over)
			hit_pad.Play();
		for (Brick& brick : bricks)
		{
			if (brick.is_collide_with_ball(ball))
			{
				hit_brick.Play();
				break;
			}
		}
	}
}

void Game::ComposeFrame()
{
	for (Brick& brick : bricks)
	{
		brick.draw(gfx);
	}
	if (!is_game_over)
	{
		ball.draw(gfx);
	}
	pad.draw(gfx);
}
