 //Pacman, First project Motion Graphics

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "First Graphics in C++");

	sf::Font font;
	if (!font.loadFromFile("ASSETS/FONTS/bomb.ttf"))
	{
		std::cout << "error loading from file" << std::endl;
	}

	int score = 0;
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineColor(sf::Color::Red);
	scoreText.setOutlineThickness(2);
	scoreText.setPosition(10, 10);

	sf::Text text;
	text.setFont(font);
	text.setString("Not Pacman"); //string to display
	text.setCharacterSize(60); //in pixels
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineColor(sf::Color::Red);
	text.setOutlineThickness(2);
	text.setPosition(230, 150);

	bool gameOver = false;

	
	sf::RectangleShape pacman;
	float pacmanWidth = 50;
	float pacmanHeight = 50;

	pacman.setSize(sf::Vector2f(pacmanWidth, pacmanHeight));
	pacman.setFillColor(sf::Color::Green);
	pacman.setPosition(200, 500);
	pacman.setOrigin(sf::Vector2f(pacmanWidth * 0.5, pacmanHeight * 0.5));

	sf::RectangleShape ghost;
	float ghostWidth = 50;
	float ghostHeight = 70;

	ghost.setSize(sf::Vector2f(ghostWidth, ghostHeight));
	ghost.setFillColor(sf::Color::Red);
	ghost.setPosition(550, 363 );
	//ghost.setOrigin(sf::Vector2f(ghostWidth * 0.5, ghostHeight * 0.5));


	sf::RectangleShape rectangleBorder;
	float borderWidth = 800;
	float borderHeight = 15;

	rectangleBorder.setSize(sf::Vector2f(borderWidth, borderHeight));
	rectangleBorder.setFillColor(sf::Color::Blue);
	rectangleBorder.setPosition(0, 350 - 15);

	sf::RectangleShape rectangleBorder2;
	float borderWidth2 = 800;
	float borderHeight2 = 15;

	rectangleBorder2.setSize(sf::Vector2f(borderWidth2, borderHeight2));
	rectangleBorder2.setFillColor(sf::Color::Blue);
	rectangleBorder2.setPosition(0, 445);



	srand(time(NULL));

	const int numCircles = 28;
	sf::CircleShape circles[numCircles];

	for (int index = 0; index < numCircles; index++)
	{
		circles[index].setFillColor(sf::Color::Yellow);
		circles[index].setRadius(10);
		circles[index].setPosition(42 * index, 400);
		circles[index].setOrigin(sf::Vector2f(10, 10));
	}

	float xPosition = 300;
	float yPosition = 400;
	float speed = 2;
	bool spacePressed = false;

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	sf::Clock clockForFrameRate;

	clockForFrameRate.restart();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		timeSinceLastUpdate += clockForFrameRate.restart();


		if (timeSinceLastUpdate > timePerFrame)
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (spacePressed == false)
				{
					speed *= -1;
					spacePressed = true;
					if (gameOver == true) {
						gameOver = false;
					}
				} 
			}
			else {
				spacePressed = false;
			}

			xPosition += speed;

			if (xPosition < 0)
			{
				xPosition = window.getSize().x;
			}
			else if (xPosition > window.getSize().x)
			{
				xPosition = 0;
			}


			pacman.setPosition(xPosition, yPosition);

			sf::Vector2f pacmanPosition = pacman.getPosition();
			sf::Vector2f ghostPosition = ghost.getPosition();

			
			if (pacmanPosition.x > ghostPosition.x)
			{
				ghost.move(1.0f, 0.0f);
			}
			else 
			{
				ghost.move(-1.0f, 0.0f);
			}


			for (int index = 0; index < numCircles; index++)
			{
				if (pacman.getGlobalBounds().intersects(circles[index].getGlobalBounds()))
				{
					circles[index].setPosition(1000, 1000);
					score++;
					scoreText.setString("Score = " + std::to_string(score));
				}
			}

			for (int index = 0; index < numCircles; index++)
			{
				if (pacman.getGlobalBounds().intersects(circles[index].getGlobalBounds()))
				{
					circles[index].setPosition(1000, 1000);

				}

			}


			if (pacman.getGlobalBounds().intersects(ghost.getGlobalBounds())) {
				window.close();
				//gameOver = true;
			}


			window.clear();

			window.draw(scoreText);

			//if (gameOver)
		
				for (int index = 0; index < numCircles; index++)
				{

					window.draw(circles[index]);

				}

				window.draw(text);
				window.draw(pacman);
				window.draw(ghost);
				window.draw(rectangleBorder);
				window.draw(rectangleBorder2);
			
			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}




