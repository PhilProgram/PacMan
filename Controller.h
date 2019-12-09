#pragma once
#include "Board.h"
#include "MainMenu.h"
class Controller
{
public:
	
	Controller();
	~Controller();
	void displayMainMenu();
	void retryQuit();
	void pacIsMoving();
	void pacNotMoving();
	void startGame();
	//void move_Characters();
	void playGame(Board &board, sf::RenderWindow &window);
	void updatePacDirection(int d);
	int getPacDirection();
	bool isPacMoving();
	int getCookiesEaten();
	void incrCookies();
	void incrGhosts();
	void winnerWinner();
	void updateScore();
	void initDeath();
	Controller(sf::RenderWindow &window);
	bool playingGame = true;
private:
	// Death, Game Over, Winner Winner
	sf::Texture gameTextures[4];
	MainMenu m_Menu;
	Board m_Board;
	int numOfGhosts = 0;
	int direction = 0;
	int cookiesEaten = 0;
	int pacDirection = 0;
	bool pacMoving;
	int m_Score = 0;
	int livesRemaining = 3;
	int m_currentLevel = 1;
	sf::Clock algoClock;
	sf::Clock playerTimer;
	sf::Clock soundClock;
	sf::Time pTimeElapsed;
	sf::RenderWindow &m_window;
	

};