#pragma once
#include <FamiliarEngine/Base.hpp>
#include "CelestialBase.hpp"

using namespace FamiliarEngine;

class Star : public CelestialBase {
private:
	std::shared_ptr<sf::Sprite> sprite;
	sf::Texture texture;

public:
	Star() {
		sprite = std::make_shared<sf::Sprite>();
		sprite->setColor(sf::Color::Yellow);
		scale = 2;
		sprite->setScale(scale, scale);

		if (!texture.loadFromFile("data/textures/celestials/star.png")) {
			return;
		};
		texture.setSmooth(true);
		sprite->setTexture(texture);
		sprite->setOrigin(sprite->getTextureRect().width / 2.0f,
			sprite->getTextureRect().height / 2.0f);
	}

	virtual int getVerticalPosition() override {
		return sprite->getPosition().y;
	};

	virtual std::shared_ptr<sf::Drawable> getDrawable() override {
		return sprite;
	};
};
