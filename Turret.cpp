#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdexcept>
#include <iostream>

#include "Turret.h"

namespace game {
	Turret::Turret(ResourceManager* resman) : DirectionalSceneNode("turret", "", "", "", resman) {
		body = new SceneNode("turret_body", "CubeMesh", "EnemyMaterial", "", resman);
		gun_housing = new SceneNode("turret_gun_housing", "CylinderMesh", "EnemyMaterial", "", resman);
		barrel = new SceneNode("turret_barrel", "CylinderMesh", "EnemyMaterial", "", resman);
		//std::cout << "Current position: (" << this->GetPosition().x << ", " << this->GetPosition().y << ", " << this->GetPosition().z << ") " << std::endl;

		// Set up body
		body->SetPosition(glm::vec3(0.0, 0.0, 0.0));
		body->SetScale(glm::vec3(0.2, 0.04, 0.2));
		glm::vec3 bodyScale = body->GetScale();
		this->addChild(body);

		// Set up gun
		gun_housing->SetScale(glm::vec3(bodyScale.x / 1.5, bodyScale.y * 3, bodyScale.z / 1.5));
		glm::vec3 gunScale = gun_housing->GetScale();
		gun_housing->SetPosition(glm::vec3(0, bodyScale.y* 1.5, 0));
		body->addChild(gun_housing);

		// Set up barrel
		barrel->SetScale(glm::vec3(gunScale.x / 3, gunScale.y * 2, gunScale.z / 3));
		glm::vec3 barrelScale = barrel->GetScale();
		barrel->SetPosition(glm::vec3(0, -gunScale.y / 4, 0));
		barrel->SetOrientation(glm::angleAxis(-glm::pi<float>() / 3.0f, glm::vec3(0, 0, 1.0)));
		gun_housing->addChild(barrel);

		// Set initial forward and side vectors
		forward_ = glm::vec3(-1, 0, 0);
		side_ = glm::vec3(0, 0, 1);
	}
	
	Turret::~Turret() {
		delete body, gun_housing, barrel;
	}

	void Turret::turnLeft() {
		turnDirection += 1;
	}

	void Turret::turnRight() {
		turnDirection += -1;
	}

	void Turret::Update(SceneNode* player) {
		//std::cout << "Player position: (" << player->GetPosition().x<<", " << player->GetPosition().y << ", " << player->GetPosition().z << ") " << std::endl;
		//std::cout << "Current position: (" << body->GetPosition().x << ", " << body->GetPosition().y << ", " << body->GetPosition().z << ") " << std::endl;

		//find position of player and self
		glm::vec2 playerPos = glm::vec2(player->GetPosition().x, player->GetPosition().z);
		glm::vec2 currentPos = glm::vec2(body->GetPosition().x, body->GetPosition().z);
		
		//find vector between self and player then normalize
		glm::vec2 newDirection = glm::vec2(0, 0);
		newDirection = currentPos - playerPos;
		newDirection = glm::normalize(newDirection);
		glm::vec2 forward = glm::vec2(this->getForward().x, this->getForward().z);
		forward = glm::normalize(forward);
		float theta = 0;
		if(newDirection.x != NULL){
			theta = acos(glm::dot(newDirection, forward) / (glm::length(newDirection) * glm::length(newDirection)));
		}

		//change the orientation of the turret
		if (newDirection.y < 0) {
			gun_housing->SetOrientation(glm::angleAxis(-theta, glm::vec3(0.0, 1.0, 0.0)));
		}
		else {
			gun_housing->SetOrientation(glm::angleAxis(theta, glm::vec3(0.0, 1.0, 0.0)));
		}
	}
}