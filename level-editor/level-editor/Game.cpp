
//Jekaterina Gorska
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Level Editor" },
	m_exitGame{ false } //when true game will exit
{

	setUpLevel(); // load texture
}


Game::~Game()
{
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	switch (t_event.key.code) {
	case sf::Keyboard::Num0:
		selectedLevel = 0;
		break;
	case sf::Keyboard::Num1:
		selectedLevel = 1;
		break;
	case sf::Keyboard::Num2:
		selectedLevel = 2;
		break;
	case sf::Keyboard::Num3:
		selectedLevel = 3;
		break;
	case sf::Keyboard::Num4:
		selectedLevel = 4;
		break;
	case sf::Keyboard::Num5:
		selectedLevel = 5;
		break;
	default:
		break;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (editing)
	{
		editingLevel();
	}
	else if (playing)
	{
		updateLevel();
		
	}



}


void Game::render()
{
	m_window.clear(sf::Color::White);
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			m_window.draw(level[col][row]);
		}
	}
	if (editing)
	{
		for (int i = 0; i < 6; i++)
		{
			m_window.draw(levelUI[i]);
		}
	}
	
	m_window.display();
}


void Game::setUpLevel()
{
	
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (levelData[col][row] == 1)
			{
				level[col][row].setSize(sf::Vector2f(70, 30));
				level[col][row].setPosition(row * 70, col * 30);
				level[col][row].setFillColor(sf::Color::Red);
			}
			if (levelData[col][row] == 0)
			{
				level[col][row].setSize(sf::Vector2f(70, 30));
				level[col][row].setPosition(row * 70, col * 30);
				level[col][row].setFillColor(sf::Color::Black);
				level[col][row].setOutlineColor(sf::Color::White);
				level[col][row].setOutlineThickness(1);
			}
			if (levelData[col][row] == 2)
			{
				level[col][row].setSize(sf::Vector2f(70, 30));
				level[col][row].setPosition(row * 70, col * 30);
				level[col][row].setFillColor(sf::Color::Blue);
			}
			if (levelData[col][row] == 3)
			{
				level[col][row].setSize(sf::Vector2f(70, 10));
				level[col][row].setPosition(row * 70, col * 30);
				level[col][row].setFillColor(sf::Color::Yellow);
			}
			if (levelData[col][row] == 4)
			{
				level[col][row].setSize(sf::Vector2f(70, 30));
				level[col][row].setPosition(row * 70, col * 30);
				level[col][row].setFillColor(sf::Color::White);
			}
			if (levelData[col][row] == 5)
			{
				level[col][row].setSize(sf::Vector2f(70, 30));
				level[col][row].setPosition(row * 70, col * 30);
				level[col][row].setFillColor(sf::Color::Green);
			}
		}
		std::cout << std::endl;
	}
}

void Game::editingLevel()
{
	if (editing)
	{
		uiPressed = false;
		for (int i = 0; i < 6; ++i) {
			levelUI[i].setSize(sf::Vector2f(100, 50));
			levelUI[i].setPosition(120 * i, 20);
			if (i == 0)
			{
				levelUI[i].setFillColor(sf::Color::Black);
			}
			if (i == 1)
			{
				levelUI[i].setFillColor(sf::Color::Red);
			}
			if (i == 2)
			{
				levelUI[i].setFillColor(sf::Color::Blue);
			}
			if (i == 3)
			{
				levelUI[i].setFillColor(sf::Color::Yellow);
			}
			if (i == 4)
			{
				levelUI[i].setFillColor(sf::Color::White);
			}
			if (i == 5)
			{
				levelUI[i].setFillColor(sf::Color::Green);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			playing = true;
			editing = false;
			resetLevel();
		}
		for (int i = 0; i < 6; ++i)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (levelUI[i].getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y))
				{
					selectedLevel = i;
					uiPressed = true;
				}
			}
		}
		if (!uiPressed)
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{

					if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						if (levelData[col][row] >= 1)
						{
							if (level[col][row].getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y))
							{
								levelData[col][row] = 0;
								level[col][row].setFillColor(sf::Color::Black);
								level[col][row].setOutlineColor(sf::Color::White);
								level[col][row].setOutlineThickness(1);
							}
						}
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (levelData[col][row] >= 0)
						{
							if (level[col][row].getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y))
							{
								levelData[col][row] = selectedLevel;
								if (selectedLevel == 0)
								{
									level[col][row].setFillColor(sf::Color::Black);
								}
								else if (selectedLevel == 1)
								{
									level[col][row].setFillColor(sf::Color::Red);
								}
								else if (selectedLevel == 2)
								{
									level[col][row].setFillColor(sf::Color::Blue);
								}
								else if (selectedLevel == 3)
								{
									level[col][row].setFillColor(sf::Color::Yellow);
								}
								else if (selectedLevel == 4)
								{
									level[col][row].setFillColor(sf::Color::White);
								}
								else if (selectedLevel == 5)
								{
									level[col][row].setFillColor(sf::Color::Green);
								}
							}
						}
					}
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					level[col][row].move(5, 0);
					
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{
					level[col][row].move(-5, 0);
					
				}

			}
		}
	}
}


void Game::resetLevel()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			level[col][row].setPosition(row * 70, col * 30);
		}
	}
}

void Game::updateLevel()
{
	if (playing)
	{
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[col][row].move(-5, 0);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			playing = false;
			editing = true;
		}
	}
}
