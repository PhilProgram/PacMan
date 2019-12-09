#include "Controller.h"
sf::RectangleShape gameOverPic(sf::Vector2f(800, 600));
//#include <iostream>
#include <SFML/Audio.hpp>
sf::Sound buttonSound;
sf::Sound levelComplete;
sf::Sound winner;
sf::SoundBuffer winnerBuffer;
sf::SoundBuffer levelCompleteBuffer;
sf::SoundBuffer buttonBuffer;
sf::SoundBuffer deathBuffer;
sf::SoundBuffer gameOverBuffer;

sf::Sound deathSound;
sf::Sound gameOver;



bool soundPlayed = false;

Controller::~Controller()
{
}

void Controller::displayMainMenu()
{
	sf::Vector2i mousePlace{ 0,0 };

	m_window.setMouseCursorVisible(1);
	m_window.create(sf::VideoMode(800, 600), "pacman");

	m_Menu.initialize();
	m_Menu.display(m_window);
	m_window.display();
	sf::sleep(sf::seconds(2.5));
	// Three Buttons on main menu  Play
								// Instructions
								// Exit
								// Instructions -> Display a text I guess"
	sf::Vector2f mouseCoordinates;
	sf::Event event;
	while (m_window.isOpen())
	{
		

		//m_window.setSize(800, 600);
		while (m_window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonPressed:
				mousePlace = sf::Vector2i{ event.mouseButton.x, event.mouseButton.y };
				if (m_Menu.m_Contains(sf::Vector2f(mousePlace)))
				{
					buttonSound.setBuffer(buttonBuffer);
					buttonSound.play();
					playingGame = true;
					startGame();
				}
				break;
				

			case sf::Event::MouseMoved:
				mousePlace = sf::Vector2i{ event.mouseMove.x , event.mouseMove.y };
				
				break;
			
			}
		}
		m_Menu.updateOutline(sf::Vector2f(mousePlace));
		m_window.clear();
		m_Menu.display(m_window);
		m_window.display();
	}
}

void Controller::retryQuit()
{
}

void Controller::pacIsMoving()
{
	pacMoving = true;
}

void Controller::pacNotMoving()
{
	pacMoving = false;
}

void Controller::startGame()
{
	// Starting point for spritesheet
	sf::Vector2f source{ 0,0 };
	sf::Vector2f sourceTwo{ 0,0 };
	// Create window
	
	//Board board{ "board.txt" };
	
	m_window.create(sf::VideoMode(m_Board.getBoardWidth(), m_Board.getBoardHeight() + 100), "pacman");
	//sf::RenderWindow window{ m_window };
	//m_window.create(sf::VideoMode(board.getBoardWidth(), board.getBoardHeight()+100), "pacman");
	//m_window.setSize(board.getBoardWidth(), board.getBoardHeight() + 100);
	m_window.setFramerateLimit(60);
	// This way you don't have to hold down the key, thus, animation
	m_window.setKeyRepeatEnabled(0);

	numOfGhosts = m_Board.numOfGhosties();
	m_Board.setLives(livesRemaining);
	// Create a new board , Board board{"board.txt"}
	// Send the board by reference to play? g
	playGame(m_Board, m_window);
}

void Controller::playGame(Board & board, sf::RenderWindow & window)
{
	
	

	board.m_drawBoard(window);
	board.m_drawTopPanel(window);
	window.display();
	sf::sleep(sf::seconds(2.5));
	pacNotMoving();
	sf::Clock clock;
	sf::Time elapsed = clock.restart();
	board.restartClocks();
	while (window.isOpen() && playingGame)
	{
		
		
		//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
		//std::cout << pacSprite.getLocalBounds(). << std::endl;
		sf::Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				
				if (event.key.code == sf::Keyboard::Right)
				{
					
					updatePacDirection(Right);
					pacIsMoving();
					
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					
					updatePacDirection(Left);
					pacIsMoving();
				
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					updatePacDirection(Up);
					pacIsMoving();
					
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					updatePacDirection(Down);
					pacIsMoving();
					
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					pacNotMoving();
					
				}
			}
		}
		if (board.deathSleep)
		{
			board.deathSleep = false;
			sf::sleep(sf::seconds(1.5));

		}
		/*if (soundClock.getElapsedTime().asSeconds() > 0.7f)
		{
			sound.play();
			soundClock.restart();
		}*/
		board.moveAllCharacters(*this);
		/*if (algoClock.getElapsedTime().asSeconds() > 15.0f)
		{
			board.dispatchSmartGhosts(board);
			algoClock.restart();
		}*/
		board.checkCollision(*this);
		if (board.checkLevelCompletion(*this))
		{
			m_Score += (numOfGhosts + 1) * 50;
			board.getNextBoard(*this);
			numOfGhosts = board.numOfGhosties();
			levelComplete.setBuffer(levelCompleteBuffer);
			levelComplete.play();
			sf::sleep(sf::seconds(2.5));
		}
		// Update the score, return true? nextLevel
		board.setScore(m_Score);
		board.m_drawBoard(window);
		board.m_drawTopPanel(window);
		window.display();
		window.clear(sf::Color(0,0,0,225));
	}
}

void Controller::updatePacDirection(int d)
{
	pacDirection = d;
}

int Controller::getPacDirection()
{
	return pacDirection;
}

bool Controller::isPacMoving()
{
	return pacMoving;
}

int Controller::getCookiesEaten()
{
	return cookiesEaten;
}

void Controller::incrCookies()
{
	cookiesEaten++;
}

void Controller::incrGhosts()
{
	numOfGhosts++;
}

void Controller::winnerWinner()
{
	//Display game over transparent text
	livesRemaining = 3;
	m_Board.setLives(livesRemaining);
	//m_file
	m_Board.resetToBeg();
	m_Board.getNextBoard(*this);
	cookiesEaten = 0;
	numOfGhosts = m_Board.numOfGhosties();
	m_Score = 0;

	playingGame = false;
	m_window.create(sf::VideoMode(800, 600), "Winner Winner Chicken Dinner");
	if (gameTextures[1].loadFromFile("winnerwinner.png"))
	{
		//std::cout << "Sucess";
	}
	winner.setBuffer(winnerBuffer);
	winner.play();
	gameOverPic.setTexture(&gameTextures[1],true);
	m_window.clear();
	m_window.draw(gameOverPic);
	m_window.display();
	sf::sleep(sf::seconds(2.5));
	deathSound.setBuffer(deathBuffer);
	deathSound.play();
	displayMainMenu();
	//play gameoversound
	// sleep thread for 1 second.
	//playGame(m_Board, m_window);
}

void Controller::updateScore()
{
	//std::cout << "JJJ" << numOfGhosts << std::endl;
	m_Score += (numOfGhosts + 1) * 2;
}

void Controller::initDeath()
{
	
	livesRemaining--;
	m_Board.setLives(livesRemaining);
	if (!livesRemaining)
	{
		
		

		//Display game over transparent text
		livesRemaining = 3;
		m_Board.setLives(livesRemaining);
		//m_file
		m_Board.resetToBeg();
		m_Board.getNextBoard(*this);
		cookiesEaten = 0;
		numOfGhosts = m_Board.numOfGhosties();
		m_Score = 0;
		
		playingGame = false;
		m_window.create(sf::VideoMode(800, 600), "pacman");
		if (gameTextures[0].loadFromFile("game_over.jpg"))
		{
			//std::cout << "Sucess";
		}
		gameOverPic.setTexture(&gameTextures[0],true);
		m_window.clear();
		m_window.draw(gameOverPic);
		m_window.display();
		gameOver.setBuffer(gameOverBuffer);
		gameOver.play();
		sf::sleep(sf::seconds(2.5));
		
		//play gameoversound
		// sleep thread for 1 second.
		//playGame(m_Board, m_window);
		
	}
	
		
	

}

Controller::Controller(sf::RenderWindow & window)
:m_window(window), m_Board{ "board.txt" , *this}
{
	if (!buttonBuffer.loadFromFile("button-09.wav"))
	{

	}
	if (!deathBuffer.loadFromFile("terminated.wav"))
	{

	}
	if (!gameOverBuffer.loadFromFile("game_over.wav"))
	{

	}
	if (!levelCompleteBuffer.loadFromFile("pacman_chomp.wav"))
	{
		
	}
	if (!winnerBuffer.loadFromFile("pacman_intermission.wav"))
	{

	}
	/*if (!buttonBuffer.loadFromFile("button-19.wav"))
	{

	}*/
	soundClock.restart();
	algoClock.restart();
}
