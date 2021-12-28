#pragma once
#include "Common/BasicIncludes.hpp"
#include <SFML/Graphics.hpp>

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
}
