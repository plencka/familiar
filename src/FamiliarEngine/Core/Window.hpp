#pragma once
#include <FamiliarEngine/Rendering.hpp>

namespace FamiliarEngine {

	class WindowSettings {
		sf::VideoMode videoMode;
		sf::String title = "";
		sf::Uint32 style = sf::Style::Default; // SFML Window Style
	public:
		WindowSettings() {
			videoMode = sf::VideoMode(200, 200);
		};

		WindowSettings setNativeFullScreen() {
			videoMode = sf::VideoMode::getDesktopMode();
			style = sf::Style::Fullscreen;
			return *this;
		}

		sf::VideoMode getVideoMode() {
			return videoMode;
		};

		sf::String getTitle() {
			return title;
		}

		sf::Uint32 getStyle() {
			return style;
		}
	};

	class IWindowContainer : public sf::RenderWindow {
	private:
		std::map<RenderLayerOrder, std::unique_ptr<RenderLayer>> renderLayers = {};

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
			renderLayers.emplace(order, std::make_unique<RenderLayer>(order));
		}

		IWindowContainer() {
			addLayer(RenderLayerOrder::Default);
		}

		~IWindowContainer() {
			renderLayers.clear();
		}

	public:
		virtual void open() {
			sf::RenderWindow::create(sf::VideoMode(200, 200), "Unconfigured window");
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
