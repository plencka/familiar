#pragma once
#include "Common/BasicIncludes.hpp"
#include "Core/Interfaces/IUpdateable.hpp"
#include <vector>

namespace FamiliarEngine {
	class UpdateManager {
	private:
		std::vector<std::weak_ptr<IUpdateable>> updateables{};

	protected:
		UpdateManager() {
		};
	
		void addUpdateObject(std::shared_ptr<IUpdateable> updateableObject) {
			updateables.push_back(updateableObject);
		}

	public:
		void processUpdate(double deltaTime) {
			for (auto it = updateables.begin(); it < updateables.end(); ++it) {
				if (std::shared_ptr<IUpdateable> updateableObject = (*it).lock()) {
					if (updateableObject->shouldUpdate()) {
						updateableObject->update(deltaTime);
					}
				}
				else {
					it = updateables.erase(it);
				}
			}
		}
	};
}
