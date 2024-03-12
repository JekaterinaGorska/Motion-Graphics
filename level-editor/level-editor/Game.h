//Author: Jekaterina Gorska
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window; 
	sf::Font m_ArialBlackfont; 
	
	bool m_exitGame; 
};

#endif

