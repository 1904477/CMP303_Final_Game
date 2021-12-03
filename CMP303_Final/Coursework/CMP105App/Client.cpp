#include "Client.h"

Client::Client(sf::IpAddress& ip, unsigned short& port, Player& p, Player& enemy, std::string& name_, sf::TcpSocket* sock)
{
	socket = sock;
	render_enemy = false;
	//udp_port = sf::UdpSocket::AnyPort;
	server_address = ip;
	//socket.setBlocking(true);
	//sf::Socket::Status Tcp = socket->connect(ip, port);
	//if (Tcp != sf::Socket::Done)
	//{
	//	printf("Client couldn't connect'\n");
	//	printf("Server could be full, non existing or under maintenance\n");
	//}
	//else
	//{

		//Name_Sending_TCP(socket,name);
	ID_And_Positions_Getter();
	Setup(&p, &enemy);
	//std::cout << "IS IT CONNECTED " << connected_ << "\n";
}

Client::~Client()
{
	
}

void Client::HandleInput(sf::Event *Ev ,Input* input,sf::RenderWindow* window, Player* p)
{
	
		if (input->isKeyDown(sf::Keyboard::T) && open_chat == false)		//Chat opens 
		{
			std::cout << "Chat should be open\n";
			input->setKeyUp(sf::Keyboard::T);
			open_chat = true;		//Chat opens on t pressed
			chat_empty_on_open = true;		//Chat emptied on t pressed
		}
		else if (input->isKeyDown(sf::Keyboard::Escape) && open_chat == true)		//Chat closes 
		{
			std::cout << "Chat should close and be emptied\n";		
			input->setKeyUp(sf::Keyboard::Escape);	
			if (userText.size() > 0)		//Empties chat when the user closes it
					userText.clear();
			open_chat = false;		//Chat is closed
		}

	if (open_chat == true)		//If the chat is open
	{
		is_chat_open = true;		//Chat is open
		if (Ev->type == sf::Event::KeyPressed)			//If a key is pressed
		{
			if (Ev->key.code == sf::Keyboard::Return)		//Send message on enter
			{
				if (userText.size() > 0)
					sendMessageTCP(p);
				open_chat = false;		//Chat closes once the user sends a message
			}

			else if (Ev->key.code == sf::Keyboard::BackSpace)		//Removes last letter in the message in the chat
			{
				if (userText.size() > 0)
					userText.pop_back();
			}
			else if (Ev->key.code == sf::Keyboard::Space)		//Space added
			{
				userText += ' ';
			}

		}
		else if (Ev->type == sf::Event::TextEntered)		//Text is being entered
		{
			if (32 < Ev->text.unicode && Ev->text.unicode < 128)
				userText += (char)Ev->text.unicode;
			std::cout << "text is being entered\n\n";

			if (chat_empty_on_open == true)			//If on chat opening the chat has message ('t') chat is emptied
			{
				userText.pop_back();
				chat_empty_on_open = false;
			}
		}
	}
}

void Client::TCPReceive()
{
	sf::Packet packet;
	socket->receive(packet);		//Packet that are being received by other clients through the server
	std::string temptext;			//Stored in a temporary text
	if (packet >> temptext)
	{
		sf::Text displayText(temptext, font, 20);
		displayText.setFillColor(sf::Color::Blue);
		chat.push_back(displayText);
	}

}

void Client::ID_And_Positions_Getter()
{
	int type;
	sf::Packet setupAsk;
	setupAsk << 19;
	if (socket->send(setupAsk) != sf::Socket::Done)
	{
		std::cout << "Error getting ID\n";
	}

	sf::Packet Id_Getter;
	sf::Packet CoinposGetter;

	if (socket->receive(Id_Getter) != sf::Socket::Done)
	{
		std::cout << "Error getting ID\n";
	}
	else
	{
		Id_Getter >> type;
		if (type == 1)
		{
			Id_Getter >> id_getter;
			std::cout << "Your id is: " << id_getter << std::endl;
			Id_Getter >> Player_Starting_posX;
			Id_Getter >> Player_Starting_posY;
			std::cout << "Your starting position is " << Player_Starting_posX << "  :  " << Player_Starting_posY << std::endl;
			Id_Getter >> Enemy_Starting_posX;
			Id_Getter >> Enemy_Starting_posY;
			std::cout << "Enemy starting position is " << Enemy_Starting_posX << "  :  " << Enemy_Starting_posY << std::endl;
		}	
	}
	if (socket->receive(CoinposGetter) != sf::Socket::Done)
	{
		std::cout << "Error getting ID\n";
	}
	else
	{
		CoinposGetter >> type;
		std::cout << type;
		if (type == 2)
		{
			for (int i = 0; i < 10; i++)
			{
				CoinposGetter >> coinPos[i].x;
				CoinposGetter >> coinPos[i].y;
				std::cout << coinPos[i].x << "  -  " << coinPos[i].y << std::endl;
				Tools.coinGenerator(&coinPos[i]);
			}
		}
	}
}

void Client::CheckCollision(Player* p)
{
	for (int i = 0; i < Tools.coins.size(); i++)
	{
		if (Tools.coins[i].getPicked() == false)
		{
			if (Collision::checkBoundingBox(p, &Tools.coins[i]))
			{
				std::cout << "coin picked and sent to server\n";
				sf::Packet coinPicked;
				int type = 8;
				coinPicked << type << id_getter << i;
				if (udp_socket.send(coinPicked, server_address, udp_port) == sf::Socket::Done)
				{
					
					Tools.coins[i].setPicked(true);
				}

			}
		}
	}
}

void Client::textSetup(sf::RenderWindow* window)
{
	sf::Vector2u w_size = window->getSize();		//Messages are being rendered
	int prev_messages_pos_ = drawText.getPosition().y - 20;
	window->draw(drawText);

	if (chat.size() > 0)		//If chat is bigger than zero, a reverse iterator places them in a down to up position
	{
		std::vector<sf::Text>::reverse_iterator rev;
		int count = 0;
		for (rev = chat.rbegin(); rev != chat.rend(); ++rev)
		{
			rev->setPosition(0, prev_messages_pos_ - count * 25);
			++count;
			window->draw(*rev);
		}
	}
	if (chat.size() == 5)			//Chat can't have more than five messages.
	{
		chat.erase(chat.begin());
	}
	drawText.setString(userText);
	drawText.setFont(font);
	drawText.setCharacterSize(20);
	drawText.setFillColor(sf::Color::Red);
	drawText.setPosition(0, w_size.y - 100);
}

void Client::disconnect(Player* p,Input* input, sf::RenderWindow* window)
{
	sf::Packet temp;
	int type = 6;
	int id = id_getter;

	temp << type;
	temp << id;
	
//	temp << id_getter;
	//std::cout << id_getter;
	if (input->isKeyDown(sf::Keyboard::Escape))
	{

		if (udp_socket.send(temp, sf::IpAddress::getLocalAddress(), udp_port) != sf::Socket::Done)
		{
			std::cout << "Error sending disconnect command to server" << std::endl;
		}
		else
		{
			std::cout << "Disconnected" << std::endl;
			window->close();
		}
	}
}

void Client::UDPReceive(Player* p, Player* enemy)
{
	sf::IpAddress sender = sf::IpAddress::getLocalAddress();
	sf::Packet updated_pos;
	int enemyID;
	int type = 0;
	unsigned int type_pos;
	unsigned short a = udp_port;
	while(udp_socket.receive(updated_pos, sender, a) == sf::Socket::Done)
	{
		updated_pos >> type;

		if (type == 7)
		{
			updated_pos >> enemyID;
			if (id_getter != enemyID)
			{
				updated_pos >> enemy_received.x >> enemy_received.y;

			//	std::cout << enemyID << "Is at position positions: \n" << enemy_new_x << "-" << enemy_new_y << "\n";
			
				render_enemy = true;

			}
		}
		if (type == 9)
		{
			int coinNum;
			updated_pos >> coinNum;
			Tools.coins[coinNum].setPicked(true);
		}


	}

}

void Client::Setup(Player* p, Player* enemy)
{
	udp_socket.setBlocking(false);
	socket->setBlocking(false);
	open_chat = false;			//Know whether chat is open
	connected_ = true;		//Know whether client is connected
	chat_empty_on_open = false;			//Empties chat when t is pressed and the chat opens
	is_chat_open = false;		//Variable to know whether chat is open
	speed = 150;
	p->setPosition(Player_Starting_posX, Player_Starting_posY);
	enemy->setPosition(Enemy_Starting_posX, Enemy_Starting_posY);
}

bool Client::getConnectedStatus()
{
	return connected_;
}

bool Client::renderEnemy()
{
	return render_enemy;
}

void Client::interpolateEnemyPos(Player* enemy,float dt)
{
	sf::Vector2f next_pos=enemy_received;

	sf::Vector2f pos = enemy->getPosition();

	sf::Vector2f dir = next_pos - pos;
	
	pos += dir * 40.0f * dt;

	enemy->setPosition(pos);
}


void Client::Update(Input* input,sf::Event* Ev, sf::RenderWindow* window, Player* p, Player* enemy,float dt)
{
	UDP_sendPosition(p,input,dt);
	
	interpolateEnemyPos(enemy,dt);
	UDPReceive(p, enemy);
	CheckCollision(p);
	disconnect(p,input, window);
	TCPReceive();
}

void Client::Render(sf::RenderWindow* window)
{
	textSetup(window);
	Tools.renderCoin(window);
}

void Client::sendMessageTCP(Player* p)			//Sends a message, adding the ID in the packet
{
	sf::Text displayText("You: "+userText, font, 20);
	displayText.setFillColor(sf::Color::White);
	chat.push_back(displayText);
	sf::Packet packet;
	packet  << name + ": " + userText;
	if (socket->send(packet) != sf::Socket::Done)
	{
		std::cout << "Error sending message. \n";
	}
	userText = "";			//Empties the chat after sending
}
void Client::UDP_sendPosition(Player* p, Input* input,float dt)
{
	sf::Time time1 = clock.getElapsedTime();
	sf::Packet temp;
	temp << 3;
	float posX = p->getPosition().x;
	float posY = p->getPosition().y;
	if (input->isKeyDown(sf::Keyboard::A))
	{
		p->move(-speed*dt, 0);
	}
	if (input->isKeyDown(sf::Keyboard::W))
	{
		p->move(0 , -speed*dt);
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		p->move(speed *dt, 0);
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		p->move(0, speed *dt);
	}
	if (time1.asSeconds() >= 0.5)
	{
		temp <<id_getter<< posX << posY;
		if (udp_socket.send(temp, server_address, udp_port) != sf::Socket::Done)
		{
			printf("message can't be sent\n");
		}
		else if(time1.asSeconds() >= 0.5)
		{
			
		}
		clock.restart();
	}
}
