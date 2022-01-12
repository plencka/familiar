#pragma once
#include <SFML/Graphics.hpp>

class IOrbitable {
public:
	virtual void setParent(std::shared_ptr<IOrbitable> parent) = 0;
	virtual std::shared_ptr<IOrbitable> getParent() = 0;

	virtual sf::Vector2f getOrbitPoint() = 0;
	virtual sf::Vector2f getLastCalculatedPosition() = 0;

	virtual float getOrbitOffset() = 0;
	virtual void setOrbitOffset(float offset) = 0;

	virtual float getCycleOffset() = 0;
	virtual void setCycleOffset(float offset) = 0;

	virtual float getOrbitSpeed() = 0;
	virtual void setOrbitSpeed(float speed) = 0;

	virtual bool requiresVerticalModifier() = 0;

	virtual void setVisualPosition(float x, float y) = 0;

protected:
	IOrbitable() {};
};
