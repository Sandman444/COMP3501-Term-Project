#include "vehicle.h"

namespace game {

	Vehicle::Vehicle(const std::string name, const Resource *geometry, const Resource *material) : SceneNode(name, geometry, material) {
	}

	Vehicle::~Vehicle() {
	}

	void Vehicle::Update(void) {

	}

} // namespace game

