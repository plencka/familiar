#pragma once
#include <FamiliarEngine/Base.hpp>
#include "FamiliarGame/StarSystemContext/Interfaces/IOrbitable.hpp"

using namespace FamiliarEngine;

constexpr float deltaStepModifier = 100.0f;

class OrbitablesManager : public IUpdateable {
private:
	double timestamp = 0;
	std::vector<std::weak_ptr<IOrbitable>> orbitables;

public:
	inline void resetTimestamp() {
		timestamp = 0;
	}

	inline void addOrbitable(std::shared_ptr<IOrbitable> orbitable) {
		orbitables.push_back(orbitable);
	}

	virtual bool shouldUpdate() override {
		return true;
	}

	void calculateOrbitFor(std::shared_ptr<IOrbitable> orbitable) {
		if (!orbitable) {
			return;
		}

		float calculatedCycleTime = timestamp + orbitable->getCycleOffset();
		float orbitOffset = orbitable->getOrbitOffset();
		float calculatedSpeed = orbitable->getSpeed() * deltaStepModifier;
		sf::Vector2f orbitPoint = orbitable->getOrbitPoint();

		orbitable->setPosition(
			orbitPoint.x + (cos(calculatedSpeed * calculatedCycleTime) * orbitOffset * orbitable->getVerticalModifier()),
			orbitPoint.y + (sin(calculatedSpeed * calculatedCycleTime) * orbitOffset)
		);
	}

	virtual void update(double deltaTime) override {
		timestamp += deltaTime;
		for (auto& orbitable : orbitables){
			calculateOrbitFor(orbitable.lock());
		}
	}
};
