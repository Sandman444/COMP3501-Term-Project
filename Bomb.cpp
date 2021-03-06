#include <stdexcept>
#include <iostream>

#include "Bomb.h"

namespace game {

	Bomb::Bomb(glm::vec3 position) : Projectile(position, glm::vec3(0, -1, 0)) {
		projectileModel = new SceneNode(GetName() + "Model", "SphereMesh", "PlayerMaterial", "");
		projectileModel->SetScale(glm::vec3(0.2, 0.2, 0.2));
		this->addChild(projectileModel);

		explosionEffect = new SceneNode(GetName() + "ExplosionEffect", "SphereParticles", "ExplosionMaterial", "Sparkle");
		explosionEffect->SetBlending(true);

		speed = 0.01;
	}


	Bomb::~Bomb() {
		delete explosionEffect;
	}

	void Bomb::move() {
		if (GetPosition().y > 0) {
			if (velocity < terminalVelocity) {
				velocity += gravity;
			}
			Translate(forward_ * velocity);
		}
		else if (exploding) {
			double currentTime = glfwGetTime();
			if (currentTime - explosionTimer > explosionDuration) {
				exploding = false;
				doneExploding = true;
			}
		}
		else if (!doneExploding) {
			exploding = true;
			projectileModel->addChild(explosionEffect);
			explosionTimer = glfwGetTime();
		}
	}

	float Bomb::getBoundingSphereRadius(void) const {
		if (!exploding) {
			return projectileModel->GetScale().x > projectileModel->GetScale().y ? std::max(projectileModel->GetScale().x, projectileModel->GetScale().z) : std::max(projectileModel->GetScale().y, projectileModel->GetScale().z);
		}
		else {
			glm::vec3 explosionScale = glm::vec3(1.5, 1.5, 1.5);
			return explosionScale.x > explosionScale.y ? std::max(explosionScale.x, explosionScale.z) : std::max(explosionScale.y, explosionScale.z);
		}
	}

	bool Bomb::isOutOfRange() {
		return doneExploding;
	}

} // namespace game