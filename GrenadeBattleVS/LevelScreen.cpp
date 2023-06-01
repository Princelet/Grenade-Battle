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
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	// Practical Task - Collision Geometry
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
				player1.SetCanJump(true);
			}

			if (platforms[i]->CheckCollision(player2))
			{
				player2.SetColliding(true);
				platforms[i]->SetColliding(true);
				player2.HandleCollision(*platforms[i]);
				player2.SetCanJump(true);
			}
		}

		for (size_t i = 0; i < player1.GetGrenades().size(); ++i)
		{
			if (player1.GetGrenades()[i])
			{
				player1.GetGrenades()[i]->Update(frameTime);
				player1.GetGrenades()[i]->SetColliding(false);

				for (size_t j = 0; j < platforms.size(); ++j)
				{
					if (platforms[j]->CheckCollision((*player1.GetGrenades()[i])))
					{
						(*player1.GetGrenades()[i]).SetColliding(true);
						platforms[j]->SetColliding(true);
						(*player1.GetGrenades()[i]).HandleCollision(*platforms[j]);
					}
				}
			}
		}

		for (size_t i = 0; i < player2.GetGrenades().size(); ++i)
		{
			if (player2.GetGrenades()[i])
			{
				player2.GetGrenades()[i]->Update(frameTime);
				player2.GetGrenades()[i]->SetColliding(false);

				for (size_t j = 0; j < platforms.size(); ++j)
				{
					if (platforms[j]->CheckCollision((*player2.GetGrenades()[i])))
					{
						(*player2.GetGrenades()[i]).SetColliding(true);
						platforms[j]->SetColliding(true);
						(*player2.GetGrenades()[i]).HandleCollision(*platforms[j]);
					}
				}
			}
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			Restart();
	}
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
}

void LevelScreen::Restart()
{
	// Delete before clearing!
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	platforms.clear();

	player1.ClearGrenades();
	player2.ClearGrenades();

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
	float x = 500.0f;
	float y = 150.0f;

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
			x = 500.0f;
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