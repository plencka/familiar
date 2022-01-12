#pragma once
#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Components/Interfaces/IOrbitable.hpp>

using namespace FamiliarEngine;

constexpr float deltaStepModifier = 10000.0f;

class OrbitablesManager : public IUpdateable {
private:
	double timestamp = 0;
	float verticalModifier = 1;
	std::vector<std::weak_ptr<IOrbitable>> orbitables;

public:
	OrbitablesManager(float verticalOrbitModifier = 1) {
		verticalModifier = verticalOrbitModifier;
	}

	inline void resetTimestamp() {
		timestamp = 0;
	}

	inline void addOrbitable(std::shared_ptr<IOrbitable> orbitable) {
		orbitables.push_back(orbitable);
	}

	inline void discardOrbitables() {
		orbitables.clear();
	}

	virtual bool shouldUpdate() override {
		return true;
	}

	inline void moveOrbitOf(std::shared_ptr<IOrbitable> orbitable, double deltaTime) {
		if (!orbitable) {
			return;
		}

		float calculatedCycleTime = timestamp + orbitable->getCycleOffset();
		float orbitOffset = orbitable->getOrbitOffset();
		float calculatedSpeed = orbitable->getOrbitSpeed() * deltaStepModifier * (float)deltaTime;
		sf::Vector2f orbitPoint = orbitable->getOrbitPoint();

		float verticalOrbitModifier = orbitable->requiresVerticalModifier() ? verticalModifier : 1;

		orbitable->setVisualPosition(
			orbitPoint.x + (cos(calculatedSpeed * calculatedCycleTime) * orbitOffset * verticalOrbitModifier),
			orbitPoint.y + (sin(calculatedSpeed * calculatedCycleTime) * orbitOffset)
		);
	}

	virtual void update(double deltaTime) override {
		timestamp += deltaTime;

		for (auto& orbitable : orbitables){
			moveOrbitOf(orbitable.lock(), deltaTime);
		}
	}
};
