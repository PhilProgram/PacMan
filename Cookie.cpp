#include "Cookie.h"




bool Cookie::collision(Object & otherObject, Controller & ctrl)
{
	return false;
}

void Cookie::m_setPosition(float x, float y)
{
	m_sprite.setPosition(x+m_sprite.getGlobalBounds().width/2, y+m_sprite.getGlobalBounds().height/2);
	//m_sprite.setOrigin(x + (m_sprite.getTextureRect().width / 2), y + (m_sprite.getTextureRect().height / 2));
	// set center - x+m_sprite.getGlobalRect().width/2
}

void Cookie::m_SetTexture()
{
	if (!m_texture.loadFromFile("cookie.png"))
	{
		//std::cout << "Error " << std::endl << std::endl;
	}
	//std::cout << "Calling set texture" << std::endl;
	m_sprite.setTexture(m_texture);
}

void Cookie::setSize(int size)
{
}

int Cookie::getSize() const
{
	return 0;
}

void Cookie::m_draw(sf::RenderWindow & window)
{
	m_sprite.setTexture(m_texture);
	window.draw(m_sprite);
}

void Cookie::m_setScale(int w, int h, int r, int c)
{
	float test = float(w / c) / float(m_sprite.getTextureRect().width);
	float test2 = test*0.4;

	float t3 = float(h / r) / float(m_sprite.getTextureRect().height);
	float t4 = t3*0.4;
	// Makes x 20 percent smaller so its easier to get through narrow passages.
	test = test - test2;
	t3 = t3 - t4;
	m_sprite.setScale(test, t3);
	//m_sprite.setScale(float(w / r) / float(m_sprite.getTextureRect().width), (h / c) / float(m_sprite.getTextureRect().height));
}

void Cookie::m_setCenter(int row, int col)
{
}

void Cookie::m_setColor(sf::Color & color)
{
	m_sprite.setColor(color);
}

void Cookie::m_setOrigin(float x, float y)
{
	m_sprite.setOrigin(x+(m_sprite.getTextureRect().width/2), y - (m_sprite.getTextureRect().height/2));
}

void Cookie::m_poisoned()
{
	m_poison = true;
}

void Cookie::m_powerup()
{
	m_powerUp = true;
}

bool Cookie::m_checkPowerUp()
{

	return m_powerUp;
}

bool Cookie::m_checkPoison()
{
	return m_poison;
}

sf::Vector2f Cookie::getCenter(Object & object)
{
	return sf::Vector2f();
}

Cookie::Cookie()
{
}


Cookie::~Cookie()
{
}
