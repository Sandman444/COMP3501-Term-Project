#include <stdexcept>
#include <iostream>

#include "Missile.h"

namespace game {

	Missile::Missile(std::string material, glm::vec3 position, glm::vec3 forward) : Projectile(position, forward) {
		projectileModel = new SceneNode(GetName() + "Model", "CubeMesh", material, "");
		projectileModel->SetScale(glm::vec3(0.3, 0.1, 0.1));
		this->addChild(projectileModel);
	}


	Missile::~Missile() {
	}

} // namespace game