#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void display(sf::RenderWindow &window);
	void initialize();
	void updateOutline(sf::Vector2f mousecoord);
	bool m_Contains(sf::Vector2f mousecoord);
private:
	// Three buttons, 1)  Play Game
	//				  2)  Instructions
	//				  3)  Exit
	
	std::vector<sf::RectangleShape> m_buttons;
	sf::Texture texture[4];
};

