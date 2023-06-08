#pragma once
#include <vector>
#include "Screen.h"
#include "Player.h"
#include "AssetManager.h"
#include "EndPanel.h"

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

private:
	void NewRound(bool p1Win);
	void Restart();
	bool LoadLevel();
	void GameOver(bool p1Win);

	Player player1;
	Player player2;
	std::vector<Platform*> platforms;

	int p1Lives;
	int p2Lives;
	sf::Text p1Text;
	sf::Text p2Text;
	EndPanel endPanel;

	bool gameRunning;

	sf::RenderWindow* window;
};