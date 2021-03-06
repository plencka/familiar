#pragma once
#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Components/CelestialBase.hpp>

using namespace FamiliarEngine;

class Planet : public CelestialBase {
public:
	Planet(std::shared_ptr<CelestialBase> parent) : CelestialBase(parent) {
		if (!texture.loadFromFile("data/textures/celestials/planet.png")) {
			return;
		};

		sprite->setTexture(texture);
		usesVerticalModifier = true;
		setScale(1);
	}

	virtual void setRandomColor() override {
		std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Yellow, sf::Color::White, sf::Color::Blue,
		sf::Color::Green, sf::Color::Cyan};
		sprite->setColor(colors[rand() % colors.size()]);
	}
};
