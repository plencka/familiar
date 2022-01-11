#pragma once
#include <FamiliarEngine/Base.hpp>

using namespace FamiliarEngine;

class Skybox : public IRenderable {
protected:
	std::weak_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::RectangleShape> shape;
	sf::Texture texture;

public:
	void adjust() {
		if (std::shared_ptr<sf::RenderWindow> renderWindow = window.lock()) {
			auto& view = renderWindow->getView();
			float width = view.getSize().x;
			float height = view.getSize().y;
			float squareSize = (width > height) ? width : height;
			shape->setSize({ squareSize, squareSize });
		}
	}

	Skybox(std::shared_ptr<sf::RenderWindow> renderWindow) : window(renderWindow) {
		shape = std::make_shared<sf::RectangleShape>();
		if (texture.loadFromFile("data/textures/stars.jpg")) {
			texture.setSmooth(true);
			texture.setRepeated(true);
			shape->setTexture(&texture);
			adjust();
		}
	}

	virtual int getVerticalPosition() override {
		return 0;
	}

	virtual std::shared_ptr<sf::Drawable> getDrawable() override {
		return shape;
	};

	virtual RenderLayerOrder getRenderLayerOrder() override {
		return RenderLayerOrder::Background;
	};
};
