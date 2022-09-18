#define _USE_MATH_DEFINES

#include <iostream>
#include "Class.h"
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow win(VideoMode(1000, 1000), "TEST");
	win.setFramerateLimit(60);
	win.setMouseCursorVisible(false);
	
	Matrix<double> Vert(100,4);
	for (int i = 0; i < Vert.getH(); i++) {
		Vert[i][0] = i % 10 * 200;
		Vert[i][1] = i / 10 * 200;
		Vert[i][3] = 1;
	}

	Matrix<double> triangle{ {100,100,400,1},
								{100,-100,400,1},
								{-100,0,600,1},
								{0,0,600,1} };
	
	std::vector<double> Angle = { 0,0,0 },
		Coords = {0,0 ,0};
	
	
	int z = 0;

	std::vector<int> Mouse = { 0,0 };
	while (win.isOpen()) {
		Event ev;
		std::vector<int> temp_nap = {0,0};
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();

			if (ev.type == sf::Event::MouseMoved)
			{
				Angle[2] += (double)(ev.mouseMove.x-500)/10;
				Angle[0] -= (double)(ev.mouseMove.y-500)/10;
				Mouse::setPosition(Vector2i(500, 500),win);
			}
	
			temp_nap = { 0,0 };
			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
				temp_nap[0] += 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
				temp_nap[0] -= 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
				temp_nap[1] += 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
				temp_nap[1] -= 1;
			}
						

		}
		double speed;
		switch (abs(temp_nap[0]) + abs(temp_nap[0])) {
		case 2:
			speed = 1.41421356237;
			break;
		case 1:
			speed = 1;
			break;
		case 0:
			speed = 1;
			break;
		}

		Coords[0] += 10 / speed * temp_nap[0] * cos(Angle[2] * M_PI / 180);
		Coords[0] += 10 / speed * temp_nap[1] * cos((Angle[2] + 90) * M_PI / 180);

		Coords[1] += 10 / speed * temp_nap[0] * sin(Angle[2] * M_PI / 180);
		Coords[1] += 10 / speed * temp_nap[1] * sin((Angle[2] + 90) * M_PI / 180);

		z += 1;
		win.clear();
		Matrix<double> temp = (Vert * Matrix<double>::rotate(-Coords[0], -Coords[1], -Coords[2]) * Matrix<double>::transform(0, 0, -Angle[2]) * Matrix<double>::rotate(0, 0,-1000) * Matrix<double>::transform(Angle[0], 0, 0) * Matrix<double>::rotate(0, 0, 1000) * Matrix<double>::projection(1000)).normalize();
		Matrix<double> temp_2 = (triangle* Matrix<double>::transform(0, 0, z) *Matrix<double>::rotate(-Coords[0], -Coords[1], -Coords[2]) * Matrix<double>::transform(0, 0, -Angle[2]) * Matrix<double>::rotate(0, 0, -1000) * Matrix<double>::transform(Angle[0], 0, 0) * Matrix<double>::rotate(0, 0, 1000) * Matrix<double>::projection(1000)).normalize();
		
		for (int i = 0; i < temp_2.getH()-1; i++) {
			for (int j = i + 1; j < temp_2.getH(); j++) {
				sf::VertexArray line(sf::Lines, 2);
				line[0].position = sf::Vector2f(temp_2[i][0] + 500, temp_2[i][1] + 500);
				line[1].position = sf::Vector2f(temp_2[j][0] + 500, temp_2[j][1] + 500);
				win.draw(line);
			}

		}

		for (int i = 0; i < Vert.getH()-11; i++) {
			sf::VertexArray line(sf::LinesStrip, 4);
			if (i % 10 == 9) continue;
			line[0].position = sf::Vector2f(temp[i][0] + 500, temp[i][1] + 500);
			line[1].position = sf::Vector2f(temp[i+1][0]  + 500, temp[i+1][1]  + 500);
			line[3].position = sf::Vector2f(temp[i + 10][0]  + 500, temp[i + 10][1]  + 500);
			line[2].position = sf::Vector2f(temp[i + 11][0]  + 500, temp[i + 11][1]  + 500);
			win.draw(line);	
		}
		
		win.display();
	}
	
	return 0;
}