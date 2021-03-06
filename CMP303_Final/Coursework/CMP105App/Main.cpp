// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "Client.h"
#include "Menu.h"
int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1200, 675), "CMP303_Coursework");
	sf::TcpSocket Tcp;
	//Tcp.setBlocking(false);
	GameState gameState;
	gameState.setCurrentState(State::MENU);

	// Initialise input and level objects.
	Input input;

	Menu menu(&window, &gameState, &input,&Tcp);	//Menu and level objects
	Level level(&window, &input, &gameState,&Tcp);
	//	client_.Init(&window);
		// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;
	bool levelInitialized = false;
	bool menuInitialized = false;
	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(false);
				}
				break;
			default:
				break;
			}
			if (gameState.getCurrentState() == State::LEVEL)
			{
				if (level.get_connected()==false)
				{
					level.Init(&menu);
				}
				level.clientInput(&event);
				
			}
			else if (gameState.getCurrentState() == State::MENU)
			{
				if (menuInitialized == false)
				{
					menu.Init();
					menuInitialized = true;
				}
				menu.handleInput(&event);
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		enum class GameState { MENU, GAME };

		// Call standard game loop functions (input, update and render)

		switch (gameState.getCurrentState())	//DIFFERENT GAME STATES
		{
		case(State::MENU):
			
			menu.update(deltaTime);
			menu.render();
			break;
		case(State::LEVEL):

			level.handleInput(deltaTime);
			level.update(deltaTime, &event);
			level.render();
			break;
		}
	}
}