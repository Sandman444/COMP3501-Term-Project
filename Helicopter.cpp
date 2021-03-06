#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdexcept>
#include <iostream>

#include "Helicopter.h"

namespace game {

	Helicopter::Helicopter(std::string name, std::string material, PlayerProjectileManager *manager) : DirectionalSceneNode(name, "", "", "") {

		projectileManager = manager;

		body = new SceneNode("helicopter_body", "CubeMesh", material, "");
		cockpit = new SceneNode("helicopter_rotorblade", "CubeMesh", material, "");
		rotorbladeJoint = new SceneNode("helicopter_rotorbladeJoint", "CylinderMesh", material, "");
		rotorBlade = new SceneNode("helicopter_rotorBlade", "CylinderMesh", material, "");
		tail = new SceneNode("helicopter_rotorBlade", "CylinderMesh", material, "");
		tailBlade = new SceneNode("helicopter_rotorBlade", "CylinderMesh", material, "");

		// Set up body
		body->SetScale(glm::vec3(0.42, 0.15, 0.15));
		glm::vec3 bodyScale = body->GetScale();
		this->addChild(body);

		// Attach laser
		laser = new Laser(name);
		body->addChild(laser);

		// Set up cockpit
		cockpit->SetScale(glm::vec3(bodyScale.y / 2.0, bodyScale.y / 2.0, bodyScale.z));
		glm::vec3 cockpitScale = cockpit->GetScale();
		cockpit->SetPosition(glm::vec3(-bodyScale.x / 2.0 - cockpitScale.x / 2.0, -bodyScale.y / 2.0 + cockpitScale.y / 2.0, 0));
		body->addChild(cockpit);

		// Set up rotorblade joint
		rotorbladeJoint->SetScale(glm::vec3(bodyScale.z - 0.05, (bodyScale.z - 0.05) / 4.0, bodyScale.z - 0.05));
		glm::vec3 bladeJointScale = rotorbladeJoint->GetScale();
		rotorbladeJoint->SetPosition(glm::vec3(0, bodyScale.y / 2.0 + bladeJointScale.y / 2.0, 0));
		body->addChild(rotorbladeJoint);

		// Set up rotorblade
		rotorBlade->SetScale(glm::vec3(bladeJointScale.y / 2.0, bodyScale.x * 1.9, bladeJointScale.y / 2.0));
		rotorBlade->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1.0)));
		rotorbladeJoint->addChild(rotorBlade);

		// Set up tail
		tail->SetScale(glm::vec3(bodyScale.z / 3.0, bodyScale.x / 1.2, bodyScale.z / 3.0));
		glm::vec3 tailScale = tail->GetScale();
		tail->SetPosition(glm::vec3(bodyScale.x / 2.0 + tailScale.y / 2.0, 0, 0));
		tail->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1.0)));
		body->addChild(tail);

		// Set up tailblade
		tailBlade->SetScale(glm::vec3(bladeJointScale.y / 2.0, 0.2, bladeJointScale.y / 2.0));
		glm::vec3 tailBladeScale = tailBlade->GetScale();
		tailBlade->SetPosition(glm::vec3(0, -tailScale.y / 2.0 + tailScale.y / 10.0, tailScale.z / 2.0 + tailBladeScale.z / 2.0));
		tail->addChild(tailBlade);

		// Set initial forward and side vectors
		forward_ = glm::vec3(-1, 0, 0);
		side_ = glm::vec3(0, 0, 1);

		// Other settings
		accelerationSpeed = 0.0017f;
		turnSpeed = 0.0008f;
		tiltSpeed = 0.001f;

		tiltFriction = 0.03f;
		airFriction = 0.018f;
		levelingForce = 0.07f;
	}


	Helicopter::~Helicopter() {
		delete body, cockpit, rotorbladeJoint, rotorBlade, tail, tailBlade, laser;
	}

	void Helicopter::moveUp() {
		accelerationDirection += glm::vec3(0, 1, 0); // Always move straight up and down
	}

	void Helicopter::moveDown() {
		accelerationDirection += glm::vec3(0, -1, 0);
	}

	void Helicopter::moveForward() {
		accelerationDirection += glm::vec3(getForward().x, 0, getForward().z);
		tiltDirection += glm::vec2(0, 1);
	}

	void Helicopter::moveBackward() {
		accelerationDirection += -glm::vec3(getForward().x, 0, getForward().z);
		tiltDirection += glm::vec2(0, -1);
	}

	void Helicopter::moveLeft() {
		accelerationDirection += glm::vec3(getSide().x, 0, getSide().z);
		tiltDirection += glm::vec2(1, 0);
	}

	void Helicopter::moveRight() {
		accelerationDirection += -glm::vec3(getSide().x, 0, getSide().z);
		tiltDirection += glm::vec2(-1, 0);
	}

	void Helicopter::turnLeft() {
		turnDirection += 1;
	}

	void Helicopter::turnRight() {
		turnDirection += -1;
	}

	void Helicopter::fireMissile() {
		double currentTime = glfwGetTime();
		if (currentTime - lastMissileFire > missileFireInterval) {
			lastMissileFire = currentTime;
			projectileManager->spawnMissile(GetPosition(), getForward(), GetOrientation());
		}
	}

	void Helicopter::dropBomb() {
		double currentTime = glfwGetTime();
		if (currentTime - lastBombDrop > bombDropInterval) {
			lastBombDrop = currentTime;
			projectileManager->spawnBomb(GetPosition());
		}
	}

	void Helicopter::fireLaser() {
		laser->on();
		projectileManager->setLaserOn(laser->isOn());
	}

	void Helicopter::Update(void) {

		// Up down left right acceleration
		glm::vec3 finalAcceleration;
		if (glm::length(accelerationDirection) > 0) {
			finalAcceleration = glm::normalize(accelerationDirection) * accelerationSpeed;
		}

		velocity += finalAcceleration - (velocity * airFriction);
		Translate(velocity);
		accelerationDirection = glm::vec3(0);
		if (glm::abs(glm::length(velocity)) < 0.0001) {
			velocity = glm::vec3(0);
		}


		// Tilting while moving
		glm::vec2 finalTiltDirection;
		if (glm::length(tiltDirection) > 0) {
			finalTiltDirection = glm::normalize(tiltDirection) * tiltSpeed;
		}

		tiltVelocity += finalTiltDirection - (tiltVelocity * tiltFriction);
		pitch(tiltVelocity.y);
		roll(-tiltVelocity.x);
		tiltDirection = glm::vec2(0);
		if (glm::abs(glm::length(tiltVelocity)) < 0.0001) {
			tiltVelocity = glm::vec2(0);
		}

		// Leveling
		glm::vec2 flatenedUp = -glm::vec2(getUp().x, getUp().z);
		glm::vec2 flatenedForward = glm::vec2(getForward().x, getForward().z);
		glm::vec2 flatenedSide = glm::vec2(getSide().x, getSide().z);
		pitch(glm::dot(flatenedUp, flatenedForward) * levelingForce);
		roll(-glm::dot(flatenedUp, flatenedSide) * levelingForce);
		

		// Adjusting yaw
		turnVelocity += (turnDirection * turnSpeed) - (turnVelocity * tiltFriction);
		yaw(turnVelocity);
		turnDirection = 0;
		if (glm::abs(glm::length(turnVelocity)) < 0.0001) {
			turnVelocity = 0;
		}


		// Blade spinning
		float rot_factor(glm::pi<float>() / 10);
		rotorBlade->Rotate(glm::angleAxis(rot_factor, glm::vec3(1, 0, 0)));
		tailBlade->Rotate(glm::angleAxis(rot_factor, glm::vec3(0, 0, 1)));

		// Update laser
		projectileManager->setLaserStart(GetPosition());
		projectileManager->setLaserEnd(getForward() * laser->getLength());
		laser->off();
		projectileManager->setLaserOn(laser->isOn());
	}

	float Helicopter::getBoundingSphereRadius(void) const {
		return body->GetScale().x > body->GetScale().y ? std::max(body->GetScale().x, body->GetScale().z) : std::max(body->GetScale().y, body->GetScale().z);
	}


} // namespace game
