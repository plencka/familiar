#pragma once
#include "Common/BasicIncludes.hpp"
#include <set>
#include <SFML/Graphics.hpp>
#include "Rendering/Interfaces/IRenderable.hpp"

namespace FamiliarEngine {
	enum class RenderLayerAction : unsigned int {
		Add = 0,
		Remove = 1,
		Refresh = 2,
	};

	class RenderLayer {
	private:
		std::multimap<int, std::weak_ptr<sf::Drawable>> drawables{};

		void addDrawable(int zPosition, std::shared_ptr<sf::Drawable> drawable) {
			drawables.emplace(zPosition, drawable);
		};

		void removeDrawable(std::shared_ptr<sf::Drawable> drawable) {
			if (!drawable) {
				return;
			}

			for (std::multimap<int, std::weak_ptr<sf::Drawable>>::iterator it = drawables.begin(); it != drawables.end(); it++) {
				if (it->second.lock() == drawable) {
					drawables.erase(it);
					return;
				}
			}
		};

		void refreshDrawable(int zPosition, std::shared_ptr<sf::Drawable> drawable) {
			removeDrawable(drawable);
			addDrawable(zPosition, drawable);
		}

	public:
		void handle(std::shared_ptr<IRenderable> renderable, RenderLayerAction action) {
			switch (action) {
				case RenderLayerAction::Add:
					addDrawable(renderable->getVerticalPosition(), renderable->getDrawable());
					break;
				case RenderLayerAction::Remove:
					removeDrawable(renderable->getDrawable());
					break;
				case RenderLayerAction::Refresh:
					refreshDrawable(renderable->getVerticalPosition(), renderable->getDrawable());
					break;
				default:
					break;
			}
		}

		void draw(std::shared_ptr<sf::RenderWindow> window) {
			for (std::multimap<int, std::weak_ptr<sf::Drawable>>::iterator it = drawables.begin(); it != drawables.end(); it++) {
				if (std::shared_ptr<sf::Drawable> drawable = it->second.lock()) {
					window->draw(*drawable.get());
				}
				else {
					it = drawables.erase(it);
				}
			}
		};
	};
}
