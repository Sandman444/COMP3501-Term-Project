#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdexcept>
#include <iostream>

#include "Tank.h"

namespace game {

	Tank::Tank(EnemyProjectileManager *manager) : DirectionalSceneNode("tank", "", "", "") {

		projectileManager = manager;

		tank_body = new SceneNode("tank_body", "CubeMesh", "EnemyMaterial", "");
		gun_turret = new DirectionalSceneNode("tank_turret", "CubeMesh", "EnemyMaterial", "");
		gun_barrel = new SceneNode("tank_barrel", "CylinderMesh", "EnemyMaterial", "");
		tread1 = new SceneNode("tank_tread1", "CubeMesh", "EnemyMaterial", "");
		tread2 = new SceneNode("tank_tread2", "CubeMesh", "EnemyMaterial", "");

		// Set up body
		tank_body->SetScale(glm::vec3(0.2, 0.04, 0.2));
		glm::vec3 tankBodyScale = tank_body->GetScale();
		this->addChild(tank_body);

		forward_ = glm::vec3(-1, 0, 0);
		side_ = glm::vec3(0, 0, 1);

		// Set up gun
		gun_turret->setForward(forward_);
		gun_turret->setSide(side_);
		gun_turret->SetScale(glm::vec3(tankBodyScale.x / 1.5, tankBodyScale.y * 3, tankBodyScale.z / 1.5));
		glm::vec3 gunScale = gun_turret->GetScale();
		gun_turret->SetPosition(glm::vec3(0, tankBodyScale.y* 1.5, 0));
		tank_body->addChild(gun_turret);
		
		// Set up barrel
		gun_barrel->SetScale(glm::vec3(gunScale.x / 3, gunScale.y * 2.0, gunScale.z / 3));
		glm::vec3 barrelScale = gun_barrel->GetScale();
		gun_barrel->SetPosition(glm::vec3(-gunScale.x / 3, gunScale.y / 5, 0.0));
		gun_barrel->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1.0)));
		gun_turret->addChild(gun_barrel);

		//Set up 1st tread
		tread1->SetScale(glm::vec3(tankBodyScale.x * 1.5, tankBodyScale.y * 2, tankBodyScale.z / 3));
		glm::vec3 tread1Scale = tread1->GetScale();
		tread1->SetPosition(glm::vec3(0, 0, -tankBodyScale.z / 2));
		tank_body->addChild(tread1);
		
		//setup 2nd tread
		tread2->SetScale(glm::vec3(tankBodyScale.x * 1.5, tankBodyScale.y * 2, tankBodyScale.z / 3));
		glm::vec3 tread2Scale = tread2->GetScale();
		tread2->SetPosition(glm::vec3(0, 0, tankBodyScale.z / 2));
		tank_body->addChild(tread2);
	}


	Tank::~Tank() {
		delete tank_body, gun_turret, gun_barrel, tread1, tread2;
	}

	/*void Tank::moveForward() {
	accelerationDirection += glm::vec3(getForward().x, 0, getForward().z);
	}

	void Tank::moveBackward() {
	accelerationDirection += -glm::vec3(getForward().x, 0, getForward().z);
	}

	void Tank::moveLeft() {
	accelerationDirection += glm::vec3(getSide().x, 0, getSide().z);
	}

	void Tank::moveRight() {
	accelerationDirection += -glm::vec3(getSide().x, 0, getSide().z);
	}*/

	void Tank::turnLeft() {
		turnDirection += 1;
	}

	void Tank::turnRight() {
		turnDirection += -1;
	}

	void Tank::Update(glm::vec3 playerPosition) {

		glm::vec3 toPlayer = glm::normalize(playerPosition - GetPosition());
		gun_turret->yaw(glm::dot(gun_turret->getSide(), toPlayer) * 0.1f);
		gun_turret->pitch(-glm::dot(gun_turret->getUp(), toPlayer) * 0.1f);

		if (glm::distance(GetPosition(), playerPosition) > 10.0) {
			Translate(glm::vec3(toPlayer.x, 0, toPlayer.z) * 0.01f);
		}

		double currentTime = glfwGetTime();
		if (currentTime - lastMissileFire > missileFireInterval) {
			lastMissileFire = currentTime;

			projectileManager->spawnMissile(GetPosition(), gun_turret->getForward(), gun_turret->GetOrientation());
		}
	}

	float Tank::getLevel() {
		return tank_body->GetScale().y / 2;
	}

	float Tank::getBoundingSphereRadius(void) const {
		return tank_body->GetScale().x > tank_body->GetScale().y ? std::max(tank_body->GetScale().x, tank_body->GetScale().z) : std::max(tank_body->GetScale().y, tank_body->GetScale().z);
	}


} // namespace game