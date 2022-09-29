#include "Prelude.h"
#include "Genome.h"
#include "Agent.h"
#include "Environment.h"

#include "raylib.h"

#define CAMERA_SPEED 3.0

bool is_drawing = true;

void move_camera(Camera2D& c2d)
{
	if (IsKeyDown(KEY_RIGHT))
	{
		c2d.target.x += CAMERA_SPEED;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		c2d.target.x -= CAMERA_SPEED;
	}

	if (IsKeyDown(KEY_UP))
	{
		c2d.target.y -= CAMERA_SPEED;
	}

	if (IsKeyDown(KEY_DOWN))
	{
		c2d.target.y += CAMERA_SPEED;
	}
}

int main()
{
	srand(time(NULL));

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "!biosphere!");

	SetTargetFPS(1000);

	Camera2D c2d;
	c2d.target = Vector2{ 0, 0 };
	c2d.offset = Vector2{ screenWidth / 2.0, screenHeight / 2.0 };
	c2d.rotation = 0.0;
	c2d.zoom = 1.0;

	Genome g = randomGenome(0);
	Phenotype p = g.unfold(100);

	Map map;

	map.create<Agent>(5, 5);

  while (!WindowShouldClose())
  {
		move_camera(c2d);

		if (IsKeyReleased(KEY_Q))
		{
			is_drawing = !is_drawing;
		}

		map.tick();

    BeginDrawing();

    ClearBackground(RAYWHITE);

    //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);


		if (is_drawing)
		{
			BeginMode2D(c2d);

				map.draw();

			EndMode2D();
		}

		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 10, BLUE);

    EndDrawing();
  }

  CloseWindow();


	return 0;
}