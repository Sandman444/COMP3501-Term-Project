#ifndef HELICOPTER_H 
#define HELICOPTER_H


#include "DirectionalSceneNode.h"
#include "ProjectileManager.h"

namespace game {

	class Helicopter : public DirectionalSceneNode {

	public:
		// Constructor
		Helicopter(ProjectileManager *manager);

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

	private:

		ProjectileManager *projectileManager;

		SceneNode *body, *cockpit, *rotorbladeJoint, *rotorBlade, *tail, *tailBlade;

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
	};

} // namespace game

#endif