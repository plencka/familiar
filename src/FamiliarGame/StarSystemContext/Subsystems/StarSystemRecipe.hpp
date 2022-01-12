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
        countSecondaryStars = rand() % maxSecondaryStarCount + 1;
        countPlanets = rand() % maxPlanetCount + minPlanetCount;
    }

	void setTimestampSeed() {
        long long timestamp = std::chrono::microseconds(std::time(NULL)).count();
        seed = (uint32_t)timestamp;
	}

    virtual void serialize(SerializablePackage& package) override
    {
        package.insert(&seed, "seed");
        package.insert(&countSecondaryStars, "secondaryStarCount");
        package.insert(&countPlanets, "countPlanets");
    }

    virtual void deserialize(SerializablePackage& package) override
    {
        package.retrieve(&seed, "seed");
        package.retrieve(&countSecondaryStars, "secondaryStarCount");
        package.retrieve(&countPlanets, "countPlanets");
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
