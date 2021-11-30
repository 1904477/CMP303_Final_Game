#include "Menu.h"
#include"Framework\GameState.h"
#include"Framework\GameObject.h"
#include<iostream>

Menu::Menu(sf::RenderWindow* hwnd, GameState* gs, Input* in)
{
	gameState = gs;
	window = hwnd;
	input = in;
	
}

Menu::~Menu()
{
}

void Menu::Init()
{
	IpEnter = "";
	nameEnter = "";
	Graphics.setup(window);

	IPorName = "IP";
	if (!font.loadFromFile("font/arial.ttf")) //SETS THE GAME NAME IN THE MENU SCREEN
	{
		std::cout << "NO \n";
	}
	gameName.setFont(font);
	gameName.setString("Game");
	gameName.setCharacterSize(50);
	gameName.setFillColor(sf::Color::White);
	gameName.setPosition(window->getSize().x / 2.5, window->getSize().y / 12);

	if (!font.loadFromFile("font/arial.ttf")) //SETS THE GAME NAME IN THE MENU SCREEN
	{
		std::cout << "NO \n";
	}
	IPaddressEnter.setFont(font);
	IPaddressEnter.setString("Type the IP-address you want to connect to");
	IPaddressEnter.setCharacterSize(20);
	IPaddressEnter.setFillColor(sf::Color::White);
	IPaddressEnter.setPosition(0, window->getSize().y / 3);

	if (!font.loadFromFile("font/arial.ttf")) //SETS THE GAME NAME IN THE MENU SCREEN
	{
		std::cout << "NO \n";
	}
	nameEnterOrder.setFont(font);
	nameEnterOrder.setString("Type your name");
	nameEnterOrder.setCharacterSize(20);
	nameEnterOrder.setFillColor(sf::Color::White);
	nameEnterOrder.setPosition(0.0f, window->getSize().y / 1.8);

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
	if (input->isKeyDown(sf::Keyboard::Space)) //IF SPACE IS PRESSED IN MENU, CONTROLS STARTS
	{
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::Space);
	}

	if (Ev->type == sf::Event::TextEntered)		//Text is being entered
	{
		if (IPorName == "IP")
		{
			if (32 < Ev->text.unicode && Ev->text.unicode < 128)
			{
				IpEnter += (char)Ev->text.unicode;
			}
		}
		else if (IPorName == "Name")
		{
			if (32 < Ev->text.unicode && Ev->text.unicode < 128)
			{
				nameEnter += (char)Ev->text.unicode;
			}
		}
	}
	if (Ev->type == sf::Event::KeyPressed && IPorName == "IP")			//If a key is pressed
	{
		if (Ev->key.code == sf::Keyboard::Return)		//Send message on enter
		{
			ipAdress_server = sf::IpAddress(IpEnter);
			std::cout << "Ip address is " << IpEnter;
			IpEnterDisplay.setFillColor(sf::Color::Green);
			IPorName = "Name";
		}
		else if (Ev->key.code == sf::Keyboard::BackSpace)		//Removes last letter in the message in the chat
		{
			if (IpEnter.size() > 0)
				IpEnter.pop_back();
		}
		else if (Ev->key.code == sf::Keyboard::Space)		//Space added
		{
			IpEnter += ' ';
		}
	}

	else if (Ev->type == sf::Event::KeyPressed && IPorName == "Name")			//If a key is pressed
	{
		if (Ev->key.code == sf::Keyboard::Return)		//Send message on enter
		{
			std::cout << "Name is" << nameEnter;
			nameEnterText.setFillColor(sf::Color::Green);
			sf::Packet name_sent;
			int type = 1;
			name_sent << type;
			name_sent << nameEnter;
			players += nameEnter;
			connect_attempt = true;

		}
		else if (Ev->key.code == sf::Keyboard::BackSpace)		//Removes last letter in the message in the chat
		{
			if (nameEnter.size() > 0)
				nameEnter.pop_back();
		}
		else if (Ev->key.code == sf::Keyboard::Space)		//Space added
		{
			nameEnter += ' ';
		}
	}

		IpEnterDisplay.setString(IpEnter);
		nameEnterText.setString(nameEnter);
		std::cout << nameEnter << std::endl;
}

void Menu::update(float dt)
{
}

void Menu::render()
{
	beginDraw();
	Graphics.render(window);

	window->draw(gameName);
	window->draw(IPaddressEnter);
	window->draw(IpEnterDisplay);
	window->draw(nameEnterText);
	window->draw(nameEnterOrder);
	
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

sf::IpAddress Menu::IpTransmissionToLevel()
{
	return ipAdress_server;
}

std::string Menu::NameTransmissionToLevel()
{
	return nameEnter;
}
