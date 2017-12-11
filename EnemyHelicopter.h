#ifndef ENEMYHELICOPTER_H 
#define ENEMYHELICOPTER_H

#include "Helicopter.h"

namespace game {

	class EnemyHelicopter : public Helicopter {

	public:
		// Constructor
		EnemyHelicopter(void);

		// Destructor
		~EnemyHelicopter();

		void Update(glm::vec3 playerPosition) override;

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void moveForward();
		void moveBackward();
		void turnLeft();
		void turnRight();

	private:

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
