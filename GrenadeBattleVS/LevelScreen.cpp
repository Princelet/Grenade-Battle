#include <fstream>
#include "LevelScreen.h"
#include "Game.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, gameRunning(true)
	, window(newGamePointer->GetWindow())
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player.Update(frameTime);
		player.SetColliding(false);
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			Restart();
	}

}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	player.Draw(target);
}

void LevelScreen::Restart()
{
	player.SetPosition(500.0f, 500.0f);
	gameRunning = true;
}