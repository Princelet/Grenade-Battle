#include "EndPanel.h"
#include "AssetManager.h"
#include "Easing.h"

EndPanel::EndPanel(sf::RenderWindow* newWindow, std::string titleText, std::string messageText)
	: Object()
	, background()
	, message()
	, window(newWindow)
	, animatingIn(false)
	, animationClock()
	, xPos()
{
	AssetManager::SetupText(message, "dogica", "Cyan", messageText);

	ResetPosition();
}

void EndPanel::Update(sf::Time frameTime)
{
	if (animatingIn)
	{
		float yPos = window->getSize().y;
		float finalYPos = (window->getSize().y - background.getGlobalBounds().height) * 0.5f;

		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);
		float duration = 1.2f;
		float time = animationClock.getElapsedTime().asSeconds();

		SetPosition(Easing::QuadIn(begin, change, duration, time));

		if (time >= duration)
		{
			SetPosition(begin + change);
			animatingIn = false;
		}
	}
}

void EndPanel::Draw(sf::RenderTarget& target)
{
	target.draw(message);
}

void EndPanel::SetPosition(sf::Vector2f newPosition)
{
	float messageX = (background.getGlobalBounds().width - message.getGlobalBounds().width) * 0.5f;
	message.setPosition(newPosition.x + messageX, newPosition.y + 150);
}

void EndPanel::StartAnimation(bool p1Win)
{
	if (p1Win)
		message.setString("Player 1 Wins!");
	else
		message.setString("Player 2 Wins!");

	animatingIn = true;
	animationClock.restart();
}

void EndPanel::ResetPosition()
{
	xPos = (window->getSize().x - background.getGlobalBounds().width) * 0.5f;
	float yPos = (window->getSize().y - background.getGlobalBounds().height) * 0.5f;
	SetPosition(sf::Vector2f(xPos, yPos));
}

void EndPanel::SetBody(std::string bodyText)
{
	message.setString(bodyText);
}