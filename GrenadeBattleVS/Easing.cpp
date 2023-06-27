#include "Easing.h"

// Practical Task - Easing Function
sf::Vector2f Easing::Linear(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
	return (change / duration) * time + begin;
}

sf::Vector2f Easing::QuadOut(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
	return -(change * (time * time) / (duration * duration)) + ((2.0f * change * time) / duration) + begin;
}