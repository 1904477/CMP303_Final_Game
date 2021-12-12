#pragma once
							//------------------------INCLUDES
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include <string>
#include <iostream>
#include "Client.h"
#include "Player.h"
#include "Menu.h"
class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs,sf::TcpSocket *sock);
	~Level();
	void handleInput(float dt);			//Main functions
	void update(float dt,sf::Event*Ev);
	void clientInput(sf::Event* Ev);
	void render();
	void Init( Menu* menu_);
	bool get_connected() { return connected_succesfully; };	//
private:

	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;		//-----------window pointer to main
	Input* input;		//-----------Input pointer to main
	GameState* gameState;
	AudioManager* audio;
	//Client client_;
	Player player_;			//Main player variable
	std::vector<Player>enemies;			//Vector of enemies, communicates with Client

	bool connected_succesfully;			//Get the connected variable 
	Menu* menu;							//Menu pointer
	std::unique_ptr<Client> client_;	//Client unique pointer

	unsigned short port;				//Ports
	sf::IpAddress IP_ADDRESS;			//Ip address
	std::string name;					//Name input by the player
	sf::TcpSocket* Tcp;					//Tcp socket

};