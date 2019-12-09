#pragma once
#include "Characters.h"
//#include "Wall.h"
class PacMan :
	public Characters
{
public:
	bool m_moveCharacter(Controller &ctrl) override;
	bool weMoving = true;
	//void collide(Object& otherObject) override;
	//void collide(Wall& otherObject) override;
	bool characterCollision(Characters& character, Controller &ctrl) override;
	bool collision(Object& otherObject, Controller &ctrl) override;
	float getRadius();

	void m_setCenter(int row, int col) override;
	void setSize(int size) override;
	int getSize() const override;
	int getSpeed() override;
	//void collide(Wall& otherObject) override;
	void m_setOrigin(float x, float y) override;
	void m_SetTexture() override;
	void m_setScale(int w, int h, int r, int c) override;
	bool m_move() override;
	void m_draw(sf::RenderWindow &window) override;
	void m_setPosition(float x, float y) override;
	void drawPac(sf::RenderWindow &window);
	void m_setColor(sf::Color &color) override;
	void activatePower();
	void activatePoison();
	void deActivatePower();
	void deActivatePoison();
	sf::Vector2f getCenter(Object &object) override;
	sf::Vector2f getOriginalPosition() override;
	void setOriginalPosition(float x, float y) override;
	PacMan();
	~PacMan();
private:
	bool pac_Powered = false;
	bool pac_Poisoned = false;
	int animeSource = 0;
	sf::Clock animeClock;
	
	
	
};

