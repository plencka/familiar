#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Entities/CelestialBodies.hpp>
#include <FamiliarGame/StarSystemContext/Entities/VisualEffects.hpp>
#include "OrbitablesManager.hpp"
#include "StarSystemRecipe.hpp"

using namespace FamiliarEngine;

class StarSystem : public OrbitablesManager {
private:
	uint32_t lastCelestialId = 0;
	std::weak_ptr<RenderView> renderView;

	std::shared_ptr<Skybox> skybox;
	std::map<uint32_t, std::shared_ptr<CelestialBase>> celestialBodies;
	std::weak_ptr<Star> primaryStar;

	sf::Vector2f primaryStarSize = { 2.0f, 3.0f };
	sf::Vector2f secondaryStarSize = { 1.0f, 1.5f };
	sf::Vector2f planetSize = { 0.9f, 2.0f };
	sf::Vector2f moonSize = { 0.3f, 0.5f };

	unsigned int generatedMoonCount = 0;
	float planetOffset = 80;
	float starOffset = 80;
	float moonOffset = 35;

	void addCelestialBody(std::shared_ptr<CelestialBase> body, bool isPrimary = false) {
		celestialBodies.emplace(lastCelestialId++, body);

		if (isPrimary) {
			primaryStar = std::dynamic_pointer_cast<Star>(body);
		}

		addOrbitable(body);

		if (std::shared_ptr<RenderView> view = renderView.lock()) {
			view->handleRenderable(body, RenderLayerAction::Add);
		}
	}

	std::shared_ptr<Star> generatePrimaryStar() {
		std::shared_ptr<Star> starPrime = std::make_shared<Star>();
		starPrime->setScale(Math::Random::getRandom(primaryStarSize.x, primaryStarSize.y));
		starPrime->setRandomColor();
		primaryStar = starPrime;
		addCelestialBody(starPrime, true);

		return starPrime;
	}

	std::shared_ptr<Star> generateSecondaryStar() {
		std::shared_ptr<Star> star = std::make_shared<Star>();
		star->setScale(Math::Random::getRandom(secondaryStarSize.x, secondaryStarSize.y));
		star->setRandomColor();
		star->setOrbitOffset(starOffset * lastCelestialId);
		star->setCycleOffset(starOffset * lastCelestialId + Math::Random::getRandom(0.0f, 10000.0f));
		star->setOrbitSpeed(Math::Random::getRandom(1.0f, 1.0f));
		addCelestialBody(star);

		return star;
	}

	std::shared_ptr<Planet> generatePlanet() {
		std::shared_ptr<Planet> planet = std::make_shared<Planet>();
		planet->setScale(Math::Random::getRandom(planetSize.x, planetSize.y));
		planet->setRandomColor();
		planet->setOrbitOffset(planetOffset * (lastCelestialId - generatedMoonCount));
		planet->setCycleOffset(planetOffset * (lastCelestialId - generatedMoonCount) + Math::Random::getRandom(0.0f, 10000.0f));
		planet->setOrbitSpeed(Math::Random::getRandom(1.0f, 3.0f));
		addCelestialBody(planet);

		return planet;
	}

	std::shared_ptr<Moon> generateMoon(std::shared_ptr<Planet> parentPlanet, int moonIndex) {
		std::shared_ptr<Moon> moon = std::make_shared<Moon>(parentPlanet);
		moon->setScale(Math::Random::getRandom(moonSize.x, moonSize.y));
		moon->setOrbitOffset(moonOffset * moonIndex);
		moon->setCycleOffset(moonOffset * moonIndex + Math::Random::getRandom(0.0f, 10000.0f));
		moon->setOrbitSpeed(Math::Random::getRandom(10.0f, 20.0f));
		addCelestialBody(moon);
		generatedMoonCount++;

		return moon;
	}

public:
	StarSystem(std::shared_ptr<RenderView> view) :
		renderView(view),
		OrbitablesManager(view->getAspectRatio()) {
		skybox = std::make_shared<Skybox>(view->getWindow());
		view->handleRenderable(skybox, RenderLayerAction::Add);
	};

	std::map<uint32_t, std::shared_ptr<CelestialBase>> getOrbitingBodies() {
		return celestialBodies;
	}

	void discardOrbitingBodies() {
		discardOrbitables();
		celestialBodies.clear();
		lastCelestialId = 0;
		generatedMoonCount = 0;
	}

	void generateFromRecipe(StarSystemRecipe& recipe) {
		discardOrbitingBodies();
		uint32_t seed = recipe.getSeed();
		srand(seed);
		std::shared_ptr<Star> starPrime = generatePrimaryStar();

		for (int i = 0; i < recipe.getSecondaryStarCount(); i++) {
			generateSecondaryStar();
		}

		for (int i = 0; i < recipe.getPlanetCount(); i++) {
			std::shared_ptr<Planet> planet = generatePlanet();
			for (int j = 0; j < Math::Random::getRandom(0, recipe.getMaxMoonCount()); j++) {
				generateMoon(planet, j+1);
			}
		}
	}
};
