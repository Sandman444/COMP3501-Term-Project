#include "laser.h"

namespace game {

	Laser::Laser(glm::vec3 forward, const std::string name, const Resource *geometry, const Resource *material) : SceneNode(name, geometry, material) {
		forward_ = forward;
	}


	Laser::~Laser() {
	}

	void Laser::Update(void) {
		this->Translate(forward_);
	}

} // namespace game
