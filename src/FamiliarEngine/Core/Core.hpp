#pragma once
#include "Common/BasicIncludes.hpp"
#include "Core/Interfaces/IUpdateable.hpp"
#include "Core/ContextManager.hpp"
#include "Config/WindowSettings.hpp"
#include <SFML/Graphics.hpp>
#include <map>

namespace FamiliarEngine {
	enum CoreState : int {
		Unknown = -2,
		NoInit = -1,
		Quit = 0,
		OK = 1,
	};

	class Core : public ContextManager {
	private:
		WindowSettings windowSettings;
		sf::Clock clock;
		CoreState state = CoreState::NoInit;
		std::shared_ptr<sf::RenderWindow> window;

	protected:
		virtual void initialize() = 0;

		Core() 
			: window(std::make_shared<sf::RenderWindow>()) {
			windowSettings = FamiliarEngine::WindowSettings().setNativeFullScreen();
			window->create(windowSettings.getVideoMode(), windowSettings.getTitle(), windowSettings.getStyle());
			window->setVerticalSyncEnabled(true);
			clock.restart();
			state = CoreState::OK;
		}

	public:
		void quit() {
			currentContext->exit();
			window->clear(sf::Color::Black);
			currentContext = nullptr;
			window->close();

			state = CoreState::Quit;
		}

		double getDeltaFrame() {
			float delta = clock.getElapsedTime().asMilliseconds() / 1000.0;

			return (delta < 0.00001) ? 0.00001 : delta;
		}

		void handleEvents() {
			double delta = getDeltaFrame();

			sf::Event sfmlEvent;
			while (window->pollEvent(sfmlEvent))
			{
				if (sfmlEvent.type == sf::Event::Closed) {
					quit();
				}
			};

			if (currentContext) {
				currentContext->processUpdate(delta);
			}

			clock.restart();
		};

		CoreState getState() {
			return state;
		}

		std::shared_ptr<sf::RenderWindow> getMainWindow() {
			return window;
		}
	};
}
