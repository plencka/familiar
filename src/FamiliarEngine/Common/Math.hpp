#pragma once
#include "Common/BasicIncludes.hpp"
#include <random>

namespace FamiliarEngine {
	namespace Math {
		namespace Random {
			float getRandom(float min, float max) {
				return float(min + float(rand()) / (float(RAND_MAX / (max - min))));
			}

			int getRandom(int min, int max) {
				return min + (rand() % int(max - min + 1));
			}
		}
	}
}
