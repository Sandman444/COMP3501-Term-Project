#ifndef HELICOPTER_H 
#define HELICOPTER_H

#include "DirectionalSceneNode.h"

namespace game {

	class Helicopter : public DirectionalSceneNode {

	public:
		// Constructor
		Helicopter(ResourceManager* resman);

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

	private:

		SceneNode *body, *cockpit, *rotorbladeJoint, *rotorBlade, *tail, *tailBlade;

		glm::vec3 velocity;
		glm::vec3 accelerationDirection;
		float accelerationFactor;

		glm::vec2 tiltDirection;
		glm::vec2 tiltVelocity;

		float turnVelocity = 0;
		int turnAccelerationDirection = 0;
		float turnAccelerationFactor;

		float tiltFriction;
		float airFriction;
	};

} // namespace game

#endif