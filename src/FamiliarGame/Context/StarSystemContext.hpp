#pragma once
#include <FamiliarEngine/Base.hpp>

using namespace FamiliarEngine;

class Star : public IRenderable {
private:
	std::shared_ptr<sf::CircleShape> shape;

public:
	Star() {
		shape = std::make_shared<sf::CircleShape>(50);
		shape->setOrigin(shape->getRadius(), shape->getRadius());
		shape->setFillColor(sf::Color::Yellow);
	}

	virtual int getVerticalPosition() override {
		return shape->getPosition().y;
	};

	virtual std::shared_ptr<sf::Drawable> getDrawable() {
		return shape;
	};

	virtual RenderLayerOrder getRenderLayerOrder() {
		return RenderLayerOrder::Default;
	};
};

class StarSystemContext : public Context {
private:
	std::shared_ptr<Star> dummyStar;
	std::shared_ptr<RenderView> view;
public:
	StarSystemContext(std::shared_ptr<sf::RenderWindow> window) : 
		Context(Hash::FNV("StarSystemContext")) {
		view = std::make_shared<RenderView>(window);
		addUpdateObject(view);

		dummyStar = std::make_shared<Star>();
		view->handleRenderable(dummyStar, RenderLayerAction::Add);
	};

	~StarSystemContext() {
		std::cout << "Bye bye.\n";
	};

	virtual void enter() override {
		std::cout << "Hello from StarSystemContext.\n";
	}

	virtual void exit() override {
		std::cout << "Goodbye from StarSystemContext.\n";
	}
};
