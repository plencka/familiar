#pragma once
#include <SFML/Graphics.hpp>

namespace FamiliarEngine {
	namespace Hash {
		constexpr uint32_t FNV(const char* textToHash) {
			uint32_t hash = 0x811c9dc5;
			const char* pData = &textToHash[0];
			while (*pData != '\0') {
				uint8_t data = *pData;
				hash = hash * 0x01000193;
				hash = hash ^ data;
				*++pData;
			}

			return hash;
		}
	}
}