#pragma once
#include <vector>
#include "Screen.h"
#include "Player.h"
#include "AssetManager.h"

class Game;

class LevelScreen :
	public Screen
{
public:
	LevelScreen(Game* newGamePointer);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

private:
	void Restart();

	Player player;

	bool gameRunning;

	sf::RenderWindow* window;
};