#pragma once
#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Entities/CelestialBodies.hpp>
#include <FamiliarGame/StarSystemContext/Entities/VisualEffects.hpp>
#include "OrbitablesManager.hpp"

using namespace FamiliarEngine;


class StarSystemContext : public Context {
private:
	std::weak_ptr<sf::RenderWindow> appWindow;
	std::shared_ptr<Skybox> skybox;
	std::shared_ptr<Star> dummyStar;
	std::shared_ptr<Planet> dummyPlanet;
	std::shared_ptr<Planet> dummyMoon;
	std::shared_ptr<RenderView> view;
	std::shared_ptr<OrbitablesManager> orbitableManager;
public:
	StarSystemContext(std::shared_ptr<sf::RenderWindow> window) : 
		Context(Hash::FNV("StarSystemContext")),
		appWindow(window) {

		view = std::make_shared<RenderView>(window);
		addUpdateObject(view);

		dummyStar = std::make_shared<Star>();
		view->handleRenderable(dummyStar, RenderLayerAction::Add);

		dummyPlanet = std::make_shared<Planet>(200, 2);
		view->handleRenderable(dummyPlanet, RenderLayerAction::Add);
		dummyPlanet->setParent(dummyStar);

		dummyMoon = std::make_shared<Planet>(50, 1);
		dummyMoon->setScale(0.4f);
		view->handleRenderable(dummyMoon, RenderLayerAction::Add);
		dummyMoon->setParent(dummyPlanet);

		orbitableManager = std::make_shared<OrbitablesManager>();
		orbitableManager->addOrbitable(dummyStar);
		orbitableManager->addOrbitable(dummyPlanet);
		orbitableManager->addOrbitable(dummyMoon);

		skybox = std::make_shared<Skybox>(window);
		view->handleRenderable(skybox, RenderLayerAction::Add);
		addUpdateObject(orbitableManager);
	};

	virtual void enter() override {
		orbitableManager->resetTimestamp();
	}

	virtual void exit() override {
	}
};
