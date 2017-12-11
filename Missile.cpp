#include <stdexcept>
#include <iostream>

#include "Missile.h"

namespace game {

	Missile::Missile(std::string material, glm::vec3 position, glm::vec3 forward) : Projectile(position, forward) {
		projectileModel = new SceneNode(GetName() + "Model", "CubeMesh", material, "");
		projectileModel->SetScale(glm::vec3(0.3, 0.1, 0.1));
		this->addChild(projectileModel);

		rocketParticles = new SceneNode(GetName() + "RocketParticles", "ConeParticles", "FireMaterial", "Flame");
		rocketParticles->SetBlending(true);
		rocketParticles->Rotate(glm::angleAxis(glm::pi<float>() / 2, glm::vec3(0, -1, 0)));
		rocketParticles->SetScale(glm::vec3(0.8, 0.8, 0.8));
		projectileModel->addChild(rocketParticles);
	}


	Missile::~Missile() {
	}

} // namespace game