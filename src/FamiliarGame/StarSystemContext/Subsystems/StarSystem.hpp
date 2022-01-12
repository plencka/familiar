#include <FamiliarEngine/Base.hpp>
#include <FamiliarGame/StarSystemContext/Entities/CelestialBodies.hpp>
#include <FamiliarGame/StarSystemContext/Entities/VisualEffects.hpp>
#include <FamiliarGame/StarSystemContext/Components/StarSystemRecipe.hpp>
#include "OrbitablesManager.hpp"

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
	float planetOffset = 90;
	float starOffset = 80;
	float moonOffset = 35;
	sf::Vector2f speedOffset = {1, 3};
	sf::Vector2f cycleOffset = {0, 10000};

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

	template <class CelestialBaseType>
	std::shared_ptr<CelestialBaseType> generateCelestial(int celestialIndex,
		std::shared_ptr<CelestialBase> parent,
		sf::Vector2f visualSize,
		float orbitOffset,
		float speedModifier = 1,
		bool isPrimary = false)
	{
		std::shared_ptr<CelestialBaseType> celestial = std::make_shared<CelestialBaseType>(parent);

		celestial->setScale(Math::Random::getRandom(visualSize.x, visualSize.y));
		celestial->setRandomColor();
		celestial->setOrbitOffset(orbitOffset * celestialIndex);
		celestial->setCycleOffset(orbitOffset * celestialIndex + Math::Random::getRandom(cycleOffset.x, cycleOffset.y));
		celestial->setOrbitSpeed(Math::Random::getRandom(speedOffset.x * speedModifier, speedOffset.y * speedModifier));

		addCelestialBody(celestial, isPrimary);
		return celestial;
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
		std::shared_ptr<Star> starPrime = generateCelestial<Star>(lastCelestialId, nullptr, primaryStarSize, 0, 1, true);

		for (int i = 0; i < recipe.getSecondaryStarCount(); i++) {
			generateCelestial<Star>(lastCelestialId, std::dynamic_pointer_cast<CelestialBase>(starPrime), secondaryStarSize, starOffset, 1);
		}

		for (int i = 0; i < recipe.getPlanetCount(); i++) {
			std::shared_ptr<Planet> planet = generateCelestial<Planet>(lastCelestialId - generatedMoonCount, starPrime, planetSize, planetOffset, 1);
			for (int j = 0; j < Math::Random::getRandom(0, recipe.getMaxMoonCount()); j++) {
				generateCelestial<Moon>(j + 1, std::dynamic_pointer_cast<CelestialBase>(planet), moonSize, moonOffset, 10);
				generatedMoonCount++;
			}
		}
	}
};
