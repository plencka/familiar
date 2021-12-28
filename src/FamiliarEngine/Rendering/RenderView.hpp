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
		inline void addLayer(RenderLayerOrder order) {
			renderLayers.emplace(order, std::make_unique<RenderLayer>());
		}

		virtual void initializeLayers() {
			addLayer(RenderLayerOrder::Default);
		}

	public:
		RenderView(std::shared_ptr<sf::RenderWindow> window)
			: renderWindow(window) {
			initializeLayers();
		}

		void handleRenderable(std::shared_ptr<IRenderable> renderable, RenderLayerAction action) {
			RenderLayerOrder order = renderable->getRenderLayerOrder();
			std::map<RenderLayerOrder, std::unique_ptr<RenderLayer>>::iterator it = renderLayers.find(order);
			if (it != renderLayers.end()) {
				it->second->handle(renderable, action);
			}
		}

		virtual bool shouldUpdate() override {
			return true;
		}

		virtual void update(float deltaTime) override {
			if (std::shared_ptr<sf::RenderWindow> window = renderWindow.lock()) {
				window->setView(sf::View(sf::Vector2f(0, 0), window->getView().getSize()));
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
