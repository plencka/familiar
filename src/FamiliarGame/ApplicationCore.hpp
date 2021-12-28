#pragma once
#include <FamiliarEngine/Base.hpp>
#include "Context/StarSystemContext.hpp"

using namespace FamiliarEngine;

class ApplicationCore : public Core {
private:
	std::shared_ptr<StarSystemContext> starSystem;

private:
	virtual void initialize() override {
		std::cout << "Hello from AppCore\n";
		addContext(starSystem);
		changeCurrentContext(starSystem->getContextId());
	}

public:
	ApplicationCore() 
		: starSystem(std::make_shared<StarSystemContext>(getMainWindow())) {
		initialize();
	}
};
