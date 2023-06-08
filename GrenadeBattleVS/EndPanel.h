#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class EndPanel :
	public Object
{
public:
	EndPanel(sf::RenderWindow* newWindow, std::string titleText, std::string messageText);

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	void SetPosition(sf::Vector2f newPosition) override;

	void StartAnimation(bool p1Win);
	void ResetPosition();

	void SetBody(std::string bodyText);

private:
	sf::Sprite background;
	sf::Text message;
	sf::RenderWindow* window;

	float xPos;

	bool animatingIn;
	sf::Clock animationClock;
};