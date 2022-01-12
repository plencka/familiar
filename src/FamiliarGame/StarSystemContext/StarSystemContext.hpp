#pragma once
#include <FamiliarEngine/Base.hpp>
#include "Subsystems/StarSystem.hpp"

using namespace FamiliarEngine;


class StarSystemContext : public Context {
private:
	std::weak_ptr<sf::RenderWindow> appWindow;
	std::shared_ptr<RenderView> view;
	std::shared_ptr<StarSystem> starSystem;

public:
	StarSystemContext(std::shared_ptr<sf::RenderWindow> window) : 
		Context(Hash::FNV("StarSystemContext")),
		appWindow(window) {

		view = std::make_shared<RenderView>(window);
		addUpdateObject(view);
	};

	void fill() {
		StarSystemRecipe recipe;
		recipe.randomizeRecipe();
		starSystem->generateFromRecipe(recipe);
	}

	virtual void parseEvents(std::vector<sf::Event> passedEvents) override {
		for (sf::Event& sfmlEvent : passedEvents) {
			if (sfmlEvent.type == sf::Event::KeyPressed) {
				if (sfmlEvent.key.code == sf::Keyboard::Space)
				{
					fill();
				}
			}
		}
	};

	virtual void enter() override {
		starSystem = std::make_shared<StarSystem>(view);
		fill();

		addUpdateObject(starSystem);
	}

	virtual void exit() override {
		starSystem = nullptr;
	}
};
