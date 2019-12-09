#include "Characters.h"







bool Characters::characterCollision(Characters& character, Controller &ctrl)
{
	return false;
}



void Characters::collide(Object & object)
{
}

void Characters::collide(Wall & object)
{
}

bool Characters::m_move()
{
	return false;
}

bool Characters::isSmartGhost()
{
	return false;
}

int Characters::getSpeed()
{
	return 0;
}

Characters::Characters()
	
{
	
	m_speed = 3;
}


Characters::~Characters()
{
}
