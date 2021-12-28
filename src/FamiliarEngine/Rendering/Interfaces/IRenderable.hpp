#pragma once
#include "Common/BasicIncludes.hpp"
#include <SFML/Graphics.hpp>

namespace FamiliarEngine {
	enum class RenderLayerOrder : int {
		Background = -1,
		Terrain = 0,
		Default = 1,
		Entity = 2,
		Player = 3,
		Foreground = 4,
		GUI = 100,
		GUIBackground = GUI + 1,
		GUIBorder = GUI + 2,
		GUIImage = GUI + 3,
		GUIClickable = GUI + 4,
		GUIText = GUI + 5,
	};

	class IRenderable {
	public:
		virtual int getVerticalPosition() = 0;
		virtual std::shared_ptr<sf::Drawable> getDrawable() = 0;
		virtual RenderLayerOrder getRenderLayerOrder() = 0;

	protected:
		IRenderable() {};
	};
}
