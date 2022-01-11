#pragma once
#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Interfaces/IOrbitable.hpp>

using namespace FamiliarEngine;

class CelestialBase : public IRenderable, public IOrbitable {
protected:
	std::weak_ptr<IOrbitable> parentBody;
	float scale = 1;
	sf::Vector2f orbitPoint = { 0,0 };
	sf::Vector2f lastPosition = { 0,0 };
	float verticalModifier = 0;
	float orbitOffset = 0;
	float cycleOffset = 0;
	float speed = 1;

protected:
	CelestialBase(){}

public:
	virtual sf::Vector2f getOrbitPoint() {
		if (std::shared_ptr<IOrbitable> parent = parentBody.lock()) {
			return parent->getLastCalculatedPosition();
		}
		else {
			return orbitPoint;
		}
	}

	virtual sf::Vector2f getLastCalculatedPosition() override {
		return lastPosition;
	};

	virtual float getOrbitOffset() override {
		return orbitOffset;
	};

	virtual float getCycleOffset() override {
		return cycleOffset;
	};

	virtual float getSpeed() override {
		return speed;
	};

	virtual float getScale() override {
		return scale;
	};

	virtual float getVerticalModifier() override {
		return verticalModifier;
	}

	virtual RenderLayerOrder getRenderLayerOrder() override {
		return RenderLayerOrder::Entity;
	};

	virtual void setParent(std::shared_ptr<IOrbitable> parent) {
		parentBody = parent;
	}
};