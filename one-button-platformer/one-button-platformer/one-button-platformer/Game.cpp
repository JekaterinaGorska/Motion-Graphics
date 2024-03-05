#include "Game.h"
#include <iostream>

//Author: Katrina Gorska

//////////////////////////////////////////////////////////////////////////////////////////
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "One Button Platform " },
	m_exitGame{false} //when true game will exit
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////
Game::~Game()
{
}

//////////////////////////////////////////////////////////////////////////////////////////
//void Game::run()
//{	
//	sf::Clock clock;
//	sf::Time timeSinceLastUpdate = sf::Time::Zero;
//	const float fps{ 60.0f };
//	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
//	while (m_window.isOpen())
//	{
//		processEvents(); // as many as possible
//		timeSinceLastUpdate += clock.restart();
//		while (timeSinceLastUpdate > timePerFrame)
//		{
//			timeSinceLastUpdate -= timePerFrame;
//			processEvents(); // at least 60 fps
//			update(timePerFrame); //60 fps
//		}
//		render(); // as many as possible
//	}
//}

void Game::run()
{
	
	


		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


		sf::Time timeSinceLastUpdate = sf::Time::Zero;


		sf::Clock clock;

		clock.restart();
		while (m_window.isOpen())
		{

			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
			}


			timeSinceLastUpdate += clock.restart();


			if (timeSinceLastUpdate > timePerFrame)
			{

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{

						m_level[row][col].move(-3.7, 0);
					}

				}

			/*	for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (levelData[row][col] == 4 && m_player.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
						{
							velocityY = -15.0;
						}
					}
				}*/


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
				{
					velocityY = -11.5;
				}

				velocityY = velocityY + gravity;
				m_player.move(0, velocityY);

				updateAnimation();

				gravity = 0.6;

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (velocityY >= 0)
						{
							if (levelData[row][col] == 1)
							{
								
								if (m_player.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
								{
									if (m_player.getPosition().y < m_level[row][col].getPosition().y)
									{
										gravity = 0;
										velocityY = 0;
										m_player.setPosition(m_player.getPosition().x, m_level[row][col].getPosition().y);
										m_player.move(0, -m_player.getGlobalBounds().height);
										break;
									}
									else {
										init();
									}
								}


							}

						}
						if (velocityY < 0)
						{
							if (levelData[row][col] == 1)
							{
								if (m_player.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
								{
									init();
								}

							}

						}
						if (levelData[row][col] == 2)
						{
							if (m_player.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 4)
						{
							if (m_player.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 3)
						{
							if (m_player.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
					}
				}

				if (m_player.getPosition().y > 600)
				{
					init();
				}

				render();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	
};


//////////////////////////////////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::updateAnimation()
{
	int frameWidth = m_playerTexture.getSize().x / frameCount;
	int frameHeight = m_playerTexture.getSize().y;

	sf::Time animationDelay = sf::milliseconds(200);
	static sf::Clock animatedClock;
	if (animatedClock.getElapsedTime() >= animationDelay)
	{
		currentFrame = (currentFrame + 1) % frameCount;
		m_player.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
		animatedClock.restart();
	}
}

void Game::init()
{
	m_view = m_window.getDefaultView();
	m_player.setSize(sf::Vector2f(80, 80));
	m_player.setPosition(160, 500);
	if (!m_playerTexture.loadFromFile("ASSETS//IMAGES//playerSpritesheet.png"))
	{
		std::cout << "problem loading spritesheet :(" << std::endl;
		return;
	}
	m_player.setTexture(&m_playerTexture);
	if (!m_tile1Texture.loadFromFile("ASSETS//IMAGES//safe.png"))
	{
		std::cout << "problem loading level 1 tile :(" << std::endl;
		return;
	}

	if (!m_tile2Texture.loadFromFile("ASSETS//IMAGES//enemy.png"))
	{
		std::cout << "problem loading level 2 tile :(" << std::endl;
		return;
	}

	if (!m_tile3Texture.loadFromFile("ASSETS//IMAGES//milk.png"))
	{
		std::cout << "problem loading level 3 tile :(" << std::endl;
		return;
	}

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (levelData[row][col] == 1)
			{
				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);
				//m_level[row][col].setFillColor(sf::Color::Red);
				m_level[row][col].setTexture(&m_tile1Texture);

			}
			if (levelData[row][col] == 0)
			{
				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);
				m_level[row][col].setFillColor(sf::Color::Black);

			}
			if (levelData[row][col] == 2)
			{
				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);
				//m_level[row][col].setFillColor(sf::Color::Blue);
				m_level[row][col].setTexture(&m_tile2Texture);
			}
			if (levelData[row][col] == 4)
			{
				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);
				m_level[row][col].setFillColor(sf::Color::Magenta);
			}
			if (levelData[row][col] == 3)
			{
				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);
				//m_level[row][col].setFillColor(sf::Color::Green);
				m_level[row][col].setTexture(&m_tile3Texture);
			}
		}
		std::cout << std::endl;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear();
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{

			m_window.draw(m_level[row][col]);
		}

	}
	if (m_player.getPosition().y > 600)
	{
		init();
	}
	m_window.draw(m_player);
	m_window.display();
}

//////////////////////////////////////////////////////////////////////////////////////////



