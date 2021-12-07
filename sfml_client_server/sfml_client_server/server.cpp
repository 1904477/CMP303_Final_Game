#include "server.h"

void server::Init()
{
	std::cout << "The local server address is: \n" << sf::IpAddress::getLocalAddress()<<"\n";
	std::cout << "The public server address is: \n" << sf::IpAddress::getPublicAddress() << "\n";
	udp_port= 1111;
	listener.listen(53000);
	listener.setBlocking(false);
	selector.add(listener);
	UDP_socket.setBlocking(false);

	
	BindUDP();
}

void server::Update()
{
	bool done = false;
	while (!done)
	{
		if (connected == true);
		TCP();
		UDP();
	}
	
}

void server::TCP()
{
	TCPCommunicationHandler();
	//TCPMessageRecSend();
}

void server::TCPCommunicationHandler()
{
	sf::Packet disconnection_detector;
	sf::TcpSocket* socket = new sf::TcpSocket;
	if (listener.accept(*socket) != sf::Socket::Done)
	{
		//std::cout << "error accepting new conn\n";
	}
	else
	{
		if (clients.size() < 3)
		{
			clients.push_back(socket);
			selector.add(*socket);
			sf::Packet name_packet;
			std::string name;
			if (socket->receive(name_packet) == sf::Socket::Done)
			{
				int type =0;
				name_packet >> type;
				if (type == 1)
				{
					name_packet >> name;
					std::cout << name << " has connected to the chat room. " << std::endl;
				}
				addPlayer();
				IdAndPositionSetter(socket, name);
			}

			socket->setBlocking(false);
			connected = true;
		}
	}
	TCPMessageRecSend();
}

void server::TCPMessageRecSend()
{

	std::size_t dummy;
	for (int i = 0; i < clients.size(); i++)
	{
		//	printf("A message was sent. \n");
			sf::Packet packet, sendPacket;
			if (clients[i]->receive(packet) == sf::Socket::Done)
			{
				std::cout << "someone sent a message\n";
				std::string text;
				packet >>text;
				int type = 8;
				sendPacket <<type<<  text;
				for (int j = 0; j < clients.size(); j++)
				{
					if (i != j)
					{
						clients[j]->send(sendPacket);
					}
				}
			}
			sendStartGame(clients[i]);
			checkDisconnections(clients[i]);
	}

}

void server::UDP()
{
	receiveUDP();
}

void server::receiveUDP()
{

	int id;
	int type;
	char data[100];
	std::size_t received;
	// UDP socket:
	sf::IpAddress sender;
	sf::Packet receivePos;
	Player incomingClient;
	unsigned short port;
	while (UDP_socket.receive(receivePos, sender, port) == sf::Socket::Done)
	{
		receivePos >> type;
		receivePos >> id;
		incomingClient.ip = sender;
		incomingClient.portUDP = port;
		incomingClient.clientID = id;
		bool match = false;
		for (int i = 0; i < Players.size(); i++)
		{
			if (Players[i].clientID == incomingClient.clientID)
			{
				match = true;
			}
		}
		if (!match)
		{
			Players.push_back(incomingClient);
		}

		if (type == 3)
		{
			sendUDP(receivePos, id);
		}
		else if (type == 6)
		{
			id_setter--;
			std::cout << "ID: " << id_setter << " has disconnected. \n";
			std::cout << id_setter << "  is now a free id.\n ";
			clients.pop_back();
			std::cout << "There are other : " << clients.size() << " people in the server \n";
		}
		else if (type == 8)
		{
			coinPickedEvent(receivePos,id);
		}
	}
}


void server::sendUDP(sf::Packet receivePosVar,int ID)
{
	int type = 7;
		sf::Packet move;
		//int id_temp;
		float posX;
		float posY;
		//receivePosVar >> id_temp;
		receivePosVar >> posX;
		receivePosVar >> posY;
		sf::Packet sendToClients;
		sendToClients << type;
		sendToClients << ID;
		sendToClients << posX;
		sendToClients << posY;
	/*	sendToClients << coinPos.x;
		sendToClients << coinPos.y;*/

		for (int i = 0; i < Players.size(); i++)
		{
			unsigned short port = Players[i].portUDP;
			sf::IpAddress address = Players[i].ip;
			if (UDP_socket.send(sendToClients, address, port) != sf::Socket::Done)
			{
				printf("message can't be sent\n");
			}
			else
			{
				//std::cout << "Positions of players have been successfully sent \n";
			}
		}
			
}

void server::IdAndPositionSetter(sf::TcpSocket* sock, std::string name_)
{
	sf::Packet setupAsked;
	int type;
	
	if (sock->receive(setupAsked) == sf::Socket::Done)
	{
		setupAsked >> type;
		if (type == 19)
		{
			sf::Packet Id_And_Pos_Setter;
			int type = 1;
			Id_And_Pos_Setter << type;
			Id_And_Pos_Setter << id_setter;


			for (int i = 0; i < Players.size(); i++)
			{
				Players[i].startPos.x = static_cast <float> (rand() % 1000);
				Players[i].startPos.y = static_cast <float> (rand() % 1000);
				Id_And_Pos_Setter << Players[i].startPos.x << Players[i].startPos.y;
			}


			if (sock->send(Id_And_Pos_Setter) != sf::Socket::Done)
			{
				std::cout << "Error sending message. \n";
			}
			else
			{
				std::cout << name_ << " is id: " << id_setter << "\n";
				id_setter++;
				std::cout << "Someone joined with id: " << id_setter << "\n";
			}
			int type1 = 2;
			coinPosPacket << type1;
			if (genDone == false)
			{
				for (int i = 0; i < 10; i++)
				{
					float x = static_cast <float> (rand() % 1000);
					float y = static_cast <float> (rand() % 1000);
					coinPos[i].x = x;
					coinPos[i].y = y;
					coinPosPacket << coinPos[i].x;
					coinPosPacket << coinPos[i].y;
					std::cout << coinPos[i].x << "  -  " << coinPos[i].y << std::endl;
				}
				genDone = true;
			}
			if (sock->send(coinPosPacket) != sf::Socket::Done)
			{
				std::cout << "Error sending message. \n";
			}
			else
			{

			}

		}
	}
	
}

void server::coinPickedEvent(sf::Packet pack,int id)
{
	int coinNum = 0;
	int type = 9;
	pack >> coinNum;
	std::cout << id << " collected coin:" << coinNum << "\n";
	sf::Packet coin_Picked;
	coin_Picked << type;
	coin_Picked << id;
	coin_Picked << coinNum;
	for (int i = 0; i < Players.size(); i++)
	{
		unsigned short port = Players[i].portUDP;
		sf::IpAddress address = Players[i].ip;
		if (UDP_socket.send(coin_Picked, address, port) != sf::Socket::Done)
		{
			printf("message can't be sent\n");
		}
		else
		{
			//std::cout << "Positions of players have been successfully sent \n";
		}
	}
}

void server::sendStartGame(sf::TcpSocket* sock)
{
	sf::Time time1;
	if (clients.size() == 2)
	{
		time1 = clock.getElapsedTime();
		sf::Packet startGame;
		int type = 5;
		startGame << type;
		if (time1.asSeconds() >= 0.1)
		{
			if (sock->send(startGame) != sf::Socket::Done)
			{
				std::cout << "failed to send startGame packet\n";
			}
			else
			{
				std::cout << "sent startGame packet.\n";
				clock.restart();
			}
		}
	}
}

void server::checkDisconnections(sf::TcpSocket* sock)			//Checks for disconnections every 3 seconds
{
	sf::Packet discCheck;
	sf::Time discTime;
	discTime = discCheckClock.getElapsedTime();
	if (discTime.asSeconds() >= 3)
	{
		if (sock->send(discCheck) != sf::Socket::Done)
		{
			id_setter--;
			std::cout << "ID: " << id_setter << " has disconnected. \n";
			std::cout << id_setter << "  is now a free id.\n ";
			clients.pop_back();
			std::cout << "There are other : " << clients.size() << " people in the server \n";
		}
		discCheckClock.restart();
	}
}

void server::addPlayer()
{
	Player inst;
	Players.push_back(inst);
}

void server::BindUDP()
{
	// bind the socket to a port
	if (UDP_socket.bind(udp_port) != sf::Socket::Done)
	{
		printf("Error binding UDP\n");
	}
	else
	{
		printf("UDP bound correctly\n");
	}
}
