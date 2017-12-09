#include <stdexcept>
#include <iostream>

#include "Projectile.h"

namespace game {

	int Projectile::projectileId = 0;

	Projectile::Projectile() : DirectionalSceneNode(computeProjectileId(), "", "") {

		forward_ = glm::vec3(0, 0, 0);
		SetPosition(glm::vec3(0, 0, 0));
	}

	Projectile::Projectile(glm::vec3 position, glm::vec3 forward) : DirectionalSceneNode(computeProjectileId(), "", "") {
		
		forward_ = forward;
		SetPosition(position);
	}


	Projectile::~Projectile() {
		delete projectileModel;
	}

	std::string Projectile::computeProjectileId() {
		return "Projectile" + std::to_string(projectileId++);
	}

	void Projectile::setActive(bool activeState) {
		active = activeState;
	}

	void Projectile::setForward(glm::vec3 newForward) {
		forward_ = newForward;
	}

	void Projectile::setSpeed(float newSpeed) {
		speed = newSpeed;
	}

	void Projectile::SetPosition(glm::vec3 position) {
		startingPosition = position;
		SceneNode::SetPosition(position);
	}

	void Projectile::move() {
		Translate(forward_ * speed);
	}

	glm::mat4 Projectile::Draw(Camera *camera, glm::mat4 parent_transf) {
		if (active) {
			return SceneNode::Draw(camera, parent_transf);
		}
		else {
			return glm::mat4(0.0);
		}
	}

	float Projectile::getBoundingSphereRadius(void) const {
		return projectileModel->GetScale().x < projectileModel->GetScale().y ? std::min(projectileModel->GetScale().x, projectileModel->GetScale().z) : std::min(projectileModel->GetScale().y, projectileModel->GetScale().z);
	}

	bool Projectile::isOutOfRange() {
		return glm::distance(startingPosition, GetPosition()) > activeRange;
	}

} // namespace game
