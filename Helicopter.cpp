#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdexcept>
#include <iostream>

#include "Helicopter.h"

namespace game {

	Helicopter::Helicopter(ResourceManager* resman) : DirectionalSceneNode("helicopter", "", "", resman) {
		body = new SceneNode("helicopter_body", "CubeMesh", "ObjectMaterial", resman);
		cockpit = new SceneNode("helicopter_rotorblade", "CubeMesh", "ObjectMaterial", resman);
		rotorbladeJoint = new SceneNode("helicopter_rotorbladeJoint", "CylinderMesh", "ObjectMaterial", resman);
		rotorBlade = new SceneNode("helicopter_rotorBlade", "CylinderMesh", "ObjectMaterial", resman);
		tail = new SceneNode("helicopter_rotorBlade", "CylinderMesh", "ObjectMaterial", resman);
		tailBlade = new SceneNode("helicopter_rotorBlade", "CylinderMesh", "ObjectMaterial", resman);

		// Set up body
		body->SetScale(glm::vec3(0.42, 0.15, 0.15));
		glm::vec3 bodyScale = body->GetScale();
		this->addChild(body);

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
		accelerationFactor = 0.001f;
		//tiltAccelerationFactor = 0.002f;
		turnAccelerationFactor = 0.001f;

		tiltFriction = 0.03f;
		airFriction = 0.02f;
	}


	Helicopter::~Helicopter() {
		delete body, cockpit, rotorbladeJoint, rotorBlade, tail, tailBlade;
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
		turnAccelerationDirection += 1;
	}

	void Helicopter::turnRight() {
		turnAccelerationDirection += -1;
	}

	void Helicopter::Update(void) {

		// Up and down acceleration
		glm::vec3 finalAcceleration;
		if (glm::length(accelerationDirection) > 0) {
			finalAcceleration = glm::normalize(accelerationDirection) * accelerationFactor;
		}

		velocity += finalAcceleration - (velocity * airFriction);
		Translate(velocity);
		accelerationDirection = glm::vec3(0);
		if (glm::abs(glm::length(velocity)) < 0.0001) {
			velocity = glm::vec3(0);
		}


		// Tilting while moving: DOESN'T WORK ):
		glm::vec2 finalTiltDirection;
		if (glm::length(tiltDirection) > 0) {
			finalTiltDirection = glm::normalize(tiltDirection) * 0.001f;
		}

		tiltVelocity += finalTiltDirection - (tiltVelocity * tiltFriction);
		//pitch(tiltVelocity.y);
		//roll(-tiltVelocity.x);
		tiltDirection = glm::vec2(0);
		if (glm::abs(glm::length(tiltVelocity)) < 0.0001) {
			tiltVelocity = glm::vec2(0);
		}

		float angle = glm::angle(getUp(), glm::vec3(0, 1, 0));
		glm::vec3 axis = glm::cross(getUp(), glm::vec3(0, 1, 0));
		//Rotate(glm::angleAxis(angle * 0.01f, axis));
		
		//if (angle < 0.1f) {
			//SetOrientation(glm::angleAxis(0.0f, glm::vec3(0, 1, 0)));
		//}



		// Adjusting yaw
		turnVelocity += (turnAccelerationDirection * turnAccelerationFactor) - (turnVelocity * tiltFriction);
		yaw(turnVelocity);
		turnAccelerationDirection = 0;
		if (glm::abs(glm::length(turnVelocity)) < 0.0001) {
			turnVelocity = 0;
		}


		// Blade spinning
		float rot_factor(glm::pi<float>() / 10);
		rotorBlade->Rotate(glm::angleAxis(rot_factor, glm::vec3(1, 0, 0)));
		tailBlade->Rotate(glm::angleAxis(rot_factor, glm::vec3(0, 0, 1)));
	}


} // namespace game
