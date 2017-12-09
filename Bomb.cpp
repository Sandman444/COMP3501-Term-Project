#include <stdexcept>
#include <iostream>

#include "Bomb.h"

namespace game {

	Bomb::Bomb(glm::vec3 position) : Projectile(position, glm::vec3(0, -1, 0)) {
		projectileModel = new SceneNode(GetName() + "Model", "SphereMesh", "ObjectMaterial");
		projectileModel->SetScale(glm::vec3(0.2, 0.2, 0.2));
		this->addChild(projectileModel);

		speed = 0.01;

		//add the explosion to the bomb to show when it blows up
		//NOTE: Needs explosion effect
		projectileEffect = new SceneNode(GetName() + "Effect", "TorusParticles", "LaserMaterial");
		//projectileEffect->SetPosition(glm::vec3(0, 0, 0));
		projectileModel->addChild(projectileEffect);
	}


	Bomb::~Bomb() {
	}

	void Bomb::move() {
		if (GetPosition().y > 0) {
			if (velocity < terminalVelocity) {
				velocity += gravity;
			}
			Translate(forward_ * velocity);
		}
	}

	float Bomb::getBoundingSphereRadius(void) const {
		if (GetPosition().y > 0) {
			return projectileModel->GetScale().x > projectileModel->GetScale().y ? std::max(projectileModel->GetScale().x, projectileModel->GetScale().z) : std::max(projectileModel->GetScale().y, projectileModel->GetScale().z);
		}
		else {
			glm::vec3 explosionScale = glm::vec3(1.5, 1.5, 1.5);
			return explosionScale.x > explosionScale.y ? std::max(explosionScale.x, explosionScale.z) : std::max(explosionScale.y, explosionScale.z);
		}
	}

} // namespace game