#pragma once
#include <vector>
#include "Characters.h"
class Ghost;
class PacMan;
//#include "Characters.h"
#include <memory>
#include <fstream>
class Object;

#include "SFML\Graphics.hpp"
class Controller;
class Board
{
public:
	void restartClocks();
	void moveAllCharacters(Controller &ctrl);
	void checkCollision(Controller &ctrl);
	bool checkLevelCompletion(Controller &ctrl);
	Board();
	~Board();
	//Draw the board
	void m_drawTopPanel(sf::RenderWindow &window);
	void m_drawBoard(sf::RenderWindow &window );
	//Initialize the board
	void m_initBoard(std::string filename);
	//Construct the board by loading in a text file
	Board(std::string fileName, Controller& ctrl);
	//Get next board - Recieves row and col, and board from board.txt
	void getNextBoard(Controller &ctrl);
	void movePac(int direc);
	int getBoardWidth() const;
	int getBoardHeight() const;
	int getRows() const;
	int getCols() const;
	bool deathSleep = false;
	void setScore(int score);
	void resetToBeg();
	int numOfGhosties();
	void setLives(int life);
	bool findPathToPac(Ghost &ghost, PacMan &pacman, int x, int y);
	void dispatchSmartGhosts(Board &board);
	int pac_speed = 0;
	//std::ostringstream ss; //string buffer to convert numbers to string
private:
	int getPacSpeed() const;
	int lives = 3;
	int level = 0;
	int numOfElves = 0;
	int numOfCookies = 0;
	int m_score = 0;
	//create a font
	sf::Font font{};
	sf::Text scoreText;
	sf::Text lifeText;
	sf::Text levelText;
	sf::Text speedText;
	
	// What is this board? A vector of toolbar to be added, characters, and objects
	std::vector<std::unique_ptr<Characters>> m_Characters;
	// Vector of objects which can be wall, cookies
	std::vector<std::unique_ptr<Object>> m_GameBoard;
	int BoardWidth = 1200;
	int BoardHeight = 800;
	int m_Rows;
	int m_Cols;
	sf::Vector2i m_TileMap;
	// File for fstream
	std::fstream m_file;
	// 
	std::vector<std::string> m_board; // Current Level
	//std::vector<Characters> m_Characters;
	sf::Clock m_GameClock;
	sf::Clock m_BoardClock;
};

