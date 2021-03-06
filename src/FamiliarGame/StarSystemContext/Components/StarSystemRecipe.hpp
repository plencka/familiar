#pragma once
#include <FamiliarEngine/Base.hpp>
#include <chrono>

constexpr int maxSecondaryStarCount = 2;
constexpr int minPlanetCount = 1;
constexpr int maxPlanetCount = 6;
constexpr int maxMoonCount = 2;

class StarSystemRecipe : public FamiliarEngine::ISerializable {
	uint32_t seed = 0;
	unsigned int countSecondaryStars = 0;
    unsigned int countPlanets = 0;

public:
    uint32_t getSeed() {
        return seed;
    }

    unsigned int getPlanetCount() {
        return countPlanets;
    }

    unsigned int getSecondaryStarCount() {
        return countSecondaryStars;
    }

    unsigned int getMaxMoonCount() {
        return maxMoonCount;
    }

    void randomizeRecipe() {
        setTimestampSeed();
        
        srand(seed);
        countSecondaryStars = Math::Random::getRandom(0, maxSecondaryStarCount);
        countPlanets = Math::Random::getRandom(minPlanetCount, maxPlanetCount);
    }

	void setTimestampSeed() {
        long long timestamp = std::chrono::microseconds(std::time(NULL)).count();
        seed = (uint32_t)timestamp;
	}

    virtual void serialize(SerializablePackage& package) override
    {
        package.insert(&seed, "seed");
    }

    virtual void deserialize(SerializablePackage& package) override
    {
        package.retrieve(&seed, "seed");
    }

    virtual std::string getFilename() override
    {
        return std::to_string(seed) + ".seed.pbin";
    }

    virtual std::string getPath() override
    {
        return "/savedSeeds/";
    }
};
