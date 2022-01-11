#pragma once
#include <FamiliarEngine/Base.hpp>
#include "CelestialBase.hpp"

using namespace FamiliarEngine;

class Planet : public CelestialBase {
private:
	sf::Texture texture;
	sf::RectangleShape shape;
public:
	Planet(float startOffset, float axisMod) {
		sprite = std::make_shared<sf::Sprite>();
		sprite->setScale(getScale(), getScale());

		if (!texture.loadFromFile("data/textures/celestials/planet.png")) {
			return;
		};

		sprite->setTexture(texture);
		sprite->setOrigin(sprite->getTextureRect().width / 2.0f,
			sprite->getTextureRect().height / 2.0f);

		orbitOffset = startOffset;
		verticalModifier = axisMod;
	}

	virtual int getVerticalPosition() override {
		if (sprite) {
			return sprite->getPosition().y;
		}
		else {
			return 0;
		}
	};

	virtual std::shared_ptr<sf::Drawable> getDrawable() override {
		return sprite;
	};
};
