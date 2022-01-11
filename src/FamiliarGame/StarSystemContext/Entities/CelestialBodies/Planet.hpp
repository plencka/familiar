#pragma once
#include <FamiliarEngine/Base.hpp>
#include "CelestialBase.hpp"

using namespace FamiliarEngine;

class Planet : public CelestialBase {
private:
	std::shared_ptr<sf::Sprite> sprite;
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
		return sprite->getPosition().y;
	};

	virtual std::shared_ptr<sf::Drawable> getDrawable() override {
		return sprite;
	};

	virtual void setPosition(float x, float y) override {
		lastPosition = { x, y };
		sprite->setPosition(x, y);
	}

	virtual void setScale(float newScale) {
		scale = newScale;
		sprite->setScale(scale, scale);
	};
};
