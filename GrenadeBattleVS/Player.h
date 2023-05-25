#pragma once
#include "PhysicsObject.h"

class LevelScreen;

class Player :
    public PhysicsObject
{
public:
    Player(LevelScreen* newLevel);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void SetP1(bool isP1);

private:
    void UpdateAcceleration();
    sf::Vector2f GetPipPosition(float pipTime);
    std::vector<sf::Sprite> pips;
    LevelScreen* level;

    bool p1;
};