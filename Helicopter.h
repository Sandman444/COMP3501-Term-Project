#ifndef HELICOPTER_H 
#define HELICOPTER_H


#include "DirectionalSceneNode.h"
#include "PlayerProjectileManager.h"
#include "Laser.h"

namespace game {

	class Helicopter : public DirectionalSceneNode {

	public:
		// Constructor
		Helicopter(std::string name, std::string material, PlayerProjectileManager *manager);

		// Destructor
		~Helicopter();

		void Update(void) override;

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void moveForward();
		void moveBackward();
		void turnLeft();
		void turnRight();
		void fireMissile();
		void dropBomb();
		void fireLaser();

		float getBoundingSphereRadius(void) const override;

	private:

		PlayerProjectileManager *projectileManager;

		SceneNode *body, *cockpit, *rotorbladeJoint, *rotorBlade, *tail, *tailBlade;

		Laser laser;
		SceneNode *laserEffect;

		glm::vec3 velocity;
		glm::vec3 accelerationDirection;
		float accelerationSpeed;

		glm::vec2 tiltDirection;
		glm::vec2 tiltVelocity;
		float tiltSpeed;

		float turnVelocity = 0;
		int turnDirection = 0;
		float turnSpeed;

		float tiltFriction;
		float airFriction;
		float levelingForce;

		double lastMissileFire = 0;
		double missileFireInterval = 0.5;

		double lastBombDrop = 0;
		double bombDropInterval = 0.5;
	};

} // namespace game

#endif