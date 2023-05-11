#pragma once
#include "PhysicsObject.h"

class Player :
    public PhysicsObject
{
public:
    Player();

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

private:
    sf::Vector2f GetPipPosition(float pipTime);
    std::vector<sf::Sprite> pips;
};