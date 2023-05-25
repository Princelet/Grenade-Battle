#include <fstream>
#include <iostream>
#include "LevelScreen.h"
#include "Game.h"
#include "Platform.h"
#include "Grenade.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player1(this)
	, player2(this)
	, gameRunning(true)
	, window(newGamePointer->GetWindow())
	, grenadeTimer(0)
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player1.Update(frameTime);
		player1.SetColliding(false);
		player2.Update(frameTime);
		player2.SetColliding(false);

		for (size_t i = 0; i < platforms.size(); ++i)
		{
			platforms[i]->Update(frameTime);
			platforms[i]->SetColliding(false);

			if (platforms[i]->CheckCollision(player1))
			{
				player1.SetColliding(true);
				platforms[i]->SetColliding(true);
				player1.HandleCollision(*platforms[i]);
			}

			if (platforms[i]->CheckCollision(player2))
			{
				player2.SetColliding(true);
				platforms[i]->SetColliding(true);
				player2.HandleCollision(*platforms[i]);
			}
		}

		for (size_t i = 0; i < grenades.size(); ++i)
		{
			grenades[i]->Update(frameTime);
			grenades[i]->SetColliding(false);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			Restart();
	}

	if (grenadeTimer > 0)
		--grenadeTimer;
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	player1.Draw(target);
	player2.Draw(target);
	// Draw objects
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}
	for (size_t i = 0; i < grenades.size(); ++i)
	{
		grenades[i]->Draw(target);
	}
}

void LevelScreen::Fire(int newPlayer)
{
	if (grenadeTimer == 0)
	{
		grenades.push_back(new Grenade);

		if (newPlayer == 1)
		{
			grenades[grenades.size() - 1]->SetPosition(player1.GetPosition());
		}
		grenadeTimer = 100;
	}
}

void LevelScreen::Restart()
{
	// Delete before clearing!
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	for (size_t i = 0; i < grenades.size(); ++i)
	{
		delete grenades[i];
		grenades[i] = nullptr;
	}

	platforms.clear();
	grenades.clear();

	player1.SetP1(true);
	player2.SetP1(false);

	gameRunning = true;

	LoadLevel();
}

bool LevelScreen::LoadLevel()
{
	// Open the level file
	std::ifstream inFile;
	std::string filePath = "Grenade Battle Assets/Level.txt";

	inFile.open(filePath);


	// Make sure the file was actually opened
	if (!inFile)
	{
		// File was not opened
		return false;
	}

	// Delete before clearing!
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}

	platforms.clear();


	// Set the starting x and y coordinates used to position our level objects
	float x = 0.0f;
	float y = 0.0f;

	// Define the spacing we will use for our grid
	const float X_SPACE = 45.0f;
	const float Y_SPACE = 45.0f;


	// Read each character one by one...
	char ch;

	// Each time, try to read the next character
	// If successful, execute the body of the loop

	// The "noskipws" means we include white space (spaces/newlines)
	while (inFile >> std::noskipws >> ch)
	{
		// Perform action based on what was read in
		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0.0f;
		}
		else if (ch == '1')
		{
			player1.SetPosition(x, y);
		}
		else if (ch == '2')
		{
			player2.SetPosition(x, y);
		}
		else if (ch == 'P')
		{
			platforms.push_back(new Platform(sf::Vector2f(x, y)));
		}
		else if (ch == '-')
		{
			// Do nothing - empty space
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}
	}

	// Close the file since we're done
	inFile.close();

	// Set game to start
	gameRunning = true;

	// Return true since we successfully loaded the file
	return true;
}