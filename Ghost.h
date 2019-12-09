#pragma once
#include "Characters.h"
class Ghost :
	public Characters 
{
public:
	bool m_moveCharacter(Controller &ctrl) override;

	//void collide(Wall& otherObject) override;
	//void collide(Object& otherObject) override;
	bool characterCollision(Characters & character, Controller & ctrl) override;
	bool collision(Object& otherObject, Controller &ctrl) override;
	bool collisionTwo(Object& otherObject);
	void m_setCenter(int row, int col) override;
	//void collide(Wall& otherObject) override;
	void m_setOrigin(float x, float y) override;
	void m_SetTexture() override;
	void m_setScale(int w, int h, int r, int c) override;
	bool m_move() override;
	void m_draw(sf::RenderWindow &window) override;
	void m_setPosition(float x, float y) override;
	void m_setColor(sf::Color &color) override;
	
	sf::Vector2f getOriginalPosition() override;
	void setOriginalPosition(float x, float y) override;
	//float getRadius() override;
	//void setSize(int size) override;
	int getSize() const;
	void setSize(int size) override;
	bool smartGhost = false;
	bool isSmartGhost() override;
	//void m_setOrigin(float x, float y) override;
	//bool m_move() override;
	Ghost();
	~Ghost();
private:
	int numOfCollisions = 0;
	int ghostAnimeSource = 0;
	sf::Clock animeClock;
	bool switchUp = false;
};

