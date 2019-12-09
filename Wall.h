#pragma once
#include "Object.h"
class Wall :
	public Object
{
public:
	
	//void collide(Wall& otherObject) override;
	//void collide(Object& otherObject) override;
	//float getRadius() override;
	bool collision(Object& otherObject, Controller &ctrl) override;
	void m_setCenter(int row, int col) override;
	void m_setColor(sf::Color &color) override;
	//virtual void collide(Wall& otherObject) ocverride;
	void m_setOrigin(float x, float y) override;
	void m_setPosition(float x, float y) override;
	void m_SetTexture() override;
	void setSize(int size) override;
	int getSize() const override;
	void m_draw(sf::RenderWindow &window) override;
	void m_setScale(int a, int b, int c, int d);
	void drawWall(sf::RenderWindow &window);
	
	//void setTexture();
	Wall();
	~Wall();
};

