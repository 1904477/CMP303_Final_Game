#include "GraphicsTools.h"

void GraphicsTools::setup(sf::RenderWindow* hwnd)
{
	font.loadFromFile("font/arial.ttf");

	rectangles.push_back(sf::RectangleShape());
	rectangles.back().setSize(sf::Vector2f(400, 30));
	rectangles.back().setPosition(0, hwnd->getSize().y / 1.8 + 50); 
	rectangles.back().setFillColor(sf::Color::Black);
	rectangles.back().setOutlineColor(sf::Color::Cyan);
	rectangles.back().setOutlineThickness(3);

	rectangles.push_back(sf::RectangleShape());
	rectangles.back().setSize(sf::Vector2f(400, 30));
	rectangles.back().setPosition(0, hwnd->getSize().y / 3 + 50);
	rectangles.back().setFillColor(sf::Color::Black);
	rectangles.back().setOutlineColor(sf::Color::Cyan);
	rectangles.back().setOutlineThickness(3);

	renderPlay.push_back(sf::RectangleShape());
	renderPlay.back().setSize(sf::Vector2f(450, 30));
	renderPlay.back().setPosition(hwnd->getSize().x / 3.3 , hwnd->getSize().y / 1.2 );
	renderPlay.back().setFillColor(sf::Color::Black);
	renderPlay.back().setOutlineColor(sf::Color::Cyan);
	renderPlay.back().setOutlineThickness(3);

	PreGameText.push_back(sf::Text());
	PreGameText.back().setFont(font);
	PreGameText.back().setString("Waiting for the other player\n");
	PreGameText.back().setCharacterSize(30);
	PreGameText.back().setFillColor(sf::Color::White);
	PreGameText.back().setPosition(hwnd->getSize().x / 8, hwnd->getSize().y / 12);

	PostGameText.push_back(sf::Text());
	PostGameText.back().setFont(font);
	PostGameText.back().setCharacterSize(30);
	PostGameText.back().setFillColor(sf::Color::White);
	PostGameText.back().setPosition(hwnd->getSize().x / 8, hwnd->getSize().y / 12);
	PostGameText.back().setString("Game is started, you can move play!");



	InGameBox.push_back(sf::RectangleShape());
	InGameBox.back().setSize(sf::Vector2f(300, 150));
	InGameBox.back().setPosition(0, hwnd->getSize().y / 1.4-30);
	InGameBox.back().setFillColor(sf::Color(140, 138, 252));
	InGameBox.back().setOutlineColor(sf::Color::Cyan);
	InGameBox.back().setOutlineThickness(3);

	InGameBox.push_back(sf::RectangleShape());
	InGameBox.back().setSize(sf::Vector2f(300, 30));
	InGameBox.back().setPosition(0, (hwnd->getSize().y / 1.4 +90));
	InGameBox.back().setFillColor(sf::Color(255,195,77));
	InGameBox.back().setOutlineColor(sf::Color::Cyan);
	InGameBox.back().setOutlineThickness(3);

	player1Score.setFont(font);
	player1Score.setCharacterSize(30);
	player1Score.setFillColor(sf::Color::White);
	player1Score.setPosition(hwnd->getSize().x / 1.2-50, hwnd->getSize().y / 12);
	
	player2Score.setFont(font);
	player2Score.setCharacterSize(30);
	player2Score.setFillColor(sf::Color::White);
	player2Score.setPosition(hwnd->getSize().x / 1.2-50, hwnd->getSize().y / 12+50);
}

void GraphicsTools::render(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < rectangles.size(); i++)
	{
		hwnd->draw(rectangles[i]);
	}
	
}

void GraphicsTools::coinGenerator(sf::Vector2f coinPos_[10])
{
		Coin coin;
		coin.setPosition(coinPos_->x,coinPos_->y);
		coin.Update();
		coins.push_back(coin);
}

void GraphicsTools::renderCoin(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].Render(hwnd);
	}

}

void GraphicsTools::renderPlayButton(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < renderPlay.size(); i++)
	{
		hwnd->draw(renderPlay[i]);
	}
}

void GraphicsTools::preGameElementsRender(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < PreGameText.size(); i++)
	{
		hwnd->draw(PreGameText[i]);
	}
}

void GraphicsTools::inLevelElements(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < InGameBox.size(); i++)
	{
		hwnd->draw(InGameBox[i]);
	}
}

void GraphicsTools::postGameElementsRender(sf::RenderWindow* hwnd,float scoreP1,float scoreP2)
{
	player1Score.setString("Your Score: "+std::to_string(scoreP1));
	player2Score.setString("Player2 Score: " + std::to_string(scoreP2));

	hwnd->draw(player1Score);
	hwnd->draw(player2Score);
	for (int i = 0; i < PostGameText.size(); i++)
	{
		hwnd->draw(PostGameText[i]);
	}
}
