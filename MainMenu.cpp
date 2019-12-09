#include "MainMenu.h"
#include <iostream>

sf::RectangleShape background(sf::Vector2f(800, 600));
MainMenu::MainMenu()
{
	
}


MainMenu::~MainMenu()
{
}

void MainMenu::display(sf::RenderWindow &window)
{
	window.draw(background);
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		window.draw(m_buttons.at(i));
	}
}

void MainMenu::initialize()
{
	
	sf::RectangleShape playButton(sf::Vector2f(300, 200));
	sf::RectangleShape InstructionButton(sf::Vector2f(300, 200));

	if (texture[0].loadFromFile("pacback.png"))
	{
	  //std::cout << "Sucess";
	}
	if (texture[1].loadFromFile("thnew.png"))
	{
		//std::cout << "Sucess";
	}
	if (texture[2].loadFromFile("purpleplay.png"))
	{
		//std::cout << "Sucess";
	}
	if (texture[3].loadFromFile("instructionButton.png"))
	{
		//std::cout << "Sucess";
	}
	
	

	background.setTexture(&texture[0]);
	
	InstructionButton.setTexture(&texture[1]);
	InstructionButton.setPosition(485, 50);
	playButton.setTexture(&texture[2]);
	//playButton.setFillColor(sf::Color::Black);
	//playButton.setScale(5, 5);
	playButton.setPosition(145, 50);
	InstructionButton.setScale(0.5, 0.5);
	
	playButton.setScale(0.5, 0.5);
	//playButton.setOutlineColor(sf::Color::White);
	//playButton.setOutlineThickness(5.0f);
	//InstructionButton.setOutlineColor(sf::Color::White);
	//InstructionButton.setOutlineThickness(5.0f);
	//playButton.setTexture(&texture[1]);
	//m_buttons.push_back(background);
	m_buttons.push_back(playButton);
	m_buttons.push_back(InstructionButton);
	
}

void MainMenu::updateOutline(sf::Vector2f mousecoord)
{
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons.at(i).getGlobalBounds().contains(mousecoord))
		{

			
			
			m_buttons.at(i).setOutlineColor(sf::Color::Yellow);
			m_buttons.at(i).setOutlineThickness(5.0f);
			//std::cout << "Contains";
		}
		else
		{
			
			m_buttons.at(i).setOutlineColor(sf::Color::Transparent);
			m_buttons.at(i).setOutlineThickness(5.0f);
			//std::cout << "Not Contains";
		}
		
	}
}

bool MainMenu::m_Contains(sf::Vector2f mousecoord)
{
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		//std::cout << "Balls";
		if (m_buttons.at(i).getGlobalBounds().contains(mousecoord))
		{
			if (i == 1)
				exit(1);
			std::cout << i;
			//std::cout << std::endl;
			return true;
		}
	}
	return false;
	
}
