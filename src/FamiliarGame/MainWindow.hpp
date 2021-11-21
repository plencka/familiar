#pragma once
#include <FamiliarEngine/Base.hpp>

class MainWindow : public FamiliarEngine::IWindowContainer {
public:
	MainWindow() : FamiliarEngine::IWindowContainer(){};

	virtual void open() override {
		FamiliarEngine::WindowSettings windowSettings = FamiliarEngine::WindowSettings().setNativeFullScreen();
		sf::RenderWindow::create(windowSettings.getVideoMode(), windowSettings.getTitle(), windowSettings.getStyle());
	};
};
