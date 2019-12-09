#pragma once
#include "Object.h"
class Controller;
#include "SFML\Graphics.hpp"

enum Direction { Right, Left, Up, Down };
class Characters :
	public Object
{
public:
	virtual bool characterCollision(Characters& character, Controller &ctrl);
	virtual void setOriginalPosition(float x, float y) = 0;
	virtual void collide(Object &object);
	virtual void collide(Wall &object);
	// override;
	virtual bool m_move(void);
	virtual bool m_moveCharacter(Controller &ctrl) = 0;
	virtual bool isSmartGhost();
	virtual sf::Vector2f getOriginalPosition() = 0;
	virtual int getSpeed();
	Characters();
	~Characters();
protected:
	// For resetting the original position after board reset.
	sf::Vector2f m_originalPosition;
	int m_direction;
	int m_speed;
	sf::Vector2f m_Center;
	sf::Clock m_Clock;
	sf::Time m_TimeElapsed;
};

