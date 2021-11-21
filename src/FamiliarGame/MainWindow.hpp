#pragma once
#include <FamiliarEngine/Base.hpp>

class MainWindow : public FamiliarEngine::IWindowContainer {
public:
	MainWindow() : FamiliarEngine::IWindowContainer(){};

	virtual void open() override {
		sf::RenderWindow::create(sf::VideoMode(200, 200), "MainWindow");
	};
};