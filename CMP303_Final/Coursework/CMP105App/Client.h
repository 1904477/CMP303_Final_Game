#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string>
#include <sstream>      // std::stringstream
#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "GraphicsTools.h"
#include "Framework/Collision.h"
class Client
{
public:
	Client(sf::IpAddress& ip, unsigned short& port, Player& p,Player& enemy, std::string& name,sf::TcpSocket*sock,sf::RenderWindow*window);
	~Client();
	void HandleInput(sf::Event* Ev,Input* input, Player* p);
	void Update(Input* input,sf::Event * Ev, Player* p, Player* enemy, float dt);
	void Render();
	void disconnect(Player* p, Input* input);
	void Setup(Player* p, Player* enemy);

	void sendMessageTCP(Player* p);
	void TCPReceive();
	void ID_And_Positions_Getter();
	void textSetup(sf::RenderWindow* window);

	void UDP_sendPosition(Player* p, Input* input, float dt);
	void UDPReceive(Player* p, Player* enemy);
	void interpolateEnemyPos(Player* enemy, float dt);
	void CheckCollision(Player* p);


	void askSetup();
	void coinPosGetter();

	bool getConnectedStatus();
	bool renderEnemy();

protected:
	std::string name;
	std::string userText;
	sf::Font font;

	sf::TcpSocket* socket;
	sf::UdpSocket udp_socket;
	std::vector<sf::Text>chat;
	sf::IpAddress Ip_serverAddress;

	GraphicsTools Tools;

	sf::Text drawText;
	sf::Text timerStart;
	sf::Text waitForPlayers;
	sf::Clock clock;
	sf::Clock clockGameStart;
	sf::Time timeGameStart;
	sf::RenderWindow* window_;

	unsigned short udp_port;

	int id_getter;
	bool connected_;

	bool render_enemy;
	bool open_chat;		//Bool for knowing if the chat is open
	bool chat_empty_on_open;	//Bool for properly switch vars
	bool is_chat_open;
	bool render_preStart = true;;
	bool renderStartTimer = false;
	bool canMove = false;

	sf::Vector2f coinPos[10];
	struct playerPos
	{
		sf::Vector2f Player_start_pos;
		sf::Vector2f enemy_received = sf::Vector2f(0, 0);
		int score;
	};
	playerPos Player1;
	playerPos Player2;
	float speed;

};