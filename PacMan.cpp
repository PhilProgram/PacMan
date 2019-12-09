#include "PacMan.h"
#include "Ghost.h"
#include <SFML/Audio.hpp>
#include "Wall.h"
#include <iostream>
#include "Board.h"
#include "Controller.h"
#include "Cookie.h"
sf::SoundBuffer chomp_buffer;
sf::Sound sound;
sf::SoundBuffer death_buffer;
sf::SoundBuffer poison_buffer;
sf::SoundBuffer power_buffer;

bool pacdebug = 0;

bool PacMan::m_moveCharacter(Controller &ctrl)
{
	
	
	
	
	float temp = m_speed;
	if (pac_Powered == true)
	{
		if (m_Clock.getElapsedTime().asSeconds() > 5.0f)
		{
			deActivatePower();
		}
			// change speed
	}
	if (pac_Poisoned == true)
	{
		if (m_Clock.getElapsedTime().asSeconds() > 3.0f)
		{
			deActivatePoison();
		}
		// change speed
	}
	//std::cout << m_speed;
	m_direction = ctrl.getPacDirection();
	/*temp = m_speed;
	if (m_Clock.getElapsedTime().asSeconds() > 9.0f)
	{
		m_Clock.restart();
	}
	else
	{
		temp = temp + m_Clock.getElapsedTime().asSeconds();
	}
	std::cout << temp << std::endl;*/
	switch(m_direction)
		{
		
		case Right:// Right
			if (ctrl.isPacMoving())
			{
				m_sprite.move(temp, 0);
			} 
			
			break;
		case Left: // Left
			if (ctrl.isPacMoving())
			{
				m_sprite.move(-temp, 0);
			} 
			
			break;
		case Up:   // Up
			if (ctrl.isPacMoving())
			{
				m_sprite.move(0, -temp);
			}
			
			break;
		case Down: // Down
			if (ctrl.isPacMoving()) {
				m_sprite.move(0, temp);
			}
			
			break;
		default:
			break;
		
		}
	//weMoving ? ctrl.pacIsMoving() : ctrl.pacNotMoving();
	return false;
}





bool PacMan::characterCollision(Characters & character, Controller & ctrl)
{
	const type_info& objectType = typeid(character);
	if (objectType == typeid(Ghost))
	{

		Ghost &ghost = static_cast<Ghost&>(character);
		if (ghost.m_sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
		{
			//Display game over text
			sound.setBuffer(death_buffer);
			sound.play();
			ctrl.pacNotMoving();
			ctrl.initDeath();
			//std::cout << "Pacman hitting ghost";
			return true;
		}

		// process a SpaceShip-SpaceShip collision;
	}
	return false;
}

bool PacMan::collision(Object & otherObject, Controller &ctrl)
{
	
	const type_info& objectType = typeid(otherObject);
	
	if (objectType == typeid(Wall))
	{
		Wall &wall = static_cast<Wall&>(otherObject);
		//std::cout << "Pac hitting wall";
		while (wall.m_sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
		{
			ctrl.pacNotMoving();
			switch (ctrl.getPacDirection())
			{
			case Left:
				m_sprite.move(1, 0);
				break;
			case Right:
				m_sprite.move(-1, 0);
				break;
			case Up:
				m_sprite.move(0, 1);
				break;
			case Down:
				m_sprite.move(0, -1);
				break;
			default:
				break;
			};

			//std::cout << "Pac hitting wall";
		}
	}
	else if (objectType == typeid(Cookie)) 
	{
			//std::cout << "collision type cookie";
			Cookie &cookie = static_cast<Cookie&>(otherObject);

			// distance from two centers
			//
			sf::Vector2f pacPos{ m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 2 };
			sf::Vector2f cookiePos{ cookie.m_sprite.getPosition().x + cookie.m_sprite.getGlobalBounds().width / 2, cookie.m_sprite.getPosition().y + cookie.m_sprite.getGlobalBounds().height / 2 };
			float distance = sqrt((pacPos.x - cookiePos.x)*(pacPos.x - cookiePos.x) + (pacPos.y - cookiePos.y)*(pacPos.y - cookiePos.y));
			
			//std::cout << distance << " " << getRadius() << std::endl;
			//if (cookie.m_sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
			if(distance<getRadius()*2)
			{
				
				if (cookie.m_checkPowerUp())
				{
					sound.setBuffer(power_buffer);
					sound.play();
					//std::cout << "Power up " << std::endl;
					activatePower();
				}
				if (cookie.m_checkPoison())
				{
					sound.setBuffer(poison_buffer);
					sound.play();
					//std::cout << "Poison" << std::endl;
					activatePoison();
				}
				if (!cookie.m_checkPoison() && !cookie.m_checkPowerUp())
				{
					sound.setBuffer(chomp_buffer);
					sound.play();
					ctrl.incrCookies();
					ctrl.updateScore();
				}
				// Check which cookie is being collided 
				// 1. Normal 2. Powerup 3. Normal
				// PacClock.Restart
				// Then if power up ? if packClock time < 5 speed = 
				// 2- percent more : else, powerup false;
				// Good cookie? Power up activate
				// Bad cookie? Poison activated
			//	std::cout << "Pacman hitting cookie";
				// Cookie will be popped
				return true;
			}
			// process a SpaceShip-SpaceShip collision;
		}
		// process a SpaceShip-SpaceStation collision;
	
	return false;
}

float PacMan::getRadius()
{
	
	
	float a = m_sprite.getTextureRect().height*m_sprite.getTextureRect().height;
	float b = m_sprite.getTextureRect().width*m_sprite.getTextureRect().width;
	float c = a + b;
	c = sqrt(c)/2;
	return c;
	//m_sprite.getOrigin();
}

void PacMan::m_setCenter(int x, int y)
{
	m_Center.x = x + (m_sprite.getTextureRect().width / 2);
	m_Center.y = y + (m_sprite.getTextureRect().height / 2);
	//std::cout << "Center: " << m_Center.x << " " << m_Center.y << std::endl;
	//m_Center{ x + (m_sprite.getTextureRect().width / 2),  };
}

void PacMan::setSize(int size)
{
	m_size = size;
}

int PacMan::getSize() const
{
	return m_size;
}

int PacMan::getSpeed()
{
	return m_speed;
}

//void PacMan::collide(Wall & otherObject)
//{
//}



void PacMan::m_setOrigin(float x, float y)
{
	m_sprite.setOrigin(x, y);
}

void PacMan::m_SetTexture()
{//
	
	if (!m_texture.loadFromFile("pacsprite.png"))
	{
		std::cout << "Error ";
	}  
	m_sprite.setTexture(m_texture, true);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 12, 16));
	
	//m_sprite.setScale(10, 10);
}

void PacMan::m_setScale(int w, int h, int r, int c)
{
	//m_sprite.setScale(4, 4);
	
	//float scaler = (w / c) / float(m_sprite.getTextureRect().width);
	//float scaler2 = (h / r) / m_sprite.getTextureRect().height;
	//std::cout << scaler << " " << scaler2 << std::endl;
	float test = float(w / c) / float(m_sprite.getTextureRect().width);
	float test2 = test*0.45;

	float t3 = float(h / r) / float(m_sprite.getTextureRect().height);
	float t4 = t3*0.45;
	// Makes x 20 percent smaller so its easier to get through narrow passages.
	test = test - test2;
	t3 = t3 - t4;
	m_sprite.setScale(test, t3 );
	//std::cout << test << " " << t3 << std::endl;
}

bool PacMan::m_move()
{
	
	//if (pacdebug)std::cout << "Pacman moving" << std::endl;
	//pacMoving ? m_sprite.move(0, 1) : 0;
	return false;
}

void PacMan::m_draw(sf::RenderWindow & window)
{
	//sourceX,sourceY
	m_sprite.setTexture(m_texture, true);
	if (animeClock.getElapsedTime().asSeconds() > 0.08f)
	{
		animeSource = ++animeSource%3 ;
		/*animeSource++;
		if (animeSource > 2)
		{
			animeSource = 0;
			
		}*/
		animeClock.restart();
	}
	m_sprite.setTextureRect(sf::IntRect(animeSource*16, m_direction*16, 16, 16));
	//std::cout << "Drawing pac";
	//m_sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
	
	window.draw(m_sprite);
}

void PacMan::m_setPosition(float x, float y)
{
	m_sprite.setPosition(x + m_sprite.getGlobalBounds().width / 2, y + m_sprite.getGlobalBounds().height / 2);
	//m_sprite.setTextureRect(sf::IntRect(0, 0, 12, 16));
	
}

void PacMan::drawPac(sf::RenderWindow &window)
{
	
	//m_sprite.setTexture(m_texture);
	window.draw(m_sprite);
}

void PacMan::m_setColor(sf::Color & color)
{
	m_sprite.setColor(color);
}

void PacMan::activatePower()
{
	float k;
	//ife greater than max power? no 
	if (m_speed > 18) {
		pac_Powered = true;
		return;
	}
	if (m_speed < 4)
	{
		k = m_speed*1.2;
		m_speed = m_speed + k;
	}
	else
	{
		k = m_speed*0.3;
		m_speed = m_speed + k;
	}
	m_Clock.restart();
	pac_Powered = true;
	
}

void PacMan::activatePoison()
{
	float k;
	if (m_speed < 2)
	{
		pac_Poisoned = true;
		return;
	}
	m_Clock.restart();
	pac_Poisoned = true;

	/*k = m_speed*0.2;
	m_speed = m_speed - k;
	*/
	m_speed *= 0.8;
}

void PacMan::deActivatePower()
{
	pac_Powered = false;
	m_speed = 4;
}

void PacMan::deActivatePoison()
{
	m_speed = 4;
	pac_Poisoned = false;
}

sf::Vector2f PacMan::getCenter(Object & object)
{
	return sf::Vector2f{ m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 2 };
}

sf::Vector2f PacMan::getOriginalPosition()
{
	return m_originalPosition;
}



void PacMan::setOriginalPosition(float x, float y)
{
	m_originalPosition.x = x;
	m_originalPosition.y = y;
}

PacMan::PacMan()
{
	animeClock.restart();
	m_Clock.restart();
	m_direction = 0;
	m_speed = 4;
	if (!chomp_buffer.loadFromFile("pacman_eatfruit.wav"))
	{

	}
	if (!death_buffer.loadFromFile("pacman_death.wav"))
	{

	}
	if (!power_buffer.loadFromFile("powerup.wav"))
	{

	}
	if (!poison_buffer.loadFromFile("poison.wav"))
	{

	}
	// load something into the sound buffer...

	
	
	//std::cout << "pacman_speed: " << m_speed << std::endl;
}


PacMan::~PacMan()
{
}
