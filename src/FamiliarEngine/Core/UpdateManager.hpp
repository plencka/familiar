#pragma once
#include "Common/BasicIncludes.hpp"
#include "Core/Interfaces/IUpdateable.hpp"
#include <vector>

namespace FamiliarEngine {
	class UpdateManager : public sf::Clock {
	private:
		std::vector<std::weak_ptr<IUpdateable>> updateables{};

	protected:
		UpdateManager() {
			restart();
		};
	
		void addUpdateObject(std::shared_ptr<IUpdateable> updateableObject) {
			updateables.push_back(updateableObject);
		}

	public:
		void processUpdate() {
			float delta = getElapsedTime().asSeconds();
			for (auto it = updateables.begin(); it < updateables.end(); ++it) {
				if (std::shared_ptr<IUpdateable> updateableObject = (*it).lock()) {
					if (updateableObject->shouldUpdate()) {
						updateableObject->update(delta);
					}
				}
				else {
					it = updateables.erase(it);
				}
			}

			restart();
		}
	};
}
