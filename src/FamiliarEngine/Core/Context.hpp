#pragma once
#include "Core/UpdateManager.hpp"

namespace FamiliarEngine {
	class Context : public UpdateManager {
	private:
		uint32_t id = 0;

	protected:
		Context(uint32_t contextId) : id(contextId){};

	public:
		virtual void enter() = 0;
		virtual void exit() = 0;

		uint32_t getContextId() {
			return id;
		}
	};
}
