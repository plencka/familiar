#pragma once
#include <FamiliarEngine/Base.hpp>
#include "StarSystemContext/StarSystemContext.hpp"

using namespace FamiliarEngine;

class ApplicationCore : public Core {
private:
	std::shared_ptr<StarSystemContext> starSystem;

private:
	virtual void initialize() override {
		addContext(starSystem);
		changeCurrentContext(starSystem->getContextId());
	}

public:
	ApplicationCore() 
		: starSystem(std::make_shared<StarSystemContext>(getMainWindow())) {
		initialize();
	}
};
