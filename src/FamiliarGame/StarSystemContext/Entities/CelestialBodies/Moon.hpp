#pragma once
#include "Planet.hpp"

using namespace FamiliarEngine;

class Moon : public Planet {
public:
	Moon(std::shared_ptr<Planet> parent) : Planet() {
		setParent(parent);
		usesVerticalModifier = false;
	}
};
