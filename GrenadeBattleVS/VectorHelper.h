#pragma once
#include <SFML/System.hpp>

namespace VectorHelper {
	float Magnitude(sf::Vector2f vec);
	float SquareMagnitude(sf::Vector2f vec);

	sf::Vector2f Normalise(sf::Vector2f vec);

	float Dot(sf::Vector2f a, sf::Vector2f b);
	float Dot(sf::Vector3f a, sf::Vector3f b);

	sf::Vector3f Cross(sf::Vector3f a, sf::Vector3f b);

	sf::Vector2f GetReflection(sf::Vector2f incident, sf::Vector2f normal);
	sf::Vector3f GetReflection(sf::Vector3f incident, sf::Vector3f normal);

	sf::Vector3f GetNormal(sf::Vector3f lineA, sf::Vector3f lineB);
	sf::Vector2f GetNormal(sf::Vector3f line);
}