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
			int type=1;
			sf::Packet name_packet;
			std::string name;
			if (socket->receive(name_packet) == sf::Socket::Done)
			{
				startingPositions();
				name_packet >> name;
				std::cout << name << " has connected to the chat room. " << std::endl;
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
				sendPacket <<  text;
				for (int j = 0; j < clients.size(); j++)
				{
					if (i != j)
					{
						clients[j]->send(sendPacket);
					}
				}
			}
	}
	for (int i = 0; i < clients.size(); i++)
	{
		sf::Packet packet;
		if (clients[i]->send(packet) != sf::Socket::Done)
		{
			id_setter--;
			std::cout << "ID: " << id_setter << " has disconnected. \n";
			std::cout << id_setter << "  is now a free id.\n ";
			clients.pop_back();
			std::cout << "There are other : " << clients.size() << " people in the server \n";
		}
		else
		{
			printf("Clients are connected\n");
		}
	}

}

void server::UDP()
{
	receiveUDP();
	propsPos();
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
	udpClient incomingClient;
	unsigned short port;
	while (UDP_socket.receive(receivePos, sender, port) == sf::Socket::Done)
	{
		receivePos >> type;
		receivePos >> id;
		incomingClient.ip = sender;
		incomingClient.portUDP = port;
		incomingClient.clientID = id;
		bool match = false;
		for (int i = 0; i < clientsUDP.size(); i++)
		{
			if (clientsUDP[i].clientID == incomingClient.clientID)
			{
				match = true;
			}
		}
		if (!match)
		{
			clientsUDP.push_back(incomingClient);
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
			int coinNum = 0;
			int type = 9;
			receivePos >> coinNum;
			std::cout << id << " collected coin:" << coinNum << "\n";
			sf::Packet coin_Picked;
			coin_Picked << type;
			coin_Picked << coinNum;
			for (int i = 0; i < clientsUDP.size(); i++)
			{
				unsigned short port = clientsUDP[i].portUDP;
				sf::IpAddress address = clientsUDP[i].ip;
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
	}
}


void server::sendUDP(sf::Packet receivePosVar,int ID)
{
	coinPos = sf::Vector2f(100, 100);
	float coin_posX = coinPos.x;
	float coin_posY = coinPos.y;
	int type = 7;
		sf::Packet move;
		//int id_temp;
		float posX;
		float posY;
		//receivePosVar >> id_temp;
		receivePosVar >> posX;
		receivePosVar >> posY;
		//std::cout <<ID<<  "Sent the position; " << "position gotten:\n " << posX << "  -  " << posY << "\n\n";
		sf::Packet sendToClients;
		sendToClients << type;
		sendToClients << ID;
		sendToClients << posX;
		sendToClients << posY;


		for (int i = 0; i < clientsUDP.size(); i++)
		{
			unsigned short port = clientsUDP[i].portUDP;
			sf::IpAddress address = clientsUDP[i].ip;
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

void server::propsPos()
{


	sf::Packet coinPos;
	
	
}

void server::startingPositions()
{
	if (clients.size() == 1)
	{
		Starting_posX = 100;
		Starting_posY = 200;
		Enemy_Starting_posX = 1000;
		Enemy_Starting_posY = 300;
	}
	else if (clients.size() == 2)
	{
		Starting_posX = 1000;
		Starting_posY = 300;
		Enemy_Starting_posX = 10;
		Enemy_Starting_posY = 20;
	}


}

void server::IdAndPositionSetter(sf::TcpSocket* sock, std::string name_)
{
	sf::Packet Id_And_Pos_Setter;
	Id_And_Pos_Setter << id_setter;
	Id_And_Pos_Setter << Starting_posX;
	Id_And_Pos_Setter << Starting_posY;
	Id_And_Pos_Setter << Enemy_Starting_posX;
	Id_And_Pos_Setter << Enemy_Starting_posY;
	Id_And_Pos_Setter << coinPos.x;
	Id_And_Pos_Setter << coinPos.y;

	if (sock->send(Id_And_Pos_Setter) != sf::Socket::Done)
	{
		std::cout << "Error sending message. \n";
	}
	else
	{
		std::cout << name_ << " is id: " << id_setter << "\n";
		id_setter++;
	}
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
