#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdexcept>
#include <iostream>

#include "EnemyHelicopter.h"

namespace game {

	EnemyHelicopter::EnemyHelicopter() : Helicopter("EnemyMaterial", NULL) {

	}


	EnemyHelicopter::~EnemyHelicopter() {

	}


	void EnemyHelicopter::Update(glm::vec3 playerPosition) {

		// Up down left right acceleration
		/*glm::vec3 finalAcceleration;
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
		projectileManager->setLaserEnd(getForward() * laser.getLength());
		laser.off();
		projectileManager->setLaserOn(laser.isOn());*/
	}


} // namespace game
