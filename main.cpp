#include <iostream>
#include <vector>
#include <Print>
#include <string>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

float sqr(float value) {
	// Multiply value two times
	return (value) * (value);
}

bool drawngraph = false;
std::vector<Vector2> points;

char buf[256];
bool foc1 = false;

char buf1[256];
bool foc2 = false;

char buf2[256];
bool foc3 = false;

void drawQuadraticGraph(double a, double b, double c, double xMin, double xMax, double xStep) {
	InitWindow(800, 600, "Quadratic Graph");
	
	Camera2D cam = {0};
	cam.zoom = 1.f;
	
	Color DefTextColor = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));

	Vector2 origin = { 400, 300 };

	float radius = 0;
	float bradius = 1.5f;

	sprintf_s(buf, sizeof(buf), "%0.2f", a);
	sprintf_s(buf1, sizeof(buf1), "%0.2f", b);
	sprintf_s(buf2, sizeof(buf2), "%0.2f", c);
		
	while (!WindowShouldClose()) {
		
		cam.zoom = expf(logf(cam.zoom) + ((float)GetMouseWheelMove() * 0.1f));

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / cam.zoom);
			cam.target = Vector2Add(cam.target, delta);
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);
				
		const char* equition = TextFormat( u8"ax²+bx+c", a, b, c);
		DrawTextEx(GetFontDefault(), equition, {10, 10}, 20, 5, DefTextColor);
		

#ifdef NDEBUG
		GuiGroupBox({ 5, 40, 110, 125 }, "Equation");
		
		if (GuiTextBox({ 10, 50, 100, 20 }, buf, 20, foc1)) { foc1 = !foc1; }
		if (GuiTextBox({ 10, 80, 100, 20 }, buf1, 20, foc2)) { foc2 = !foc2; }
		if (GuiTextBox({ 10, 110, 100, 20 }, buf2, 20, foc3)) { foc3 = !foc3; }

		if (GuiButton({ 10, 140, 100, 20 }, "Graph")) {
			a = std::stod(buf);
			b = std::stod(buf1);
			c = std::stod(buf2);
			drawngraph = false;
		}
#endif // _NDEBUG

		radius = bradius / cam.zoom;

#ifdef _DEBUG

		const char* title = TextFormat("Quadratic Graph | FPS: %i", GetFPS());
		SetWindowTitle(title);

		GuiGroupBox({ 5, 80, 110, 125 }, "Equation");
		
		if (GuiTextBox({ 10, 90, 100, 20 }, buf, 20, foc1)) { foc1 = !foc1; }
		if (GuiTextBox({ 10, 120, 100, 20 }, buf1, 20, foc2)) { foc2 = !foc2; }
		if (GuiTextBox({ 10, 150, 100, 20 }, buf2, 20, foc3)) { foc3 = !foc3; }

		if (GuiButton({ 10, 180, 100, 20 }, "Graph")) {
			a = std::stod(buf);
			b = std::stod(buf1);
			c = std::stod(buf2);
			drawngraph = false;
		}

		if (IsKeyPressed(KEY_PAGE_UP)) {
			radius += 0.1f;
		}
		else if (IsKeyPressed(KEY_PAGE_DOWN)) {
			radius -= 0.1f;
		}
		//Debug Text

		const char* t = TextFormat("RADIUS: %f | ZOOM: %f", radius, cam.zoom);
		DrawText(t, 10, 30, 20, DefTextColor);
		const char* t2 = "DEBUG";
		DrawText(t2, 800 - MeasureText(t2, 20) - 10, 10, 20, DefTextColor);
				
#endif // DEBUG
		
		BeginMode2D(cam);
		
		DrawLineV({ -100000, 300 }, { 100000, 300 }, DARKGRAY);
		DrawLineV({ 400 , 100000 }, { 400, -100000 }, DARKGRAY);
		 

		if (drawngraph == false) {
			points.clear();
			for (double x = xMin; x <= xMax; x += xStep) {
				// Calculate the corresponding y value for the current x
				double y = (a * sqr(x)) + (b * x) + c;

				// Convert the x and y values to pixels
				Vector2 point = { x + origin.x, -y + origin.y };
				
				points.push_back(point);

			}
			drawngraph = true;
		}
		DrawSplineBezierQuadratic(points.data(), points.size(), radius, RED);

		EndMode2D();
		EndDrawing();

	}
}


int main() {
	float a = 0.1;
	float b = 1;
	float c = 0;
	
	drawQuadraticGraph(a, b, c, -2000, 2000, 1);

	return 0;
}