#pragma once
#include "Object.h"
class Cookie :
	public Object
{
	
	
public:
	bool collision(Object& otherObject, Controller &ctrl) override;
	//virtual void collide(Wall& otherObject) ocverride;
	void m_setPosition(float x, float y) override;
	void m_SetTexture() override;
	void setSize(int size) override;
	int getSize() const override;
	void m_draw(sf::RenderWindow &window) override;
	void m_setScale(int a, int b, int c, int d);
	void m_setCenter(int row, int col) override;
	void m_setColor(sf::Color &color) override;
	void m_setOrigin(float x, float y) override;

	float getRadius;
	
	void m_poisoned();
	void m_powerup();
	bool m_checkPowerUp();  // Returns true if cookie is powerup
	bool m_checkPoison();	// Returns true if cookie is poison

	sf::Vector2f getCenter(Object &object) override;
	//int getSize() const;
	Cookie();
	~Cookie();
private:
	bool m_powerUp = false;
	bool m_poison = false;
};

