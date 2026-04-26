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

std::string i = "  SIN(x) - 257.4 * x^2";

enum TokenType
{
	NUMBER,
	OPERATOR, 
	VARIABLE,
	FUNCTION,
	L_PAREN,
	R_PAREN
};

struct Token {
	TokenType type;
	std::string val;
};

std::string checkinput(std::string in) {
	std::string out = { 0 };
	for (int i = 0; i < in.length(); i++) {
		if (in[i] == ' ') {
			continue;
		}
		else if (std::isupper(in[i])) {
			out += tolower(in[i]);
		}
		else if (in[i] == '#' || in[i] == '@') {
			std::cout << "ERROR: INVALID CHARACTER!!!" << std::endl;
			out = "";
			break;
		}
		else {
			out += in[i];
		}
	}
	std::cout << out << std::endl;
	return out;
}

void parse(std::string in) {
	int i = 0;
	std::vector<Token> tokens = {};
	while (i < in.length()) {
		if (isdigit(in[i])) {
			int j = i + 1;
			std::string tmp_buffer = "";
			tmp_buffer += in[i];
			while (isdigit(in[j]) || (in[j] == '.')) {
				tmp_buffer += in[j];
				j++;
			}
			tokens.push_back({ NUMBER, tmp_buffer });
			if (j > i + 1) {
				i = j-1;
			}
		}
		else if (isalpha(in[i])) {
			int j = i + 1;
			std::string tmp_buffer = "";
			tmp_buffer += in[i];
			while (isalpha(in[j])) {
				tmp_buffer += in[j];
				j++;
			}
			if (tmp_buffer == "x") {
				tokens.push_back({ VARIABLE, tmp_buffer });
			}
			else {
				tokens.push_back({ FUNCTION, tmp_buffer });
				i = j-1;
			}
		}
		else if (in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' || in[i] == '^') {
			std::string tmp_buffer = "";
			tmp_buffer += in[i];
			tokens.push_back({ OPERATOR, tmp_buffer});
		}
		else if (in[i] == '(' || in[i] == ')') {
			std::string tmp_buffer = "";
			tmp_buffer += in[i];
			if (tmp_buffer == "(") {
				tokens.push_back({ L_PAREN, tmp_buffer });
			}
			else {
				tokens.push_back({ R_PAREN, tmp_buffer });
			}
		}
		i++;
	}
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i].type << " | " << tokens[i].val << std::endl;
	}
}

//Graph toggle
bool drawngraph = false;
//Graph points
std::vector<Vector2> points;

//TextBox1 Buffer and Focus toggle
char tb1_buf[256];
bool tb1_foc = false;

//TextBox2 Buffer and Focus toggle
char tb2_buf[256];
bool tb2_foc = false;

//TextBox3 Buffer and Focus toggle
char tb3_buf[256];
bool tb3_foc = false;

void drawQuadraticGraph(double a, double b, double c, double xMin, double xMax, double xStep) {
	InitWindow(800, 600, "Quadratic Graph");
	
	Camera2D cam = {0};
	cam.zoom = 1.f;
	
	Color DefTextColor = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));

	//Screen origin
	Vector2 origin = { 400, 300 };

	float radius = 0;
	float bradius = 1.5f;

	//Converting the params from double to string and copying them to the buffers.
	sprintf_s(tb1_buf, sizeof(tb1_buf), "%0.2f", a);
	sprintf_s(tb2_buf, sizeof(tb2_buf), "%0.2f", b);
	sprintf_s(tb3_buf, sizeof(tb3_buf), "%0.2f", c);
		
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
		
		//Running only on RELEASE build
#ifdef NDEBUG
		//Graph properties GUI
		{
			GuiGroupBox({ 5, 40, 110, 125 }, "Equation");

			if (GuiTextBox({ 10, 50, 100, 20 }, tb1_buf, 20, tb1_foc)) { tb1_foc = !tb1_foc; }
			if (GuiTextBox({ 10, 80, 100, 20 }, tb2_buf, 20, tb2_foc)) { tb2_foc = !tb2_foc; }
			if (GuiTextBox({ 10, 110, 100, 20 }, tb3_buf, 20, tb3_foc)) { tb3_foc = !tb3_foc; }

			if (GuiButton({ 10, 140, 100, 20 }, "Graph")) {
				a = std::stod(tb1_buf);
				b = std::stod(tb2_buf);
				c = std::stod(tb3_buf);
				drawngraph = false;
			}
		}
#endif // _NDEBUG

		//Making radius dependant to camera zoom 
		radius = bradius / cam.zoom;


		//Running only on DEBUG build
#ifdef _DEBUG
				
		const char* title = TextFormat("Quadratic Graph | FPS: %i", GetFPS());
		SetWindowTitle(title);

		//Graph properties GUI
		{
			GuiGroupBox({ 5, 80, 110, 125 }, "Equation");

			if (GuiTextBox({ 10, 90, 100, 20 }, tb1_buf, 20, tb1_foc)) { tb1_foc = !tb1_foc; }
			if (GuiTextBox({ 10, 120, 100, 20 }, tb2_buf, 20, tb2_foc)) { tb2_foc = !tb2_foc; }
			if (GuiTextBox({ 10, 150, 100, 20 }, tb3_buf, 20, tb3_foc)) { tb3_foc = !tb3_foc; }

			if (GuiButton({ 10, 180, 100, 20 }, "Graph")) {
				a = std::stod(tb1_buf);
				b = std::stod(tb2_buf);
				c = std::stod(tb3_buf);
				drawngraph = false;
			}
		}
		
		//Debug Text
		const char* t = TextFormat("RADIUS: %f | ZOOM: %f", radius, cam.zoom);
		DrawText(t, 10, 30, 20, DefTextColor);
		const char* t2 = "DEBUG";
		DrawText(t2, 800 - MeasureText(t2, 20) - 10, 10, 20, DefTextColor);
				
#endif // DEBUG
		
		BeginMode2D(cam);
		
		//X, Y Axis
		DrawLineV({ -100000, 300 }, { 100000, 300 }, DARKGRAY);
		DrawLineV({ 400 , 100000 }, { 400, -100000 }, DARKGRAY);
		
		//Calculating the Points only when the param change.
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
		//Rendering the graph
		DrawSplineBezierQuadratic(points.data(), points.size(), radius, RED);

		EndMode2D();
		EndDrawing();

	}
}


int main() {
	parse(checkinput(i));

	float a = 0.1;	float b = 1; float c = 0;
	drawQuadraticGraph(a, b, c, -2000, 2000, 1);

	return 0;
}