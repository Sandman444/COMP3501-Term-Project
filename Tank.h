#ifndef TANK_H 
#define TANK_H

#include "DirectionalSceneNode.h"
#include "EnemyProjectileManager.h"

namespace game {

	class Tank : public DirectionalSceneNode {

	public:
		// Constructor
		Tank(EnemyProjectileManager *manager);

		// Destructor
		~Tank();

		void Update(void) override;

		/*void moveLeft();
		void moveRight();
		void moveForward();
		void moveBackward();*/
		void turnLeft();
		void turnRight();

		float getBoundingSphereRadius(void) const override;

	private:

		EnemyProjectileManager *projectileManager;
		SceneNode *tank_body, *gun_turret, *gun_barrel, *tread1, *tread2;

		glm::vec3 velocity;
		glm::vec3 accelerationDirection;
		float accelerationSpeed;

		float turnVelocity = 0;
		int turnDirection = 0;
		float turnSpeed;
	};

} // namespace game

#endif