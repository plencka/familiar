#pragma once
#include <set>
#include <SFML/Graphics.hpp>

namespace FamiliarEngine {
	enum class RenderLayerOrder : int {
		Background = -1,
		Terrain = 0,
		Default = 1,
		Entity = 2,
		Player = 3,
		Foreground = 4,
		GUI = 100,
		GUIBackground = GUI + 1,
		GUIBorder = GUI + 2,
		GUIImage = GUI + 3,
		GUIClickable = GUI + 4,
		GUIText = GUI + 5,
	};

	class RenderLayer {
	private:
		RenderLayerOrder renderOrder;
		std::multimap<int, sf::Drawable*> drawables;

	public:
		RenderLayer(RenderLayerOrder order){
			drawables = {};
			renderOrder = order;
		}

		RenderLayerOrder getRenderOrder() {
			return renderOrder;
		};

		void addDrawable(int zPosition, sf::Drawable* drawable) {
			drawables.emplace(zPosition, drawable);
		};

		void removeDrawable(sf::Drawable* drawable) {
			for (std::multimap<int, sf::Drawable*>::iterator it = drawables.begin(); it != drawables.end(); it++) {
				if (it->second == drawable) {
					drawables.erase(it);
					return;
				}
			}
		};

		void refreshDrawable(int zPosition, sf::Drawable* drawable) {
			removeDrawable(drawable);
			addDrawable(zPosition, drawable);
		}

		void draw(sf::RenderWindow& window) {
			for (auto const& drawable : drawables)
			{
				window.draw(*drawable.second);
			}
		};
	};
}
