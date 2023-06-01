#pragma once
#include <vector>
#include "Screen.h"
#include "Player.h"
#include "AssetManager.h"

class Game;
class Platform;
class Grenade;

class LevelScreen :
	public Screen
{
public:
	LevelScreen(Game* newGamePointer);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

	void Fire(int newPlayer, sf::Vector2f firingVel);

private:
	void Restart();
	bool LoadLevel();

	Player player1;
	Player player2;
	std::vector<Platform*> platforms;

	bool gameRunning;

	sf::RenderWindow* window;
};