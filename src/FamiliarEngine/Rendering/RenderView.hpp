#pragma once
#include "Common/BasicIncludes.hpp"
#include "Rendering/RenderLayer.hpp"
#include "Core/Interfaces/IUpdateable.hpp"

namespace FamiliarEngine {
	class RenderView : public IUpdateable {
	private:
		std::weak_ptr<sf::RenderWindow> renderWindow;
		std::map<RenderLayerOrder, std::unique_ptr<RenderLayer>> renderLayers = {};

	protected:
		inline void addLayer(RenderLayerOrder order, sf::Vector2f viewAnchor = { 0,0 }) {
			renderLayers.emplace(order, std::make_unique<RenderLayer>(viewAnchor));
		}

		virtual void initializeLayers(std::shared_ptr<sf::RenderWindow> window) {
			addLayer(RenderLayerOrder::Background, window->getDefaultView().getCenter());
			addLayer(RenderLayerOrder::Entity, { 0,0 });
			addLayer(RenderLayerOrder::GUI, window->getDefaultView().getCenter());
		}

	public:
		RenderView(std::shared_ptr<sf::RenderWindow> window)
			: renderWindow(window) {
			initializeLayers(window);
		}

		void adjustLayers(std::shared_ptr<sf::RenderWindow> window){
			renderLayers[RenderLayerOrder::Background]->setAnchor(window->getDefaultView().getCenter());
			renderLayers[RenderLayerOrder::GUI]->setAnchor(window->getDefaultView().getCenter());
		}

		void handleRenderable(std::shared_ptr<IRenderable> renderable, RenderLayerAction action) {
			RenderLayerOrder order = renderable->getRenderLayerOrder();
			std::map<RenderLayerOrder, std::unique_ptr<RenderLayer>>::iterator it = renderLayers.find(order);
			if (it != renderLayers.end()) {
				it->second->handle(renderable, action);
			}
		}

		std::shared_ptr<sf::RenderWindow> getWindow() {
			return renderWindow.lock();
		}

		float getAspectRatio() {
			if (std::shared_ptr<sf::RenderWindow> window = renderWindow.lock()) {
				sf::Vector2f size = window->getView().getSize();
				return size.x / size.y;
			}
			else {
				return 1;
			}
		}

		virtual bool shouldUpdate() override {
			return true;
		}

		virtual void update(double deltaTime) override {
			if (std::shared_ptr<sf::RenderWindow> window = renderWindow.lock()) {
				window->clear();
				for (auto& renderLayer : renderLayers)
				{
					renderLayer.second->draw(window);
				}
				window->display();
			}
		};
	};
}
