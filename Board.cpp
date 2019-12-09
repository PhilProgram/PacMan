#include "Board.h"
#include "Controller.h"
//#include "Object.h"
#include <iostream>
#include <thread>
#include "Cookie.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Wall.h"
#include <sstream>
#include "SFML\Graphics.hpp"
sf::Vector2f pacPos; //pacPos; { m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 2 };
sf::Vector2f ghostPos;// cookiePos; { cookie.m_sprite.getPosition().x + cookie.m_sprite.getGlobalBounds().width / 2, cookie.m_sprite.getPosition().y + cookie.m_sprite.getGlobalBounds().height / 2 };
float distance;// = sqrt((pacPos.x - cookiePos.x)*(pacPos.x - cookiePos.x) + (pacPos.y - cookiePos.y)*(pacPos.y - cookiePos.y));
bool canMove = true;
//std::cout << distance << " " << getRadius() << std::endl;
//if (cookie.m_sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
//if (distance<getRadius() * 2)

void Board::restartClocks()
{
	m_BoardClock.restart();
	m_GameClock.restart();
}
void Board::moveAllCharacters(Controller &ctrl)
{
	for (int i = 0; i < m_Characters.size(); i++)
		m_Characters.at(i)->m_moveCharacter(ctrl);
}
// This just checks the collision between Characters and Board, not characters and characters.
void Board::checkCollision(Controller &ctrl)
{
	for (int i = 0; i < m_Characters.size(); i++)
	{
		for (int j = 0; j < m_GameBoard.size(); j++)
		{
			//m_GameBoard.at(i)->collide(m_GameBoard.at(j));
			if (m_Characters.at(i)->collision(*m_GameBoard.at(j), ctrl))
			{
				m_GameBoard.erase(m_GameBoard.begin() + j);
			}
			// if character at pos i=0 intersects with objects sprite from game board
			// 
		}
	}
	for (int index = 1; index < m_Characters.size(); index++)
	{
		if (m_Characters.at(0)->characterCollision(*m_Characters.at(index), ctrl))
		{
			//resetPositions;
			for (int k = 0; k < m_Characters.size(); k++)
			{
				m_Characters.at(k)->m_setPosition(m_Characters.at(k)->getOriginalPosition().x, m_Characters.at(k)->getOriginalPosition().y);
			}
			sf::sleep(sf::seconds(0.5));
			deathSleep = true;
		};
	}
	
}
bool Board::checkLevelCompletion(Controller &ctrl)
{
	ctrl.getCookiesEaten();
	if (ctrl.getCookiesEaten() == numOfCookies)
	{
		return true;
	}
	return false;
}
Board::Board()
{
	
}
Board::Board(std::string filename, Controller &ctrl)
{
	
	if (!font.loadFromFile("arial.ttf"))
		//find this file in the "pong" example in the SFML examples folder
	{
		//std::cout << "Error loading font\n";
	}
	
	speedText.setFont(font);
	speedText.setCharacterSize(50);
	speedText.setStyle(sf::Text::Bold);
	speedText.setFillColor(sf::Color::Green);
	speedText.setPosition(250, 0);
	



	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setPosition(800, 0);
	
	lifeText.setPosition(550, 0);
	lifeText.setFillColor(sf::Color::Green);
	lifeText.setCharacterSize(50);
	lifeText.setFont(font);
	lifeText.setFillColor(sf::Color::White);

	
	levelText.setFont(font);
	levelText.setCharacterSize(50);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(20, 0);
	
	
	//scoreText.setString("10:05");
	
	
	//Construct board object with fileName.txt



	if (!m_file.is_open())
		m_file.open(filename);

	if (m_file.fail())
	{
		//std::cout << "Error: File did not open";
	}


	getNextBoard(ctrl);

	
	//m_file.close();
}
// Get next board from txt file
void Board::getNextBoard(Controller &ctrl)
{
	numOfElves = 0;
	level++;
	m_Characters.clear();
	m_GameBoard.clear();
	m_board.clear();
	
	int offset = 100; // to hold time and score and lives
	std::string line;
	std::string line2;
	
	std::getline(m_file, line);
	if (line[0] == 'e')
	{
		
		ctrl.winnerWinner();
	}
	m_Rows = std::stoi(line);
	std::getline(m_file, line2);
	m_Cols = std::stoi(line2);
	//std::cout << "Rows: " << m_Rows << " Cols: " << m_Cols << std::endl;
	for (int i = 0; i < m_Rows; i++)
	{
		getline(m_file, line);
		m_board.push_back(line);
	}
	//int counter = 0;
	for (int j = 0; j < m_Rows; j++)
	{
		for (int a = 0; a < m_Cols; a++)
		{
			// Case if theres a wall
			if (m_board[j][a] == '#'|| m_board[j][a] == 'E' || m_board[j][a] == 'D')	// Insert Wall
			{
				sf::Color m1 = sf::Color::Magenta;
				sf::Color m2 = sf::Color::Green;
				// create wall - send board? Not neccesary, we're doing this internally
				Wall wall;
				char temp = m_board[j][a];
				switch (temp)
				{
				case  'D':

					wall.m_setColor(m1);
					break;
				case  'E':
					wall.m_setColor(m2);
					break;

				default:
					break;

				}
				wall.m_setPosition(a * (BoardWidth / m_Cols), j  * (BoardHeight / m_Rows) + offset);
				wall.m_SetTexture();
				wall.m_setScale(getBoardWidth(), getBoardHeight(), getRows(), getCols());
				m_GameBoard.push_back(std::make_unique<Wall>(wall));;
			}
			// Case if theres a Pacman on board. 
			if (m_board[j][a] == '@' || m_board[j][a] == 'W' || m_board[j][a] == 'S')

			{
				sf::Color m1 = sf::Color::Magenta;
				sf::Color m2 = sf::Color::Green;

				// The only thing we really need to do is change the color,

				// Create pacman function
				//std::cout << "PacMan inserted";
				PacMan Packy;
				Packy.m_setPosition(a * (BoardWidth / m_Cols), j  * (BoardHeight / m_Rows) + offset);
				Packy.setOriginalPosition(a * (BoardWidth / m_Cols), j  * (BoardHeight / m_Rows) + offset);
				Packy.m_SetTexture();
				Packy.m_setScale(getBoardWidth(), getBoardHeight(), getRows(), getCols());
				//std::cout << Packy.getRadius();



				char temp = m_board[j][a];
				switch (temp)
				{
				case  'S':

					Packy.m_setColor(m1);
					break;
				case  'W':
					Packy.m_setColor(m2);
					break;

				default:
					break;

				}
				m_Characters.push_back(std::make_unique<PacMan>(Packy));
				std::reverse(m_Characters.begin(), m_Characters.end());

			}
			// Cookies
			//if(m_board[j][a] == '*' || if(m_board[j][a] == 'I' || if(m_board[j][a] == 'K)
			if (m_board[j][a] == '*' || m_board[j][a] == 'I' || m_board[j][a] == 'K')
			{
				sf::Color m1 = sf::Color::Cyan;
				sf::Color m2 = sf::Color::Magenta;
				// Create cookie, 
				Cookie cookie;
				
				//std::cout << numOfCookies << std::endl;
				cookie.m_setPosition(a * (BoardWidth / m_Cols), j  * (BoardHeight / m_Rows)+offset);
				cookie.m_SetTexture();
				//cookie.m_setOrigin((a * (BoardWidth / m_Cols)),(j  * (BoardHeight / m_Rows)));
				cookie.m_setScale(getBoardWidth(), getBoardHeight(), getRows(), getCols());

				char temp = m_board[j][a];
				switch (temp)
				{
				case  'I':

					
					cookie.m_poisoned();
					cookie.m_setColor(m1);;
					break;
				case  'K':
					
					cookie.m_powerup();
					cookie.m_setColor(m2);
					break;

				default:
					numOfCookies++;
					break;

				}
				m_GameBoard.push_back(std::make_unique<Cookie>(cookie));;
				//std::cout << Packy.getRadius();
				//m_Characters.push_back(std::make_unique<PacMan>(Packy));
			}
			

			// Ghosts
			//ifif(m_board[j][a] == '
			if (m_board[j][a] == '%' ||  m_board[j][a] == 'T' || m_board[j][a] == 'G')
			{
				int randomTemp = rand() % 8;
				
				numOfElves++;
				sf::Color m1 = sf::Color::Green;
				sf::Color m2 = sf::Color::Blue;
				Ghost ghost;
				// (randomTemp > 2)
				//{
				//	std::cout << "Smart ass" << std::endl;
				//''	ghost.smartGhost = true;
				//}
				ghost.m_setPosition(a * (BoardWidth / m_Cols), j  * (BoardHeight / m_Rows)+offset);
				ghost.setOriginalPosition(a * (BoardWidth / m_Cols), j  * (BoardHeight / m_Rows) + offset);
				ghost.m_SetTexture();
				ghost.m_setScale(getBoardWidth(), getBoardHeight(), getRows(), getCols());

				char temp = m_board[j][a];
				switch (temp)
				{
				case  'T':
					ghost.m_setColor(m1);;
					break;
				case  'G':
					ghost.m_setColor(m2);
					break;

				default:
					//numOfElves++;
					break;

				}
				m_Characters.push_back(std::make_unique<Ghost>(ghost));
				//std::cout << Packy.getRadius();
			}
			
		}
	}
	
	
}

void Board::movePac(int direc)
{
}

int Board::getBoardWidth() const
{
	return BoardWidth;
}

int Board::getBoardHeight() const
{
	return BoardHeight;
}

int Board::getRows() const
{
	return m_Rows;
}

int Board::getCols() const
{
	return m_Cols;
}

void Board::setScore(int score)
{
	m_score = score;
}

void Board::resetToBeg()
{
	numOfElves = 0;
	level = 0;
	numOfCookies = 0;
	lives = 3;
	m_file.clear();
	m_file.seekg(0, std::ios::beg);
}

int Board::numOfGhosties()
{
	return numOfElves;
}

void Board::setLives(int life)
{
	lives = life;
}

bool Board::findPathToPac(Ghost & ghost, PacMan & pacman, int x, int y)
{
	
	pacPos = {pacman.m_sprite.getPosition().x + pacman.m_sprite.getGlobalBounds().width / 2, pacman.m_sprite.getPosition().y + pacman.m_sprite.getGlobalBounds().height / 2 };
	ghostPos = { ghost.m_sprite.getPosition().x + ghost.m_sprite.getGlobalBounds().width / 2, ghost.m_sprite.getPosition().y + ghost.m_sprite.getGlobalBounds().height / 2 };
	float distance = sqrt((pacPos.x - ghostPos.x)*(pacPos.x - ghostPos.x) + (pacPos.y - ghostPos.y)*(pacPos.y - ghostPos.y));

	ghost.m_sprite.move(x, y);
	//std::cout << distance << " " << getRadius() << std::endl;
	//if (cookie.m_sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))

	//==== Base Case ====
	if (distance< pacman.getRadius() * 3)
		return true;
	// Collision case - false
	
	


	findPathToPac(ghost, pacman, 1, 0);
	findPathToPac(ghost, pacman, -1, 0);
	findPathToPac(ghost, pacman, 0, -1);
	findPathToPac(ghost, pacman, 0,1);
	
	
	return false;



}

void Board::dispatchSmartGhosts(Board & board)
{
	for (size_t i = 1; i < m_Characters.size(); i++)
	{

		if (m_Characters.at(i)->isSmartGhost())
		{
			//std::cout << "Finding path";
			// Ghost, Pacman, x, y
			if (findPathToPac(dynamic_cast<Ghost&>(*m_Characters.at(i)), dynamic_cast<PacMan&>(*m_Characters.at(0)), 0, 0));
			{
				//std::cout << "Path found" << std::endl;
			}
		}
	}
}

int Board::getPacSpeed() const
{
	return m_Characters.at(0)->getSpeed();
}

Board::~Board()
{
}

void Board::m_drawTopPanel(sf::RenderWindow & window)
{
	speedText.setString("Speed: " + std::to_string(getPacSpeed()));
	scoreText.setString("Score: " + std::to_string(m_score));
	lifeText.setString("Lives: " + std::to_string(lives));
	level == 5 ? levelText.setString("FINAL") : levelText.setString("Level: " + std::to_string(level));
	
	getPacSpeed() < 4 ? speedText.setFillColor(sf::Color::Red) : speedText.setFillColor(sf::Color::Yellow);
	if (getPacSpeed() > 10)
	{
		speedText.setFillColor(sf::Color::Green);
	}
	lives < 2 ? lifeText.setFillColor(sf::Color::Red) : lifeText.setFillColor(sf::Color::Green);
	/*if (m_BoardClock.getElapsedTime().asSeconds() < 10.0f)
	{
		scoreText.setColor(sf::Color::Red);
	}*/

	//scoreText.setString("Time: " + std::to_string(int(m_BoardClock.getElapsedTime().asSeconds())));
	window.draw(scoreText);
	window.draw(speedText);
	window.draw(lifeText);
	window.draw(levelText);
}

void Board::m_drawBoard(sf::RenderWindow &window)
{
	
	for (int i = 0; i < m_GameBoard.size(); i++)
	{
		m_GameBoard.at(i)->m_draw(window);	
	}
	for (int i = 0; i < m_Characters.size(); i++)
	{
		m_Characters.at(i)->m_draw(window);
	}  
}


