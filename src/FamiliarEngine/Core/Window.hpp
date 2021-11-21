#pragma once
#include <FamiliarEngine/Rendering.hpp>

namespace FamiliarEngine {

	class WindowSettings {
		sf::VideoMode mode;
		sf::String title = "";

	};

	class IWindowContainer : public sf::RenderWindow {
	private:
		std::map<RenderLayerOrder, RenderLayer*> renderLayers = {};

		void handleEvents() {
			sf::Event sfmlEvent;
			while (pollEvent(sfmlEvent))
			{
				if (sfmlEvent.type == sf::Event::Closed)
					close();
			}
		};

		void renderContent() {
			clear();
			for (auto& renderLayer : renderLayers)
			{
				renderLayer.second->draw(*this);
			}
			display();
		};

	protected:
		void addLayer(RenderLayerOrder order) {
			renderLayers.emplace(order, new RenderLayer(order));
		}

		IWindowContainer() {
			addLayer(RenderLayerOrder::Default);
		}

		~IWindowContainer() {
			for (auto & renderLayer : renderLayers)
			{
				delete renderLayer.second;
			}
			renderLayers.clear();
		}

	public:
		virtual void open() {
			sf::RenderWindow::create(sf::VideoMode(200, 200), "Default window");
		};

		bool update() {
			if (isOpen()) {
				handleEvents();
				renderContent();

				return true;
			}

			return false;
		};
	};
}