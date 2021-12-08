#include "Client.h"

Client::Client(sf::IpAddress& ip, unsigned short& port, Player& p, Player& player2, std::string& name_, sf::TcpSocket* sock,sf::RenderWindow *window)
{
	socket = sock;
	render_enemy = false;
	Ip_serverAddress = ip;
	std::cout << Ip_serverAddress << "\n";
	window_ = window;
	ID_And_Positions_Getter();
	Setup(&p);
	udp_port = 1111;
	name = name_;
	Tools.setup(window_);
}

Client::~Client()
{
	
}

void Client::Update(Input* input, sf::Event* Ev, Player* p, Player* enemy, float dt)
{
	TCPReceive();
	if (canMove == true)			//The positions and movements are possible only when second player joins.
		UDP_sendPosition(p, input, dt);

	UDPReceive(p, enemy);
	interpolateEnemyPos(enemy, dt);

	CheckCollision(p);
	disconnect(p, input);
}

void Client::Render()
{
	if(open_chat==true)
	Tools.inLevelElements(window_);

	if (render_preStart == true)			//Rendered before the second player joins, 
		Tools.preGameElementsRender(window_);		//Render coins 

	else if (renderStartTimer == true)		//Rendered after the second player joins, 
		Tools.postGameElementsRender(window_,Player1.score,Player2.score, gameTime);

	textSetup(window_);			//Sets up the chat positions.
	Tools.renderCoin(window_);		//Render coins 
}

void Client::ID_And_Positions_Getter()
{

	askSetup();
	sf::Packet Id_Getter;
	if (socket->receive(Id_Getter) != sf::Socket::Done)
	{
		std::cout << "Error getting ID\n";
	}
	else
	{
		int type;
		Id_Getter >> type;
		if (type == 1)
		{
			Id_Getter >> id_getter;
			std::cout << "Your id is: " << id_getter << std::endl;
			Id_Getter >> Player1.Player_start_pos.x>> Player1.Player_start_pos.y;
			Id_Getter >> Player2.Player_start_pos.x >> Player2.Player_start_pos.y;
		}
	}

	coinPosGetter();
}

void Client::HandleInput(sf::Event *Ev ,Input* input, Player* p)
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
	sf::Packet startGame;
	if (socket->receive(startGame) != sf::Socket::Done)
	{
	}		
	else
	{
		int type = 0;
		startGame >> type;
		if (type == 5)
		{
				render_preStart = false;
				renderStartTimer = true;
				canMove = true;
		}
		if (type == 8)
		{
			std::string temptext;			//Stored in a temporary text
			if (startGame >> temptext)
			{
				sf::Text displayText(temptext, font, 15);
				displayText.setFillColor(sf::Color::Green);
				chat.push_back(displayText);
			}
		}
	}

}

void Client::sendMessageTCP(Player* p)			//Sends a message in TCP chat, adding the type, name and message.
{
	sf::Text displayText("You: " + userText, font, 15);
	displayText.setFillColor(sf::Color::White);
	chat.push_back(displayText);
	sf::Packet packet;
	packet << name + ": " + userText;
	if (socket->send(packet) != sf::Socket::Done)		//Send message through TCP socket.
	{
		std::cout << "Error sending message. \n";
	}
	userText = "";			//Empties the chat after sending
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
				if (udp_socket.send(coinPicked, Ip_serverAddress, udp_port) == sf::Socket::Done)
				{
					Tools.coins[i].setPicked(true);
				}

			}
		}
	}
}

void Client::CoinPicked(sf::Packet pack,int enemyID)
{

}

void Client::textSetup(sf::RenderWindow* window)
{
	sf::Vector2u w_size = window->getSize();		//Messages are being rendered
	int prev_messages_pos_ = drawText.getPosition().y - 25;
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
	drawText.setCharacterSize(15);
	drawText.setFillColor(sf::Color::Red);
	drawText.setPosition(0, w_size.y - 100);
}

void Client::disconnect(Player* p,Input* input)
{
	sf::Packet temp;
//	int type = sendDisconnection;
	int id = id_getter;

	temp << sendDisconnection;
	temp << id;
	if (input->isKeyDown(sf::Keyboard::Escape))
	{

		if (udp_socket.send(temp, Ip_serverAddress, udp_port) != sf::Socket::Done)
		{
			std::cout << "Error sending disconnect command to server" << std::endl;
		}
		else
		{
			std::cout << "Disconnected" << std::endl;
			window_->close();
		}
	}
}

void Client::UDPReceive(Player* p, Player* enemy)
{
	sf::IpAddress sender;
	sf::Packet updated_pos;
	int enemyID;			//Enemy id is extrapolated
	int type = 0;
	
	unsigned short a = udp_port;
	while (udp_socket.receive(updated_pos, sender, a) == sf::Socket::Done)
	{
		std::cout << sender << "\n";
		updated_pos >> type;
		if (type == gameTimeReceive)			//Updated game Time
		{
			updated_pos >> gameTime;
			std::cout << time << "\n";
		}
		if (type == receiveEnemyPos)		//RECEIVES UPDATED ENEMY POSITIONS
		{
			updated_pos >> enemyID;

			if (id_getter != enemyID)			//IF THE ID RECEIVED IS NOT THE MAIN PLAYER ONE, THEN UPDATE OTHER PLAYERS POSTIONS
			{
				float temp_time;
				updated_pos >> temp_time;
				std::cout << "Time that you received the position: " << temp_time << "\n";
				updated_pos >> Player2.next_pos.x >> Player2.next_pos.y;		//Updated enemy position 
				messages_times.push_back(temp_time);
				m_Messages.push_back(Player2.next_pos);					//Message history for prediction.
				render_enemy = true;		//Render enemy only if his positions are received.
			}
		}
		if (type == coinHasBeenPicked)				//SOMEONE PICKED A COIN
		{
			int coinNum;
			updated_pos >> enemyID;
			updated_pos >> coinNum;

			if (id_getter != enemyID)			//If who picked a coin is not you, then increase enemy score.
			{
				Player2.score += 5;
				std::cout << "Player 2 picked a coin\n";
			}
			else
			{
				Player1.score += 5;				//Otherwise increase main player score
			}
			Tools.coins[coinNum].setPicked(true);
		}
	}
}

void Client::Setup(Player* p)
{
	font.loadFromFile("font/arial.ttf");			//Initialisation of different texts.
	udp_socket.setBlocking(false);			//Udp set to non blocking. (it doesn't wait for an event to happen.)
	socket->setBlocking(false);			//TCP set to non blocking.
	open_chat = false;			//Know whether chat is open
	connected_ = true;		//Know whether client is connected
	chat_empty_on_open = false;			//Empties chat when t is pressed and the chat opens
	is_chat_open = false;		//Variable to know whether chat is open
	speed = 150;
	p->setPosition(Player1.Player_start_pos.x, Player1.Player_start_pos.y);
}

bool Client::getConnectedStatus()
{
	return connected_;
}

bool Client::renderEnemy()
{
	return render_enemy;
}

void Client::coinPosGetter()
{
	sf::Packet CoinposGetter;			//Starting positions of coins
	if (socket->receive(CoinposGetter) != sf::Socket::Done)
	{
		std::cout << "Error getting ID\n";
	}
	else
	{
		int type = 0;
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

void Client::interpolateEnemyPos(Player* enemy,float dt)			//Interpolation of the position of the enemy in case of lag to avoid "teleport" of enemy sprite.
{
	sf::Vector2f next_pos = Player2.next_pos;
	sf::Vector2f pos = enemy->getPosition();
	sf::Vector2f dir = next_pos - pos;
	float length = sqrt(dir.x * dir.x + dir.y*dir.y);
	if (length < 0.5f) 
	{
		Player2.next_pos += Player2.getDirection() * 1000.0f;
	}
	pos += dir * 20.0f * dt;
	//enemy->setPosition(posllerp

	//float predictedX = -1.0f;
	//float predictedY = -1.0f;
	//float timeSinceLastMsg, timeBetPos;
	//sf::Vector2f vel;
	//sf::Vector2f displ_;
	//sf::Vector2f distBetweenPos;

	//const float msize = m_Messages.size();
	//if (msize < 3) {
	//	return enemy->setPosition(enemy->next_pos.x, enemy->next_pos.y);
	//}
	//const sf::Vector2f msg0 = m_Messages[msize - 1];
	//const sf::Vector2f msg1 = m_Messages[msize - 2];
	//const sf::Vector2f msg2 = m_Messages[msize - 3];
	//
	//const float timeSize = messages_times.size();
	///*if (timeSize < 3) {
	//	return gameTime;
	//}*/
	//const float time0 = messages_times[timeSize - 1];
	//const float time1 = messages_times[timeSize - 2];
	//const float time2 = messages_times[timeSize - 3];
	//
	//timeSinceLastMsg = gameTime - time0;
	//timeBetPos = time0 - time1;
	//distBetweenPos.x = msg0.x - msg1.x;
	//distBetweenPos.y = msg0.y - msg1.y;

	//vel.x = distBetweenPos.x / timeBetPos;
	//vel.y = distBetweenPos.y / timeBetPos;
	//
	//displ_.x = vel.x * timeSinceLastMsg;
	//displ_.y = vel.y * timeSinceLastMsg;

	//predictedX = enemy->getPosition().x + displ_.x;
	//predictedY = enemy->getPosition().y + displ_.y;
	//enemy->setPosition(predictedX, predictedY);


}

void Client::askSetup()
{
	int type;
	sf::Packet setupAsk;			
	setupAsk << askForSetup;
	if (socket->send(setupAsk) != sf::Socket::Done)
	{
		std::cout << "Error getting ID\n";
	}
}


void Client::UDP_sendPosition(Player* p, Input* input,float dt)		//THIS FUNCTION SENDS THE PLAYER'S ACTUAL POSITIONS TO THE SERVER THROUGH UDP
{
	sf::Time time1 = clock.getElapsedTime();			//Timer to keep track of how often we send the positions
	sf::Packet temp;
	temp << sendPlayerPos;		//Type of UDP packet is three
	float posX = p->getPosition().x;
	float posY = p->getPosition().y;
	if (open_chat == false)			//PLAYER CAN MOVE ONLY IF CHAT IS CLOSED.
	{
		if (input->isKeyDown(sf::Keyboard::A))		//MOVEMENTS-------------------
		{
			p->move(-speed * dt, 0);
		}
		if (input->isKeyDown(sf::Keyboard::W))
		{
			p->move(0, -speed * dt);
		}
		if (input->isKeyDown(sf::Keyboard::D))
		{
			p->move(speed * dt, 0);
		}
		if (input->isKeyDown(sf::Keyboard::S))
		{
			p->move(0, speed * dt);
		}
	}
	if (time1.asSeconds() >= 0.5)		//How often send the position of the player.
	{
		temp <<id_getter<< posX << posY;
		if (udp_socket.send(temp, Ip_serverAddress, udp_port) != sf::Socket::Done)			//Send to the UDP socket.
		{
			printf("message can't be sent\n");
		}
		else if(time1.asSeconds() >= 0.5)
		{
			
		}
		clock.restart();			//Restart clock.
	}
}
