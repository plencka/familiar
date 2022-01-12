#pragma once
#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Components/CelestialBase.hpp>

using namespace FamiliarEngine;

class Star : public CelestialBase {
public:
	Star() {
		if (!texture.loadFromFile("data/textures/celestials/star.png")) {
			return;
		};

		texture.setSmooth(true);
		sprite->setColor(sf::Color::Yellow);
		usesVerticalModifier = false;
		sprite->setTexture(texture);
		setScale(1);
	}

	void setRandomColor() {
		std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Yellow, sf::Color::White, sf::Color::Blue };
		sprite->setColor(colors[rand() % colors.size()]);
	}
};
