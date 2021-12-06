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
//	void sendUDP();
	void BindUDP();
	void receiveUDP();
	void sendUDP(sf::Packet receivePosVar,int ID);
	void startingPositions();
	void IdAndPositionSetter(sf::TcpSocket* sock,std::string name_);
	void coinPickedEvent(sf::Packet pack, int id);
	void sendStartGame(sf::TcpSocket *sock);
	void checkDisconnections(sf::TcpSocket* sock);
	bool connected;
	int tcp_port;
	unsigned short udp_port;
	bool server_started;
protected:
	std::thread first, second;
	sf::UdpSocket UDP_socket;
	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*>clients;
	int id_setter=26;
	int x=0, y=0;
	struct udpClient
	{
		sf::IpAddress ip;
		unsigned short portUDP;
		int clientID;
	};
	std::vector<udpClient> clientsUDP;
	float Starting_posX;
	float Starting_posY;
	float Enemy_Starting_posX;
	float Enemy_Starting_posY;
	int scoreP1 = 0;
	int scoreP2 = 0;
	sf::Clock clock;	
	sf::Clock discCheckClock;

	
	sf::Packet coinPosPacket;
	bool genDone=false;
	sf::Vector2f coinPos[10];
};

