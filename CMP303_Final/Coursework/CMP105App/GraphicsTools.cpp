#include "GraphicsTools.h"

void GraphicsTools::setup(sf::RenderWindow* hwnd)				//GAME ELEMENTS(TEXT AND BOXES)
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
	PostGameText.back().setString("Game is started, you can now move and play!");

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

	gameStartTimerText.setFont(font);
	gameStartTimerText.setCharacterSize(30);
	gameStartTimerText.setFillColor(sf::Color::Green);
	gameStartTimerText.setPosition(hwnd->getSize().x / 1.2-20 , hwnd->getSize().y / 2);

	coinHasBeenPicked.setFont(font);
	coinHasBeenPicked.setCharacterSize(20);
	coinHasBeenPicked.setFillColor(sf::Color::White);
	coinHasBeenPicked.setPosition(hwnd->getSize().x / 1.2, hwnd->getSize().y / 5);
}

void GraphicsTools::render(sf::RenderWindow* hwnd)
{
	for (int i = 0; i < rectangles.size(); i++)
	{
		hwnd->draw(rectangles[i]);
	}
	
}

void GraphicsTools::coinGenerator(sf::Vector2f coinPos_[30])
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

void GraphicsTools::postGameElementsRender(sf::RenderWindow* hwnd,float gameTime)
{

	gameStartTimerText.setString("Game time: "+std::to_string(gameTime));
	

	hwnd->draw(gameStartTimerText);
	
	hwnd->draw(coinHasBeenPicked);
	for (int i = 0; i < PostGameText.size(); i++)
	{
		hwnd->draw(PostGameText[i]);
	}
}

void GraphicsTools::pickedCoin(int id, int coinNum)
{
	coinHasBeenPicked.setString(std::to_string(id) + " picked the coin: " + std::to_string(coinNum));
}
