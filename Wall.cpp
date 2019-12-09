#include "Wall.h"
#include <iostream>







bool Wall::collision(Object & otherObject, Controller & ctrl)
{
	return false;
}

void Wall::m_setCenter(int row, int col)
{
}

void Wall::m_setColor(sf::Color & color)
{
	m_sprite.setColor(color);
}



void Wall::m_setOrigin(float x, float y)
{
}

void Wall::m_setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void Wall::m_SetTexture()
{
	
	if (!m_texture.loadFromFile("wall.png"))
	{
		std::cout << "Error " << std::endl << std::endl;
	}
	//std::cout << "Calling set texture" << std::endl;
	m_sprite.setTexture(m_texture);
	//m_sprite.setScale(0.3, 0.3);
	//m_sprite.setTextureRect(sf::IntRect(16, 16, 56, 56));
	//m_sprite.setScale(5, 5);
}

void Wall::setSize(int size)
{
}

int Wall::getSize() const
{
	return 0;
}

void Wall::drawWall(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}


void Wall::m_draw(sf::RenderWindow & window)
{
	m_sprite.setTexture(m_texture);
	window.draw(m_sprite);
}

void Wall::m_setScale(int w, int h, int r, int c)
{
	//m_sprite.setScale(0.25, 0.25);
	//double scaler = (w / c) / m_sprite.getTextureRect().width;
	//float scaler2 = (h / r) / m_sprite.getTextureRect().height;
	//std::cout << m_sprite.getTextureRect().width << " " << scaler2 << std::endl;
	//800/15 = 55? So, m_sprite.width * X = 55, x = 55/width
	m_sprite.setScale(float(w / c) / float(m_sprite.getTextureRect().width), (h / r) / float(m_sprite.getTextureRect().height));
}

Wall::Wall()
{
	if (!m_texture.loadFromFile("wall.png"))
	{
		std::cout << "Error " << std::endl << std::endl;
	}
}


Wall::~Wall()
{
}
