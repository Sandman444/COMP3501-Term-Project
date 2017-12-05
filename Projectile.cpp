#include <stdexcept>
#include <iostream>

#include "Projectile.h"

namespace game {

	int Projectile::projectileId = 0;

	Projectile::Projectile(glm::vec3 position, glm::vec3 forward) : DirectionalSceneNode(computeProjectileId(), "", "") {
		
		forward_ = forward;
		SetPosition(position);
		buildModel();
	}


	Projectile::~Projectile() {
	}

	std::string Projectile::computeProjectileId() {
		return "Projectile" + ++projectileId;
	}

	void Projectile::buildModel() {
		projectileModel = new SceneNode(GetName() + "Model", "CubeMesh", "ObjectMaterial");
		this->addChild(projectileModel);
	}

	void Projectile::setActive(bool activeState) {
		active = activeState;
	}

	void Projectile::setForward(glm::vec3 newForward) {
		forward_ = newForward;
	}

	void Projectile::move() {
		Translate(forward_ * speed);
	}

	glm::mat4 Projectile::Draw(Camera *camera, glm::mat4 parent_transf) {
		if (active) {
			return SceneNode::Draw(camera, parent_transf);
		}
		else {
			return glm::mat4(1.0);
		}
	}

} // namespace game
