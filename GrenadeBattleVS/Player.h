#pragma once
#include "PhysicsObject.h"

class LevelScreen;
class Grenade;

class Player :
    public PhysicsObject
{
public:
    Player(LevelScreen* newLevel);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void SetP1(bool isP1);
    void SetCanJump(bool newCanJump);

    void Fire(sf::Vector2f firingVel);

    void ClearGrenades();
    std::vector<Grenade*> GetGrenades();

private:
    void UpdateAcceleration() override;
    sf::Vector2f GetPipPosition(float pipTime);

    std::vector<sf::Sprite> pips;
    std::vector<Grenade*> grenades;
    sf::Vector2f aimVel;

    LevelScreen* level;
    bool canJump;
    int grenadeTimer;

    bool p1;
};