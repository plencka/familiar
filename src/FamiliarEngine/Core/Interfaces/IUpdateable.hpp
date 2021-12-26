#pragma once

namespace FamiliarEngine {
	class IUpdateable {
	public:
		virtual bool shouldUpdate() = 0;
		virtual void update(float deltaTime) = 0;
	protected:
		IUpdateable() {};
	};
}
