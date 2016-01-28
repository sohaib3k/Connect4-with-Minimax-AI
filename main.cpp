#include <SFML/Graphics.hpp>
#include <iostream>
#include "Header.h"
int check = 0; // Check if UserFunc ran
int check1 = 0;// Check if AIfunc ran
int won = 0;//CHeck if AI has won
int won2 = 0;//Check if user has won
void GameGRAPHICS(game *a){
	game *g = a;
	sf::Texture image;
	image.loadFromFile("Untitled.png");

	sf::Texture image1;
	image1.loadFromFile("Untitled1.png");

	sf::Texture im2;
	im2.loadFromFile("draw.png");

	sf::Sprite sprite;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(700, 700), "Minimax AI I.Q chess!", sf::Style::Default, settings);

	sf::CircleShape shape(20.f);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Blue);

	int positionX = 10;
	int positionY = 10;
	map <int, vector<char> > table;
	sf::RectangleShape button(sf::Vector2f(50, 50));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (check < 1)
		{
			check++;
			g->iniTable(g->DIMENSION);
		}
		table = g->gameTable;
		for (int i = 0; i < g->DIMENSION; i++)
		{
			positionY = 10;
			for (int j = 0; j < g->DIMENSION; j++)
			{
				if (table[j][i] == '1')
				{
					shape.setFillColor(sf::Color::Yellow);
				}
				if (table[j][i] == '2')
				{
					shape.setFillColor(sf::Color::Red);
				}
				shape.setPosition(positionX, positionY);
				window.draw(shape);
				positionY = positionY + 50;

				shape.setFillColor(sf::Color::White);
				shape.setOutlineThickness(2);
				shape.setOutlineColor(sf::Color::Blue);
			}
			positionX = positionX + 70;
		}
		if (check1 == 0)
		{
			won = g->aiFunc();
			check1++;
			table = g->gameTable;
			window.clear();
			for (int i = 0; i < g->DIMENSION; i++)
			{
				positionY = 10;
				for (int j = 0; j < g->DIMENSION; j++)
				{
					if (table[j][i] == '1')
					{
						shape.setFillColor(sf::Color::Yellow);
					}
					if (table[j][i] == '2')
					{
						shape.setFillColor(sf::Color::Red);
					}
					shape.setPosition(positionX, positionY);
					window.draw(shape);
					positionY = positionY + 50;

					shape.setFillColor(sf::Color::White);
					shape.setOutlineThickness(2);
					shape.setOutlineColor(sf::Color::Blue);
				}
				positionX = positionX + 70;
			}
		}
		int col = 0;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int checkX = 0;
			int checkX2 = 70;
			sf::Vector2i position = sf::Mouse::getPosition(window);
			for (int i = 0; i<g->DIMENSION; i++)
			{
				if (position.x > checkX && position.x < checkX2)
				{
					col = i + 1;
				}
				checkX = checkX2;
				checkX2 = checkX2 + 72;
			}
		}
		positionX = 10;
		positionY = 10;
		if (col > 0 && col <= g->DIMENSION)
		{
			g->inputMouse(col);
			won2 = g->userFunc();
			table = g->gameTable;
			check1 = 0;
			for (int i = 0; i < g->DIMENSION; i++)
			{
				positionY = 10;
				for (int j = 0; j < g->DIMENSION; j++)
				{
					if (table[j][i] == '1')
					{
						shape.setFillColor(sf::Color::Yellow);
					}
					if (table[j][i] == '2')
					{
						shape.setFillColor(sf::Color::Red);
					}
					shape.setPosition(positionX, positionY);
					window.draw(shape);
					positionY = positionY + 50;

					shape.setFillColor(sf::Color::White);
					shape.setOutlineThickness(2);
					shape.setOutlineColor(sf::Color::Blue);
				}
				positionX = positionX + 70;
			}
		}
		sf::CircleShape s(70.f);

		shape.setFillColor(sf::Color::White);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(sf::Color::Blue);

		if (won == 2 && won2 == 1)
		{
			sprite.setTexture(im2);
			sprite.setPosition(80, 370);
			window.draw(sprite);
		}
		if (won == 2)
		{
			sprite.setTexture(image1);
			sprite.setPosition(80, 370);
			window.draw(sprite);
		}
		if (won2 == 1)
		{
			sprite.setTexture(image);
			sprite.setPosition(80, 370);
			window.draw(sprite);
		}
		window.display();
	}

}
int main()
{
	game *g = new game();
	cout << "Out strange minimax Algorithm works optimally at 7 or less dimension. Default Minimax depth = 2" << endl;
	cout << "Enter Dimension nxn";
	cin >> g->DIMENSION;
	cout << "Enter number of rings for winning criteria";
	cin >> g->WIN;
	//Runs the whole graphics scene
	GameGRAPHICS(g);
	return 1;
}
