#pragma once
#include <SFML/Graphics.hpp>

class IOrbitable {
public:
	virtual sf::Vector2f getOrbitPoint() = 0;
	virtual sf::Vector2f getLastCalculatedPosition() = 0;

	virtual float getOrbitOffset() = 0;
	virtual float getCycleOffset() = 0;
	virtual float getSpeed() = 0;

	virtual void setPosition(float x, float y) = 0;
	virtual void setParent(std::shared_ptr<IOrbitable> parent) = 0;

	virtual float getScale() = 0;
	virtual void setScale(float newScale) = 0;

	virtual float getVerticalModifier() = 0;

protected:
	IOrbitable() {};
};
