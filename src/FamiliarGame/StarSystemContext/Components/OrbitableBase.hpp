#pragma once
#include <FamiliarEngine/Base.hpp>
#include "Interfaces/IOrbitable.hpp"

class OrbitableBase : public IOrbitable {
protected:
	std::weak_ptr<IOrbitable> parentBody;

	bool usesVerticalModifier = false;
	sf::Vector2f orbitPoint = { 0,0 };
	sf::Vector2f lastPosition = { 0,0 };
	float orbitOffset = 0;
	float cycleOffset = 0;
	float orbitSpeed = 1;

public:
	virtual sf::Vector2f getOrbitPoint() override {
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

	virtual bool requiresVerticalModifier() override {
		return usesVerticalModifier;
	}

	virtual float getOrbitOffset() override {
		return orbitOffset;
	}

	virtual void setOrbitOffset(float offset) override {
		orbitOffset = offset;
	}

	virtual float getCycleOffset() override {
		return cycleOffset;
	}

	virtual void setCycleOffset(float offset) override {
		cycleOffset = offset;
	}

	virtual float getOrbitSpeed() override {
		return orbitSpeed;
	};

	virtual void setOrbitSpeed(float speed) override {
		orbitSpeed = speed;
	}

	virtual std::shared_ptr<IOrbitable> getParent() override {
		return parentBody.lock();
	};

	virtual void setParent(std::shared_ptr<IOrbitable> parent) override {
		parentBody = parent;
	};

protected:
	OrbitableBase() {};
};
