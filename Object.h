#pragma once

//#include "PacMan.h"
class PacMan; // forward declarations
class Board;
class Wall;
class Controller;
//class Ghost;
//class Wall;
//class Cookie;
#include "SFML\Graphics.hpp"
enum {Pac, Brick};
class Object
{
public:
	
	//virtual void collide(Object& otherObject) = 0;
	//virtual void collide(Wall& otherObject) = 0;

	virtual bool collision(Object& otherObject, Controller &ctrl) = 0;
	//virtual void collide(Wall& otherObject) = 0;
	//virtual void collide(Wall& otherObject) = 0;
	//virtual void collide(Cookie& otherobject) = 0;
	
	sf::Color m_color;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	//sf::Color m_fillcolor;

	
	int m_size;
	Object();
	~Object();
	
	virtual void m_setScale(int w, int h, int r, int c) = 0;
	virtual void m_setPosition(float x, float y) = 0;
	virtual void m_setOrigin(float x, float y) = 0;
	virtual void m_setColor(sf::Color &color) = 0;
	virtual void m_setCenter(int row, int col) = 0;
	virtual void setSize(int size);
	virtual int getSize() const; 
	virtual void m_SetTexture() = 0;
	virtual void m_draw(sf::RenderWindow &window) = 0;
	virtual sf::Vector2f getCenter(Object &object);
};

