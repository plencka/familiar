#pragma once
#include "Common/BasicIncludes.hpp"

namespace FamiliarEngine {
	constexpr uint32_t hash32BitOffset = 0x811c9dc5;
	constexpr uint32_t hash32BitPrime = 0x01000193;

	namespace Hash {
		constexpr uint32_t FNV(const char* textToHash) {
			uint32_t hash = hash32BitOffset;
			const char* pData = &textToHash[0];
			while (*pData != '\0') {
				uint8_t data = *pData;
				hash = hash * hash32BitPrime;
				hash = hash ^ data;
				*++pData;
			}

			return hash;
		}
	}
}
