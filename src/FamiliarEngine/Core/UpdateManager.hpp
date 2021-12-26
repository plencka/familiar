#pragma once
#include "FamiliarEngine/Common.hpp"
#include "Interfaces/IUpdateable.hpp"
#include <vector>

namespace FamiliarEngine {
	class UpdateManager {
	private:
		std::vector<std::weak_ptr<IUpdateable>> updateables{};
		sf::Clock clock;

	protected:
		UpdateManager() {};
	
	public:
		void addUpdateObject(std::shared_ptr<IUpdateable> updateableObject) {
			updateables.push_back(updateableObject);
		}

		void processUpdate() {
			float delta = clock.getElapsedTime().asSeconds();
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

			clock.restart();
		}
	};
}
