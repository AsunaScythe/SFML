#define _USE_MATH_DEFINES

#include <iostream>
#include "Matrix.h"
#include "graphics.h"
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow win(VideoMode(1000, 1000), "TEST");

	win.setFramerateLimit(60);
	win.setMouseCursorVisible(false);
	
	Matrix<double> Vert(100,4);
	for (int i = 0; i < Vert.getHeight(); i++) {
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
	
	
	int z = 0,
		e = 0;

	std::vector<int> Mouse = { 0,0 };
	double ty = 1000;
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
			if (Keyboard::isKeyPressed(Keyboard::Key::Y)) 
				ty += 10;
			if (Keyboard::isKeyPressed(Keyboard::Key::H)) 
				ty -= 10;
			if (Keyboard::isKeyPressed(Keyboard::Key::U))
				e += 10;
			if (Keyboard::isKeyPressed(Keyboard::Key::J))
				e -= 10;
			if (Keyboard::isKeyPressed(Keyboard::Key::K))
				e = ty;
			std::cout << ty << " " << e << std::endl;

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

		Coords[0] += 100 / speed * temp_nap[0] * cos(Angle[2] * M_PI / 180);
		Coords[0] += 100 / speed * temp_nap[1] * cos((Angle[2] + 90) * M_PI / 180);

		Coords[1] += 100 / speed * temp_nap[0] * sin(Angle[2] * M_PI / 180);
		Coords[1] += 100 / speed * temp_nap[1] * sin((Angle[2] + 90) * M_PI / 180);

		z += 1;
		win.clear();


		Matrix<double> both = move(-Coords[0], -Coords[1], -1000) * rotate_z(-Angle[2]) * rotate_x(Angle[0]) * move(0, 0, e);
		Matrix<double> temp = (Vert * both);
		std::vector<bool> back(temp.getHeight(), true);
		/*
		for(int i = 0;i < temp.getH();i++)
			if (temp[i][2] > 0) {
				back[i] = false;
			}
		*/	
		temp = (temp * projection(ty)).normalize();
		Matrix<double> temp_2 = (triangle * rotate_z(z) * both*projection(ty)).normalize();

		for (int i = 0; i < temp_2.getHeight()-1; i++) {
			for (int j = i + 1; j < temp_2.getHeight(); j++) {
				sf::VertexArray line(sf::Lines, 2);
				line[0].position = sf::Vector2f(temp_2[i][0] + 500, temp_2[i][1] + 500);
				line[1].position = sf::Vector2f(temp_2[j][0] + 500, temp_2[j][1] + 500);
				win.draw(line);
			}

		}

		for (int i = 0; i < Vert.getHeight()-11; i++) {
			sf::VertexArray line(sf::Quads, 4);
			if (i % 10 == 9) continue;
			Color col;
			if ((i + (i / 10 % 2)) % 2  == 0)
				col = Color::Red;
			else
				col = Color::Blue;
			line[0].position = sf::Vector2f(temp[i][0] + 500, temp[i][1] + 500);
			line[1].position = sf::Vector2f(temp[i+1][0]  + 500, temp[i+1][1]  + 500);
			line[3].position = sf::Vector2f(temp[i + 10][0]  + 500, temp[i + 10][1]  + 500);
			line[2].position = sf::Vector2f(temp[i + 11][0]  + 500, temp[i + 11][1]  + 500);
			for (int j = 0; j < 4; j++) line[j].color = col;
			if(!(!back[i] && !back[i + 1] && !back[i + 10] && !back[i + 11]))
				win.draw(line);	
		}
		
		win.display();
	}
	
	return 0;
}