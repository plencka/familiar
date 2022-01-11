#pragma once
#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Entities/CelestialBodies.hpp>
#include <FamiliarGame/StarSystemContext/Entities/VisualEffects.hpp>

using namespace FamiliarEngine;

constexpr float slowerStep = 100.0f;

class OrbitMove : public IUpdateable {
private:
	float timestamp = 0;
	std::vector<std::weak_ptr<IOrbitable>> orbitables;

public:
	void addOrbitable(std::shared_ptr<IOrbitable> orbitable) {
		orbitables.push_back(orbitable);
	}

	virtual bool shouldUpdate() override {
		return true;
	}

	virtual void update(double deltaTime) override {
		for (auto& orbitable : orbitables) {
			if (std::shared_ptr<IOrbitable> orbit = orbitable.lock()) {
				timestamp += deltaTime;
				float orbitableOffset = timestamp + orbit->getCycleOffset();
				float offset = orbit->getOrbitOffset();
				float speed = orbit->getSpeed() * (1/orbit->getScale()) * slowerStep;
				sf::Vector2f orbitPoint = orbit->getOrbitPoint();

				orbit->setPosition(
					orbitPoint.x + (cos(speed * orbitableOffset) * offset * orbit->getVerticalModifier()),
					orbitPoint.y + (sin(speed * orbitableOffset) * offset)
				);
			}
		}
	}
};

class StarSystemContext : public Context {
private:
	std::weak_ptr<sf::RenderWindow> appWindow;
	std::shared_ptr<Skybox> skybox;
	std::shared_ptr<Star> dummyStar;
	std::shared_ptr<Planet> dummyPlanet;
	std::shared_ptr<Planet> dummyMoon;
	std::shared_ptr<RenderView> view;
	std::shared_ptr<OrbitMove> move;
public:
	StarSystemContext(std::shared_ptr<sf::RenderWindow> window) : 
		Context(Hash::FNV("StarSystemContext")) {
		appWindow = window;

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

		move = std::make_shared<OrbitMove>();
		move->addOrbitable(dummyStar);
		move->addOrbitable(dummyPlanet);
		move->addOrbitable(dummyMoon);

		skybox = std::make_shared<Skybox>(window);
		view->handleRenderable(skybox, RenderLayerAction::Add);
		addUpdateObject(move);
	};

	~StarSystemContext() {
		std::cout << "Bye bye.\n";
	};

	virtual void enter() override {
		std::cout << "Hello from StarSystemContext.\n";
	}

	virtual void exit() override {
		std::cout << "Goodbye from StarSystemContext.\n";
	}
};
