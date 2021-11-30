#include "client.h"
void client::Init()
{
	sf::IpAddress ip_;
	ip_ = ip_.getLocalAddress();
	sf::TcpSocket socket;
	bool done = false;
	std::string id;
	std::string text = "";

	std::cout << "enter online id: ";
	std::cin >> id;

	socket.connect(ip_, 10);
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Chat");
	std::vector <sf::Text>chat;

	sf::Packet packet;
	packet << id;
	socket.send(packet);
	socket.setBlocking(false);
	window.setTitle(id);

	sf::Font font;
	font.loadFromFile("arial.ttf");
	while (!done)
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				window.close();
			case::sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (Event.key.code == sf::Keyboard::Return)
				{
					sf::Packet packet;
						packet << id + ": " + text;
						socket.send(packet);
						sf::Text displayText(text, font, 20);
						displayText.setFillColor(sf::Color::Red);
						chat.push_back(displayText);
						text = "";
				}
				break;
			case sf::Event::TextEntered:
				text += Event.text.unicode;
			//	break;
			}
		}
		sf::Packet packet;
		socket.receive(packet);
		std::string temptext;
		if (packet >> temptext)
		{
			sf::Text displayText(temptext, font, 20);
			displayText.setFillColor(sf::Color::Blue);
			chat.push_back(displayText);
		}
		int i = 0;
		for (i; i < chat.size(); i++)
		{
			chat[i].setPosition(0, i * 20);
			window.draw(chat[i]);
		}
		sf::Text drawText(text, font, 20);
		drawText.setFillColor(sf::Color::Red);
		drawText.setPosition(0, i * 20);
		window.draw(drawText);
		//std::cout << "text is being rendered";
		window.display();
		window.clear();
	}
	
}