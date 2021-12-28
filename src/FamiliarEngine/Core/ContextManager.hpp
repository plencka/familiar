#pragma once
#include "Common/BasicIncludes.hpp"
#include "Core/Context.hpp"

namespace FamiliarEngine {
	class ContextManager {
	protected:
		std::shared_ptr<Context> currentContext;
		std::map<uint32_t, std::weak_ptr<Context>> contextMap;

	public:
		void addContext(std::shared_ptr<Context> context) {
			contextMap.emplace(context->getContextId(), context);
		}

		std::shared_ptr<Context> getContext(uint32_t contextId) {
			std::map<uint32_t, std::weak_ptr<Context>>::iterator it = contextMap.find(contextId);
			if (it != contextMap.end()) {
				return it->second.lock();
			}
			else {
				throw std::out_of_range("No such context.");
			}
		}

		std::shared_ptr<Context> getCurrentContext() {
			return currentContext;
		}

		void changeCurrentContext(uint32_t contextId) {
			try {
				std::shared_ptr<Context> requestedContext = getContext(contextId);
				if (currentContext) {
					currentContext->exit();
				}

				currentContext = requestedContext;
				currentContext->enter();
			}
			catch (std::out_of_range exception) {
				printf("No context with id 0x%X.", contextId);
			}
		}
	};
}
