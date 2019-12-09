#include "Ghost.h"
#include <iostream>
#include "Wall.h"
bool ghostdebug = 0;

bool Ghost::m_moveCharacter(Controller & ctrl)
{
	
	//float k = rand() % 6;
	//m_direction = Right;
	if (m_Clock.getElapsedTime().asSeconds() > 4)
	{
		m_direction = rand() % 4;
		//d::cout << "Oh yea" << std::endl;
		m_Clock.restart();
	}
	if (m_Clock.getElapsedTime().asSeconds() > 1)
	{
		if (numOfCollisions > 5)
		{
			if (smartGhost)
			{
				int tempr = rand() % 1;
				if (m_direction == 0 || m_direction == 1)
				{
					
					m_direction = 2 + tempr;
				}
				else
				{
					m_direction = 0 + tempr;
				}
				m_Clock.restart();
				numOfCollisions = 0;
			}
			else {
				//std::cout << "Too many collisions" << std::endl;
				m_direction = rand() % 4;
				m_Clock.restart();
				numOfCollisions = 0;
			}
		}
		//std::cout << "Oh yea";
		//m_Clock.restart();
	}
	
		switch (m_direction)
		{
		case Right:// Right
			//ctrl.isPacMoving() ? 
			m_sprite.move(m_speed, 0);
			//std::cout << m_sprite.getPosition().x;
			break;
		case Left: // Left
			m_sprite.move(-m_speed, 0);
			//ctrl.isPacMoving() ? m_sprite.move(-m_speed, 0) : 0;

			break;
		case Up:   // Up
			m_sprite.move(0, -m_speed);
			//ctrl.isPacMoving() ? m_sprite.move(0, -m_speed) : 0;

			break;
		case Down: // Down
			//ctrl.isPacMoving() ? m_sprite.move(0, m_speed) : 0;
			m_sprite.move(0, m_speed);
			break;
		default:
			break;

		}
		return false;
}

// Characters to character collision for ghost
bool Ghost::characterCollision(Characters & character, Controller & ctrl)
{

	return false;
}

bool Ghost::collision(Object & otherObject, Controller &ctrl)
{
	const type_info& objectType = typeid(otherObject);
	if (objectType == typeid(Wall)) 
	{
		Wall &wall = static_cast<Wall&>(otherObject);
		int tempDirection = m_direction;
		while (wall.m_sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
		{ 
			numOfCollisions++;
			if (tempDirection == Up)
			{
			m_sprite.move(0, 1);
			m_direction = Down;
			}
			else if (tempDirection == Down)
			{
			//std::cout << "Direction change";
			m_sprite.move(0, -1);
			m_direction = Up;
			}
			else if (tempDirection == Right)
			{
			//::cout << "Direction change";
				m_sprite.move(-1,0);
				m_direction = Left;
			}		
			else if (tempDirection == Left)
			{
			//std::cout << "Direction change";
			m_sprite.move(1,0);
			m_direction = Right;
			}
		}
		//return true;
	}

  return false;
}

bool Ghost::collisionTwo(Object & otherObject)
{
	const type_info& objectType = typeid(otherObject);
	if (objectType == typeid(Wall))
	{
		Wall &wall = static_cast<Wall&>(otherObject);
		int tempDirection = m_direction;
		if (wall.m_sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void Ghost::m_setCenter(int row, int col)
{
}



void Ghost::setSize(int size)
{
	m_size = size;
}

bool Ghost::isSmartGhost()
{
	return smartGhost;
}

void Ghost::m_setOrigin(float x, float y)
{
}

void Ghost::m_SetTexture()
{
	if (!m_texture.loadFromFile("spritesheet.png"))
	{
		//std::cout << "Error ";
	}
	m_sprite.setTexture(m_texture, true);
	m_sprite.setTextureRect(sf::IntRect(64, 164, 21, 21));
}

void Ghost::m_setScale(int w, int h, int r, int c)
{
	//m_sprite.setScale(4, 4);
	float test = float(w / c) / float(m_sprite.getTextureRect().width);
	float test2 = test*0.1;
	//m_sprite.getTextureRect().left;
	float t3 = float(h / r) / float(m_sprite.getTextureRect().height);
	float t4 = t3*0.1;
	// Makes x 20 percent smaller so its easier to get through narrow passages.
	test = test - test2;
	t3 = t3 - t4;
	m_sprite.setScale(test, t3);
	//std::cout << test << " " << t3 << std::endl;
}


int Ghost::getSize() const
{
	return m_size;
}


bool Ghost::m_move()
{
	if (ghostdebug)std::cout << "Ghost moving" << std::endl;
	//m_sprite.move(1, 0);
	return false;
}

void Ghost::m_draw(sf::RenderWindow & window)
{
	// Sprite sheet, 0-1 = UP
	//				 2-3 = DOWN
	//               4-5 = RIGHT
	//				 6-7 = LEFT
	// So if were moving up, if greater than 
	//So if were moving up, source is 6) 
	//int ghostAnimeSource;
	if (!switchUp) {
		if (m_direction == 0)
		{
			ghostAnimeSource = 6;
		}
		else if (m_direction == 1)
		{
			ghostAnimeSource = 4;
		}
		else if (m_direction == 2)
		{
			ghostAnimeSource = 0;
		}
		else if (m_direction == 3)
		{
			ghostAnimeSource = 2;
		}
	}
	else if (switchUp)
	{
		if (m_direction == 0)
		{
			ghostAnimeSource = 7;
		}
		else if (m_direction == 1)
		{
			ghostAnimeSource = 5;
		}
		else if (m_direction == 2)
		{
			ghostAnimeSource = 1;
		}
		else if (m_direction == 3)
		{
			ghostAnimeSource = 3;
		}
	}
	if (animeClock.getElapsedTime().asSeconds() > 0.08f)
	{
		if (switchUp)
			switchUp = false;
		else if(!switchUp)
			switchUp = true;
		//ghostAnimeSource++;
		/*animeSource++;
		if (animeSource > 2)
		{
		animeSource = 0;

		}*/
		animeClock.restart();
	}
	//0,21,42,84
	m_sprite.setTexture(m_texture, true);
	//m_sprite.setColor(m_color) : 0;
	//std::cout << "drawing ghost";
	
	m_sprite.setTextureRect(sf::IntRect(ghostAnimeSource*21, 122, 21, 21));
	window.draw(m_sprite);
	//ghostAnimeSource++;
	//ghostAnimeSource--;
}

void Ghost::m_setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void Ghost::m_setColor(sf::Color & color)
{
	m_sprite.setColor(color);
}

sf::Vector2f Ghost::getOriginalPosition()
{
	return m_originalPosition;
}

void Ghost::setOriginalPosition(float x, float y)
{
	m_originalPosition.x = x;
	m_originalPosition.y = y; 
	
}

Ghost::Ghost()
{
	int tempRand = rand() % 100;
	tempRand > 50 ? smartGhost = false : smartGhost = true;
	animeClock.restart();
	m_direction = rand() % 4;
	//std::cout << "direction" <<  m_direction;
	m_speed = rand() % 3;
	m_speed++;
	if (!m_texture.loadFromFile("spritesheet.png"))
	{
		std::cout << "Error " << std::endl << std::endl;
	}
}


Ghost::~Ghost()
{
	
}
