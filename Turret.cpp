#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdexcept>
#include <iostream>

#include "Turret.h"

namespace game {
	Turret::Turret(EnemyProjectileManager *manager) : DirectionalSceneNode("turret", "", "", "") {

		projectileManager = manager;

		forward_ = glm::vec3(-1, 0, 0);
		side_ = glm::vec3(0, 0, 1);

		body = new SceneNode("turret_body", "CubeMesh", "EnemyMaterial", "");
		gun_housing = new DirectionalSceneNode("turret_gun_housing", "CylinderMesh", "EnemyMaterial", "");
		barrel = new DirectionalSceneNode("turret_barrel", "CylinderMesh", "EnemyMaterial", "");

		// Set up body
		body->SetScale(glm::vec3(0.2, 0.04, 0.2));
		glm::vec3 bodyScale = body->GetScale();
		this->addChild(body);

		// Set up gun
		gun_housing->setForward(glm::vec3(-1, 0, 0));
		gun_housing->setSide(glm::vec3(0, 0, 1));
		gun_housing->SetScale(glm::vec3(bodyScale.x / 1.5, bodyScale.y * 3, bodyScale.z / 1.5));
		glm::vec3 gunScale = gun_housing->GetScale();
		gun_housing->SetPosition(glm::vec3(0, bodyScale.y * 1.5, 0));
		body->addChild(gun_housing);

		// Set up barrel
		barrel->setForward(glm::vec3(0, 1, 0));
		barrel->setSide(glm::vec3(0, 0, -1));
		barrel->SetScale(glm::vec3(gunScale.x / 3, gunScale.y * 2, gunScale.z / 3));
		glm::vec3 barrelScale = barrel->GetScale();
		barrel->SetPosition(glm::vec3(0, -gunScale.y / 4, 0));
		barrel->SetOrientation(glm::angleAxis(glm::pi<float>() / 3.0f, glm::vec3(0, 0, 1.0)));
		gun_housing->addChild(barrel);
	}
	
	Turret::~Turret() {
		delete body, gun_housing, barrel;
	}

	float Turret::getLevel() {
		return body->GetScale().y / 2;
	}

	void Turret::turnLeft() {
		turnDirection += 1;
	}

	void Turret::turnRight() {
		turnDirection += -1;
	}

	void Turret::Update(glm::vec3 playerPosition) {

		glm::vec3 toPlayer = glm::normalize(playerPosition - GetPosition());

		double currentTime = glfwGetTime();
		if (currentTime - lastMissileFire > missileFireInterval) {
			lastMissileFire = currentTime;

			projectileManager->spawnSplineMissile(GetPosition(), gun_housing->getForward(), gun_housing->GetOrientation(), playerPosition);
		}
	}

	float Turret::getBoundingSphereRadius(void) const {
		return body->GetScale().x > body->GetScale().y ? std::max(body->GetScale().x, body->GetScale().z) : std::max(body->GetScale().y, body->GetScale().z);
	}
}