#include <iostream>
#include <SFML/Graphics.hpp>

float Square(float value) {
	// Multiply value two times
	return (value) * (value);
}

auto SolveExisosh2ou(double a, double b, double c) {
	double x1 = 0;
	double x2 = 0;
	double delta;

	struct retVals
	{
		float x1, x2;
	};

	delta = Square(b) - 4 * a * c;

	std::cout << "The Square root of delta: " << delta << std::endl;
	if (delta > 0) {
		x1 = (- b + sqrt(delta)) / 2 * a;
		x2 = (- b - sqrt(delta)) / 2 * a;

		std::cout << "x1 = " << x1 << "|x2 = " << x2 << std::endl;
	}
	if (delta == 0)
	{
		x1 = x2 = -b / 2 * a;
		std::cout << "Delta has a value of " << delta << "so x = " << x1 << std::endl;
	}
	if (delta < 0)
	{
		std::cout << "The delta has a value of  " << delta << " so the equation is not undefined." << std::endl;
	}

	float y = c;
	float p1 = x1;
	float p2 = x2;
	std::cout << "y = " << y << " , " << "Point 1 p1 = " << p1 << " , " << "Point 2 p2 = " << p2 << std::endl;
}

void drawQuadraticGraph(double a, double b, double c, double xMin, double xMax, double xStep) {
	// Create a window to draw the graph
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Quadratic Graph");
	window.setFramerateLimit(60);

	// Define the origin of the graph in pixels
	sf::Vector2f origin(400, 300);

	// Define the scale for the x and y values
	double xScale = 30;
	double yScale = 30;

	// Loop through the x values within the given range
	for (double x = xMin; x <= xMax; x += xStep) {
		// Calculate the corresponding y value for the current x
		double y = a * x * x + b * x + c;

		// Convert the x and y values to pixels
		sf::Vector2f point((x - xMin) * xScale + origin.x, -y * yScale + origin.y);

		// Draw a point at the current x and y values
		sf::CircleShape shape(2);
		shape.setFillColor(sf::Color::Cyan);
		shape.setPosition(point);
		window.draw(shape);
	}

	// Display the window
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.display();
	}
}


int main() {
	float a;
	float b;
	float c;
	
	std::cout << "________________________" << std::endl;
	std::cout << "|       Quadratic      |" << std::endl;
	std::cout << "|       Equation       |" << std::endl;
	std::cout << "|       solver         |" << std::endl;
	std::cout << "------------------------" << std::endl;

	std::cout << " " << std::endl;

	std::cout << "* Tip:The equation should" << std::endl;
	std::cout << "have the type of: ax^2 + bx + c" << std::endl;

	std::cout << " " << std::endl;

	std::cout << "> Enter the value of a: "; std::cin >> a;
	std::cout << "> Enter the value of b: "; std::cin >> b;
	std::cout << "> Enter the value of c: "; std::cin >> c;

	SolveExisosh2ou(a, b, c);
	drawQuadraticGraph(a, b, c, -20, 20, 0.5);

	return 0;
}