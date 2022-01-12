#pragma once
#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Components/OrbitableBase.hpp>

using namespace FamiliarEngine;

class CelestialBase : public OrbitableBase, public IRenderable {
protected:
	sf::Texture texture;
	std::shared_ptr<sf::Sprite> sprite;

	float currentScale = 1;

protected:
	CelestialBase(std::shared_ptr<CelestialBase> parent = nullptr) {
		setParent(std::dynamic_pointer_cast<IOrbitable>(parent));
		sprite = std::make_shared<sf::Sprite>();
	}

public:
	inline virtual RenderLayerOrder getRenderLayerOrder() override {
		return RenderLayerOrder::Entity;
	};

	inline virtual int getVerticalPosition() override {
		if (sprite) {
			return sprite->getPosition().y;
		}
		else {
			return 0;
		}
	};

	inline virtual std::shared_ptr<sf::Drawable> getDrawable() override {
		return sprite;
	};

	inline virtual void setVisualPosition(float x, float y) override {
		lastPosition = { x, y };
		if (sprite) {
			sprite->setPosition(x, y);
		}
	}

	inline virtual float getScale() {
		return currentScale;
	};

	inline virtual void setScale(float newScale) {
		currentScale = newScale;
		if (sprite) {
			sprite->setScale(currentScale, currentScale);
			sprite->setOrigin(sprite->getTextureRect().width / 2.0f,
				sprite->getTextureRect().height / 2.0f);
		}
	};

	virtual void setRandomColor() {
		std::vector<sf::Color> colors = { sf::Color::White};
		sprite->setColor(colors[rand() % colors.size()]);
	}
};
