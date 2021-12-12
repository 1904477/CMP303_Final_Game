#include "Menu.h"
#include"Framework\GameState.h"
#include"Framework\GameObject.h"
#include<iostream>

Menu::Menu(sf::RenderWindow* hwnd, GameState* gs, Input* in, sf::TcpSocket* sock)		//Different pointers to main
{
	gameState = gs;
	window = hwnd;
	input = in;
	Tcp = sock;
}

Menu::~Menu()
{
}

void Menu::Init()
{
	IpEnter = "";			//Once menu is initialised, every space for inputs is reset to empty
	nameEnter = "";
	Graphics.setup(window);

	renderJoinGame = false;			
	IPorName = "IP";
	if (!font.loadFromFile("font/arial.ttf")) //SETS THE GAME NAME IN THE MENU SCREEN, after this, other texts initialised
	{
		std::cout << "NO \n";
	}
	gameName.setFont(font);
	gameName.setString("Ball Collector");
	gameName.setCharacterSize(50);
	gameName.setFillColor(sf::Color::White);
	gameName.setPosition(window->getSize().x / 2.5, window->getSize().y / 12);

	if (!font.loadFromFile("font/arial.ttf")) 
	{
		std::cout << "NO \n";
	}
	IPaddressEnter.setFont(font);
	IPaddressEnter.setString("Type the IP-address you want to connect to");
	IPaddressEnter.setCharacterSize(20);
	IPaddressEnter.setFillColor(sf::Color::White);
	IPaddressEnter.setPosition(0, window->getSize().y / 3);

	if (!font.loadFromFile("font/arial.ttf")) 
	{
		std::cout << "NO \n";
	}
	nameEnterOrder.setFont(font);
	nameEnterOrder.setString("Type your name");
	nameEnterOrder.setCharacterSize(20);
	nameEnterOrder.setFillColor(sf::Color::White);
	nameEnterOrder.setPosition(0.0f, window->getSize().y / 1.8);


	if (!font.loadFromFile("font/arial.ttf")) 
	{
		std::cout << "NO \n";
	}
	joinLobbyDisplay.setFont(font);
	joinLobbyDisplay.setString("Type your name and press enter to join the lobby");
	joinLobbyDisplay.setCharacterSize(20);
	joinLobbyDisplay.setFillColor(sf::Color::White);
	joinLobbyDisplay.setPosition(window->getSize().x / 3.3f, window->getSize().y / 1.2f);


	IpEnterDisplay.setFillColor(sf::Color::White);
	IpEnterDisplay.setFont(font);
	IpEnterDisplay.setCharacterSize(20);
	IpEnterDisplay.setPosition(0, window->getSize().y /3+50);

	nameEnterText.setFillColor(sf::Color::White);
	nameEnterText.setFont(font);
	nameEnterText.setCharacterSize(20);
	nameEnterText.setPosition(0, window->getSize().y / 1.8+50);

}

void Menu::handleInput(sf::Event* Ev)
{
	sf::Vector2u w_size = window->getSize();		//Messages are being rendered
	if (input->isKeyDown(sf::Keyboard::Escape))	//IF EXIT IS PRESSED,THE SCREEN CLOSES
	{
		window->close();
	}
	

	if (Ev->type == sf::Event::TextEntered)		//Text is being entered
	{
		if (IPorName == "IP")				//IP text selected and entered
		{
			if (32 < Ev->text.unicode && Ev->text.unicode < 128)
			{
				IpEnter += (char)Ev->text.unicode;
			}
		}
		else if (IPorName == "Name")	//name text selected and entered
		{
			if (32 < Ev->text.unicode && Ev->text.unicode < 128)
			{
				nameEnter += (char)Ev->text.unicode;
			}
		}
	}
	if (Ev->type == sf::Event::KeyPressed && IPorName == "IP")			//If you are entering the ip
	{
		IpEnterFunction(Ev);
	}

	else if (Ev->type == sf::Event::KeyPressed && IPorName == "Name")			//If you are entering the name
	{
		nameEnterFunction(Ev);
	}
	IpEnterDisplay.setString(IpEnter);			//The text is updated with the ipEnter variable
	nameEnterText.setString(nameEnter);				//The text is updated with the nameEnter variable
	
}

void Menu::update(float dt)
{
}

void Menu::render()
{
	beginDraw();		//Render different elements of the menu
	Graphics.render(window);
	window->draw(gameName);
	window->draw(IPaddressEnter);
	window->draw(IpEnterDisplay);
	window->draw(nameEnterText);
	window->draw(nameEnterOrder);
	
	if (renderJoinGame == true)			//Appears only once ip is entered
	{
		Graphics.renderPlayButton(window);
		window->draw(joinLobbyDisplay);
	}
	
	endDraw();
}

void Menu::beginDraw()
{
	window->clear(sf::Color(0,71,100));
}

void Menu::endDraw()
{
	window->display();
}

void Menu::reset()
{
}

void Menu::Name_Sending_TCP()		//If IP is entered, send name to server
{

	printf("Connection successful!\n\n");
	sf::Packet name_sender;
	int type = sendName;
	name_sender << type;
	name_sender << nameEnter;
	std::cout << nameEnter << std::endl;
	if (Tcp->send(name_sender) != sf::Socket::Done)
	{
		std::cout << "Error setting up\n";
	}


}

void Menu::nameEnterFunction(sf::Event* Event_)			//Enter the name
{
	if (Event_->key.code == sf::Keyboard::Return)		//Send message on enter
	{
		nameEnterText.setFillColor(sf::Color::Green);
		sf::Packet name_sent;
		players += nameEnter;
		connect_attempt = true;
		IPorName == "";
		
		sf::Socket::Status Tcp_Stat = Tcp->connect(ipAdress_server, 53000);			//Once name is entered, connect to IP and port
		if (Tcp_Stat != sf::Socket::Done)
		{
			printf("Client couldn't connect'\n");
			printf("Server could be full, non existing or under maintenance\n");
			Init();			//If connection couldn't happen, restart menu
		}
		else
		{
					//If you managed to connect
		}
		{
	
			std::cout << "IS IT CONNECTED " << "\n";
			Name_Sending_TCP();			//send name to server
			gameState->setCurrentState(State::LEVEL);			//Enter in game and game is started.
		}

	}
	else if (Event_->key.code == sf::Keyboard::BackSpace)		//Removes last letter in the message in the chat
	{
		if (nameEnter.size() > 0)
			nameEnter.pop_back();
	}
	else if (Event_->key.code == sf::Keyboard::Space)		//Space added
	{
		nameEnter += ' ';
	}
}

void Menu::IpEnterFunction(sf::Event* Event_)
{
	if (Event_->key.code == sf::Keyboard::Return)		//Send message on enter
	{
		ipAdress_server = sf::IpAddress(IpEnter);
		//ipAdress_server = sf::IpAddress::getLocalAddress();
		IpEnterDisplay.setFillColor(sf::Color::Green);
		IPorName = "Name";
		renderJoinGame = true;		//Once IP is entered, enter name and render the button to join the game
	}
	else if (Event_->key.code == sf::Keyboard::BackSpace)		//Removes last letter in the message in the chat
	{
		if (IpEnter.size() > 0)
			IpEnter.pop_back();
	}
	else if (Event_->key.code == sf::Keyboard::Space)		//Space added
	{
		IpEnter += ' ';
	}
}

sf::IpAddress Menu::IpTransmissionToLevel()
{
	return ipAdress_server;
}

std::string Menu::NameTransmissionToLevel()
{
	return nameEnter;
}
