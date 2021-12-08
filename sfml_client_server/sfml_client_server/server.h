#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <list>
#include<thread>
class server
{
public:
	void Init();
	void Update();
	void TCP();
	void TCPCommunicationHandler();
	void TCPMessageRecSend();
	void UDP();
	void BindUDP();
	void receiveUDP();
	void sendUDP(sf::Packet receivePosVar,int ID);
	void IdAndPositionSetter(sf::TcpSocket* sock,std::string name_);
	void coinPickedEvent(sf::Packet pack, int id);
	void sendStartGame(sf::TcpSocket *sock);
	void checkDisconnections(sf::TcpSocket* sock);
	void addPlayer();
	void sendTime();

	bool connected;
	int tcp_port;
	unsigned short udp_port;
	bool server_started;
protected:
	sf::UdpSocket UDP_socket;
	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*>clients;
	int id_setter=26;

	struct Player
	{
		sf::Vector2f startPos;
		int score = 0;
		sf::IpAddress ip;
		unsigned short portUDP;
		int clientID;
	};
	std::vector<Player> Players;
	sf::Clock startGameClock;
	sf::Clock gameClock;
	sf::Clock discCheckClock;
	sf::Clock howOftenSendGameTime;
	bool gameStarted = false;
	
	int sendStartGameTo2 = 0;
	float dt;
	sf::Packet coinPosPacket;
	bool genDone=false;
	sf::Vector2f coinPos[10];
};

